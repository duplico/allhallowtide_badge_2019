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
uint8_t tlc_send_type;
uint8_t tlc_tx_index;   // Index of the current byte in the TX buffer

// Let's make these 12-bit. So the most significant hexadigit will be brightness-correct.
uint16_t tlc_gs[16];

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
        0x10,
        // HERE WE SWITCH TO 7-BIT SPI.
        // The following index is 18:
        0x7F, // unused
        0x60, 0x27, 0x7F, // band
        0x60, 0x27, 0x7F, // band
        0x60, 0x27, 0x7F, // band
        0x60, 0x27, 0x7F, // band
        0x60, 0x27, 0x7F, // heart
};

/// Start an asynchronous send of the TLC5948S grayscale data.
void tlc_set_gs() {
    while (tlc_send_type != TLC_SEND_IDLE)
        __no_operation(); // shouldn't ever actually have to block on this.
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
    UCB0CTLW0 = UCSWRST;  // Shut down USCI_B0 and clear CTLW0.

    UCB0CTLW0 |= UCCKPH_1; // Capture on first, change on next
    UCB0CTLW0 |= UCCKPL_0; // Idle LOW polarity
    UCB0CTLW0 |= UCMSB_1; // MSB first.
    UCB0CTLW0 |= UCSYNC_1; // SYNCHRONOUS mode (SPI)
    UCB0CTLW0 |= UCSSEL_2; // SMCLK source
    UCB0CTLW0 |= UCMST_1; // Master mode.

    UCB0BRW = 0x04; // Baudrate is SMCLK/4

    UCB0CTLW0 &= ~UCSWRST; // enable it.

    // Clear and enable UCB0 TX interrupt
    UCB0IFG &= ~UCTXIFG;
    UCB0IE |= UCTXIE;

    tlc_set_fun();
    tlc_set_gs();
}

#pragma vector=USCI_B0_VECTOR
__interrupt void EUSCI_B0_ISR(void)
{
    // TX is the only interrupt turned on?
    if (UCB0IV & 0x04) {

        if (tlc_send_type == TLC_SEND_TYPE_GS) {
            if (tlc_tx_index == 32) { // done
                P1OUT |= BIT0; P1OUT &= ~BIT0; // Pulse LAT
                tlc_send_type = TLC_SEND_IDLE;
                return;
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
                UCB0IFG &= ~UCTXIFG;
                UCB0IE |= UCTXIE;
            } else if (tlc_tx_index == 34) {
                P1OUT |= BIT0; P1OUT &= ~BIT0; // Pulse LAT

                UCB0CTLW0 |= UCSWRST;
                UCB0CTLW0 &= ~UC7BIT;
                UCB0CTLW0 &= ~UCSWRST;
                UCB0IFG &= ~UCTXIFG;
                UCB0IE |= UCTXIE;
                tlc_send_type = TLC_SEND_IDLE;
                return;
            }
            UCB0TXBUF = fun_base[tlc_tx_index];
            tlc_tx_index++;
        } else {
            tlc_send_type = TLC_SEND_IDLE; // probably shouldn't reach.
        }
    }
}
