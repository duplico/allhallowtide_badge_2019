/*
 * leds.h
 *
 *  Created on: Oct 17, 2019
 *      Author: george
 */

#ifndef LEDS_H_
#define LEDS_H_

#include <stdint.h>

#define BAND_LED_COUNT 4
#define LEGS_DUR_STEP 14

#define BAND_TWINKLE_STEPS_FAST 100
#define BAND_TWINKLE_STEPS_SLOW 400
#define BAND_TWINKLE_STEPS_HARD 14

typedef struct {
    uint16_t red;
    uint16_t green;
    uint16_t blue;
} rgbcolor16_t;


typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} rgbcolor_t;

typedef struct {
    int_fast32_t red;
    int_fast32_t green;
    int_fast32_t blue;
} rgbdelta_t;

typedef struct {
    const rgbcolor_t (*colors)[4];
    const uint16_t *durations;
    const uint16_t *fade_durs;
    uint8_t len;
    uint8_t anim_type;
    uint8_t boop_loops;
} band_animation_t;

void leds_timestep();
void band_start_anim_by_id(uint8_t anim_id, uint8_t anim_type, uint8_t loop, uint8_t ambient);

#endif /* LEDS_H_ */
