/*
 * leds.h
 *
 *  Created on: Oct 17, 2019
 *      Author: george
 */

#ifndef LEDS_H_
#define LEDS_H_

#include <stdint.h>

typedef struct {
    uint16_t red;
    uint16_t green;
    uint16_t blue;
} rgbcolor_t;

typedef struct {
    int_fast32_t red;
    int_fast32_t green;
    int_fast32_t blue;
} rgbdelta_t;

#endif /* LEDS_H_ */
