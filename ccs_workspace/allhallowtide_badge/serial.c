/*
 * serial.c
 *
 *  Created on: Oct 26, 2019
 *      Author: george
 */
#include <stdint.h>

#include <msp430fr2512.h>

#include "badge.h"
#include "serial.h"

volatile uint8_t serial_ll_state;
volatile uint8_t paired_id;

void serial_init() {
    serial_ll_state = SERIAL_LL_IDLE;

    // Pause the UART peripheral:
    UCA0CTLW0 |= UCSWRST;
    // Source the baud rate generation from SMCLK (8 MHz)
    // 8N1 (8 data bits, even parity bit, 1 stop bit)
    UCA0CTLW0 |= UCSSEL__SMCLK + UCPEN_1 + UCPAR_1 + UCSPB_0;
    // Configure the baud rate to 230400.
    //  (See page 589 in the family user's guide, SLAU445I)
    // The below is for 8.00 MHz SMCLK:
    UCA0BRW = 2;
    UCA0MCTLW = 0xBB00 | UCOS16_1 | UCBRF_2;

    // Activate the UART:
    UCA0CTLW0 &= ~UCSWRST;

    // The TX interrupt flag (UCTXIFG) gets set upon enabling the UART.
    //  But, we'd prefer that interrupt not to fire, so we'll clear it
    //  now:
    UCA0IFG &= ~UCTXIFG;

    // Enable interrupts for TX and RX:
    UCA0IE |= UCTXIE | UCRXIE;

}

void serial_send_pair() {
    // TODO: Do we need a sync byte or something?
    UCA0TXBUF = (BIT7 | badge_conf.badge_id);
}

void serial_send_pair_ack() {
    UCA0TXBUF = (BIT6 | badge_conf.badge_id);
}

void serial_timeout() {
    if (serial_ll_state == SERIAL_LL_OPEN_WAIT) {
        // re-tx pair
        serial_send_pair();
    }
}

#pragma vector=USCI_A0_VECTOR
__interrupt void serial_isr() {
    uint8_t buffer;
    switch(__even_in_range(UCA0IV, UCIV__UCTXIFG)) {
    case UCIV__UCRXIFG:
        // Receive buffer full; a byte is ready to read.
        buffer = UCA0RXBUF;

        switch(serial_ll_state) {
        case SERIAL_LL_OPEN_WAIT:
            // we're awaiting either a pair or an ack
            if (buffer & BIT6 && !(buffer & BIT7)) {
                //PAIR_ACK message
                // State transition to PAIRED.
                serial_ll_state = SERIAL_LL_PAIRED;
                paired_id = buffer & ~(BIT7+BIT6); // limit 63 I guess
                if (paired_id < 40) {
                    f_paired = 1;
                    LPM0_EXIT;
                } else {
                    // invalid ID I guess?
                    break;
                }
            }
            // fall through, to handle the non-ack one.
        case SERIAL_LL_PAIRED:
            if (buffer & BIT7 && !(buffer & BIT6)) {
                // PAIR message
                // Send an ACK.
                UCA0TXBUF = (BIT6 | badge_conf.badge_id);
            }
            break;
        }
        break;
    case UCIV__UCTXIFG:
        break;
    }

}

