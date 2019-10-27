/*
 * serial.h
 *
 *  Created on: Oct 26, 2019
 *      Author: george
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#define SERIAL_LL_IDLE 0
#define SERIAL_LL_OPEN_WAIT 1
#define SERIAL_LL_PAIRED 2

extern volatile uint8_t serial_ll_state;

void serial_timeout();
void serial_init();

#endif /* SERIAL_H_ */
