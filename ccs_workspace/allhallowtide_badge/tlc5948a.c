/*
 * tlc5948a.c
 * (c) 2016 George Louthan
 * 3-clause BSD license; see license.md.
 */

#include "tlc5948a.h"
#include <driverlib.h>
#include <stdint.h>

/*
 *   LED controller (TLC5948A)
 *        UCB0 - LEDs
 *        (write on rise, change on fall,
 *         clock inactive low, MSB first)
 *        ~somi~, miso, clk (3-wire) (output only)
 *        GSCLK     P1.3 (MCLK)
 *        LAT       P1.0
 *
 */

#define TLC_THISISGS    0x00
#define TLC_THISISFUN   0x01

// Current TLC sending state:
uint8_t tlc_send_type = TLC_SEND_IDLE;
uint8_t tlc_tx_index = 0;   // Index of the current byte in the TX buffer

// Let's make these 12-bit. So the most significant hexadigit will be brightness-correct.
uint16_t tlc_gs[16] = {0, };

// This is the basic set of function data.
// A few of them can be edited.
uint8_t fun_base[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // ...reserved...
        // B135 / PSM(D1)       0
        // B134 / PSM(D0)       0
        // B133 / OLDENA        0
        // B132 / IDMCUR(D1)    0
        // B131 / IDMCUR(D0)    0
        // B130 / IDMRPT(D0)    0
        // B129 / IDMENA        0
        // B128 / LATTMG(D1)    1:
        0x01,
        // B127 / LATTMG(D0)    1
        // B126 / LSDVLT(D1)    0
        // B125 / LSDVLT(D0)    0
        // B124 / LODVLT(D1)    0
        // B123 / LODVLT(D0)    0
        // B122 / ESPWM         1
        // B121 / TMGRST        1
        // B120 / DSPRPT        1:
        0x87,
        // B119 / BLANK
        // and 7 bits of global brightness correction:
        0x7f,
        // HERE WE SWITCH TO 7-BIT SPI.
        // The following index is 18:
        0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
        0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
};

/// Start an asynchronous send of the TLC5948S grayscale data.
void tlc_set_gs() {
    if (tlc_send_type != TLC_SEND_IDLE)
        return;
    tlc_send_type = TLC_SEND_TYPE_GS;
    tlc_tx_index = 0;
    UCB0TXBUF = TLC_THISISGS;
}

/// Start an asynchronous send of the TLC5948A function data.
void tlc_set_fun() {
    while (tlc_send_type != TLC_SEND_IDLE)
        __no_operation(); // shouldn't ever actually have to block on this.
    tlc_send_type = TLC_SEND_TYPE_FUN;
    tlc_tx_index = 0;
    UCB0TXBUF = TLC_THISISFUN;
}

/// Stage the blank bit, but don't send it.
void tlc_stage_blank(uint8_t blank) {
    if (blank) {
        fun_base[17] |= BIT7;
        fun_base[16] &= ~BIT1;
    } else {
        fun_base[17] &= ~BIT7;
        fun_base[16] |= BIT1;
    }
}

/// Stage global brightness if different from default.
void tlc_stage_bc(uint8_t bc) {
    bc = bc & 0b01111111; // Mask out BLANK just in case.
    fun_base[17] &= 0b10000000;
    fun_base[17] |= bc;
}

