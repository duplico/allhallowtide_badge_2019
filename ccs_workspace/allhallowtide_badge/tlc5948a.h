/*
 * leds.h
 * (c) 2014 George Louthan
 * 3-clause BSD license; see license.md.
 */

#ifndef TLC5948A_H_
#define TLC5948A_H_

#include <stdint.h>
#include <msp430fr2512.h>

#define TLC_SEND_IDLE     0
#define TLC_SEND_TYPE_GS  1
#define TLC_SEND_TYPE_FUN 2

void tlc_init();

uint8_t tlc_test_loopback(uint8_t);

void tlc_set_gs();
void tlc_set_fun();
void tlc_stage_blank(uint8_t);

extern uint16_t tlc_gs[16] = {0, };

#endif /* TLC5948A_H_ */
