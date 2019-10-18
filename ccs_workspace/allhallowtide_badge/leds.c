/*
 * leds.c
 *
 *  Created on: Oct 17, 2019
 *      Author: george
 */

#include <stdint.h>
#include <msp430fr2512.h>
#include <driverlib.h>

#include "leds.h"

/*
 * The LED order is RIGHT TO LEFT. So, gs[0] is the rightmost LED,
 *  gs[3] is the leftmost, and gs[4] is the HEART!
 */