/// Initialize the TLC5948A driver.
void tlc_init() {
    tlc_stage_blank(1);

    // Configure the eUSCI.
    UCB0CTLW0 |= UCSWRST;  // Shut down USCI_A0,

    // TODO: Get rid of driverlib here if possible.

    // And USCI_A0 peripheral:
    EUSCI_B_SPI_initMasterParam ini = {0};
    ini.clockPhase = EUSCI_B_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT;
    ini.clockPolarity = EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW;
    ini.clockSourceFrequency = 8000000;
    ini.desiredSpiClock = 4000000;
    ini.msbFirst = EUSCI_B_SPI_MSB_FIRST;
    ini.selectClockSource = EUSCI_B_SPI_CLOCKSOURCE_SMCLK;
    ini.spiMode = EUSCI_B_SPI_3PIN;
    EUSCI_B_SPI_initMaster(EUSCI_B0_BASE, &ini);

    UCB0CTLW0 &= ~UC7BIT;  //  put it in 8-bit mode out of caution.
    UCB0CTLW0 &= ~UCSWRST; //  and enable it.

    EUSCI_B_SPI_clearInterrupt(EUSCI_B0_BASE, EUSCI_B_SPI_TRANSMIT_INTERRUPT);
    EUSCI_B_SPI_enableInterrupt(EUSCI_B0_BASE, EUSCI_B_SPI_TRANSMIT_INTERRUPT);

    tlc_set_fun();
    tlc_set_gs();
}

#pragma vector=USCI_B0_VECTOR
__interrupt void EUSCI_B0_ISR(void)
{
    switch (__even_in_range(UCB0IV, 4)) {
    //Vector 2 - RXIFG
    case 2:
        // We received some garbage sent to us while we were sending.
        // TODO:
        EUSCI_B_SPI_receiveData(EUSCI_B0_BASE); // Throw it away.
        break; // End of RXIFG ///////////////////////////////////////////////////////

    case 4: // Vector 4 - TXIFG : I just sent a byte.
        if (tlc_send_type == TLC_SEND_TYPE_GS) {
            if (tlc_tx_index == 32) { // done
                P1OUT |= BIT4; P1OUT &= ~BIT4; // Pulse LAT
                tlc_send_type = TLC_SEND_IDLE;
                break;
            } else { // gs - MSB first; this starts with 0.
                volatile static uint16_t channel_gs = 0;
                channel_gs = tlc_gs[tlc_tx_index / 2]; // Divide by 2 because these are uint16
                if (tlc_tx_index & 0x01) { // odd; less significant byte
                    UCB0TXBUF = (channel_gs & 0xff);
                } else { // even; more significant byte
                    UCB0TXBUF = (channel_gs >> 8) & 0xff;
                }
            }
            tlc_tx_index++;
        } else if (tlc_send_type == TLC_SEND_TYPE_FUN) {
            if (tlc_tx_index == 18) { // after 18 we have to switch to 7-bit mode.
                UCB0CTLW0 |= UCSWRST;
                UCB0CTLW0 |= UC7BIT;
                UCB0CTLW0 &= ~UCSWRST;
                EUSCI_B_SPI_clearInterrupt(EUSCI_B0_BASE, EUSCI_A_SPI_TRANSMIT_INTERRUPT);
                EUSCI_B_SPI_enableInterrupt(EUSCI_B0_BASE, EUSCI_A_SPI_TRANSMIT_INTERRUPT);
            } else if (tlc_tx_index == 34) {
                // LATCH!
                P1OUT |= BIT0;
                P1OUT &= ~BIT0;

                UCB0CTLW0 |= UCSWRST;
                UCB0CTLW0 &= ~UC7BIT;
                UCB0CTLW0 &= ~UCSWRST;
                EUSCI_B_SPI_clearInterrupt(EUSCI_B0_BASE, EUSCI_B_SPI_TRANSMIT_INTERRUPT);
                EUSCI_B_SPI_enableInterrupt(EUSCI_B0_BASE, EUSCI_B_SPI_TRANSMIT_INTERRUPT);
                tlc_send_type = TLC_SEND_IDLE;
                break;
            }
            EUSCI_B_SPI_transmitData(EUSCI_B0_BASE, fun_base[tlc_tx_index]);
            tlc_tx_index++;
        } else {
            tlc_send_type = TLC_SEND_IDLE; // probably shouldn't reach.
        }
        break; // End of TXIFG /////////////////////////////////////////////////////
    default: break;
    } // End of ISR flag switch ////////////////////////////////////////////////////
}
