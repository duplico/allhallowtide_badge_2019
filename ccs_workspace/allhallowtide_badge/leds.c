/*
 * leds.c
 *
 *  Created on: Oct 17, 2019
 *      Author: george
 */

#include <stdint.h>
#include <stdlib.h>

#include <msp430fr2512.h>
#include <driverlib.h>

#include "tlc5948a.h"

#include "leds.h"
#include "band_anims.h"

/*
 * The LED order is RIGHT TO LEFT. So, gs[0] is the rightmost LED,
 *  gs[3] is the leftmost, and gs[4] is the HEART!
 */

const rgbcolor_t band_off[BAND_LED_COUNT] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
};

rgbcolor_t band_colors_curr[BAND_LED_COUNT] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
};

rgbcolor_t band_colors_next[BAND_LED_COUNT] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
};

rgbdelta_t band_colors_step[BAND_LED_COUNT] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
};

/// Does the heart LED need re-display to the LED driver?
uint8_t heart_dirty = 1;
/// Does the band display need re-sent to the LED driver?
uint8_t band_dirty = 1;

// TODO: Refactor this out:
uint8_t band_animation_state = 0;

rgbcolor_t heart_color_curr;
rgbcolor_t heart_color_next;
rgbdelta_t heart_color_step;

// TODO: use:
uint8_t heart_state;

uint8_t band_anim_frame = 0;
uint8_t band_anim_id = 0;
uint8_t band_anim_type = 0;
uint8_t band_saved_anim_id = 0;
uint8_t band_saved_anim_type = 0;
uint8_t band_is_ambient = 1;
uint8_t band_anim_looping = 0;
uint8_t band_anim_length = 0;
uint16_t band_hold_steps = 0;
uint16_t band_hold_index = 0;
uint16_t band_transition_steps = 0;
uint16_t band_transition_index = 0;
const band_animation_t *band_current_anim;

uint8_t wiggle_mask = 0xff;

// TODO: Use this to configure the brightness:
uint8_t current_ambient_correct = 0;
uint8_t previous_ambient_correct = 0;

uint8_t band_twinkle_bits = 0xea;
uint16_t band_anim_adjustment_index = 0;

// See https://graphics.stanford.edu/~seander/bithacks.html#IntegerLogObvious
inline uint8_t log2(uint16_t v) {
    int8_t r = 0; // r will be lg(v)
    while (v >>= 1)
    {
        r++;
    }

    return r;
}

void set_heart() {

}

/// Start a new frame, setting up current, source, dest, and step.
void band_load_colors() {
    // leg_colors_curr <- tentacle_current_anim[tentacle_anim_index]

    // Stage in the current color:
    memcpy(band_colors_curr, band_current_anim->colors[band_anim_frame], sizeof(rgbcolor_t)*BAND_LED_COUNT);

    // Stage in the next color:
    // If we're looping, it's modded. If not looping, back to black.
    if (band_anim_frame == band_current_anim->len-1 && !(band_anim_looping || band_is_ambient)) { // last frame:
        // We're at the last frame, and we are NOT looping. So our NEXT
        // color will be OFF.
        memcpy(band_colors_next, band_off, sizeof(rgbcolor_t)*BAND_LED_COUNT);
    } else {
        // We're either looping or not at the end, so it's probably safe to skip this:
        uint8_t next_id = (band_anim_frame+1) % band_current_anim->len;
        memcpy(band_colors_next, band_current_anim->colors[next_id], sizeof(rgbcolor_t)*BAND_LED_COUNT);
    }

    // Stage in the step color:
    for (uint8_t i = 0; i < BAND_LED_COUNT; i++)
    {
        band_colors_step[i].red = ((int_fast32_t) band_colors_next[i].red - band_colors_curr[i].red) / band_transition_steps;
        band_colors_step[i].green = ((int_fast32_t) band_colors_next[i].green - band_colors_curr[i].green) / band_transition_steps;
        band_colors_step[i].blue = ((int_fast32_t) band_colors_next[i].blue - band_colors_curr[i].blue) / band_transition_steps;
    }
}

/// Do a fading step within a frame, stepping colors by their step values.
inline void band_fade_colors() {
    // If this is the very last transition step,
    if (band_transition_steps && band_transition_index == band_transition_steps-1) {
        // hit the destination:
        memcpy(band_colors_curr, band_colors_next,
               sizeof(rgbcolor_t) * BAND_LED_COUNT);
    } else {
        for (uint8_t i = 0; i < BAND_LED_COUNT; i++)
        {
            // TODO: Check how well this works:
            band_colors_curr[i].red += band_colors_step[i].red;
            band_colors_curr[i].green += band_colors_step[i].green;
            band_colors_curr[i].blue += band_colors_step[i].blue;
        }
    }
}

// TODO:
//void eye_twinkle_off() {
//    eye_twinkle_bits = 0xffffffffffffffff;
//    eyes_twinkling = 0;
//    set_face(face_curr); // Dirty face.
//}
//
//void eye_twinkle_on() {
//    eyes_twinkling = 1;
//    face_anim_adj_index = 0;
//}
//
//void tentacle_wiggle() {
//    uint8_t wiggle_mask_temp = 0xff;
//    if (band_current_anim->wiggle) {
//        wiggle_mask_temp &= ~(1 << (rand() % 4));
//        if (rand() % 2) wiggle_mask_temp &= ~(1 << (rand() % 4));
//    }
//    wiggle_mask = wiggle_mask_temp;
//}

/// Actually apply the appropriate colors to our grayscale values.
/**
 ** This also handles special cases, like twinkling.
 **/
void set_band_gs(const rgbcolor_t* band_colors) {
    static uint_fast32_t r = 0;
    static uint_fast32_t g = 0;
    static uint_fast32_t b = 0;

    for (uint8_t flower_index = 0; flower_index < BAND_LED_COUNT; flower_index++)
    {
        r = band_colors[flower_index].red << 1;
        g = band_colors[flower_index].green << 1;
        b = band_colors[flower_index].blue << 1;

        // TODO: Determine what the equivalent of wiggling is, if any:
//        // If it's <3 (meaning lower) and masked out by wiggling,
//        if (flower_index < 4 && !(wiggle_mask & (1 << flower_index))) {
//            // turn it off.
//            r=0;
//            g=0;
//            b=0;
//        } else if (flower_index >=4 && !(wiggle_mask & (1 << (flower_index-4)))) {
//            r = leg_colors[flower_index-4].red;
//            g = leg_colors[flower_index-4].green;
//            b = leg_colors[flower_index-4].blue;
//        }

        // Handle the particulars of the animation's
        //  sub-type. (twinkling, etc.)
        switch(band_current_anim->anim_type) {
        case ANIM_TYPE_FASTTWINKLE:
            if (band_twinkle_bits & (1 << flower_index)) {
                r = r >> 2;
                g = g >> 2;
                b = b >> 2;
            }
            break;
        case ANIM_TYPE_SLOWTWINKLE:
            if (band_twinkle_bits & (1 << flower_index)) {
                r = r >> 2;
                g = g >> 2;
                b = b >> 2;
            }
            break;
        case ANIM_TYPE_HARDTWINKLE:
            if (band_twinkle_bits & (1 << flower_index)) {
                r = 0;
                g = 0;
                b = 0;
            }
            break;
        default:
            break;
        }

        // TODO:
        r = r << current_ambient_correct;
        g = g << current_ambient_correct;
        b = b << current_ambient_correct;

        if (r>UINT16_MAX) r=UINT16_MAX;
        if (g>UINT16_MAX) g=UINT16_MAX;
        if (b>UINT16_MAX) b=UINT16_MAX;

        tlc_gs[3+1+(3-flower_index)*3] = b;
        tlc_gs[3+2+(3-flower_index)*3] = g;
        tlc_gs[3+3+(3-flower_index)*3] = r;
    }
}

void band_set_steps_and_go() {
    // TODO: Modify this as appropriate:
    band_hold_steps = band_current_anim->durations[band_anim_frame] / 13; // / LEGS_DUR_STEP;
    band_hold_index = 0;
    // TODO: And this:
    band_transition_steps = band_current_anim->fade_durs[band_anim_frame] / 13; // / LEGS_DUR_STEP;
    band_transition_index = 0;

    band_load_colors();

    // TODO: Is this double-called, due to the "dirty" logic?
    set_band_gs(band_current_anim->colors[band_anim_frame]);
}

/// Launch a new headband animation, possibly as the new ambient one.
/**
 ** This should generally not be called directly by the application logic,
 **  but rather indirectly by invoking `band_start_anim_by_id`.
 */
void band_start_anim_by_struct(const band_animation_t *animation, uint8_t loop, uint8_t ambient) {
    // If ambient=1, then a bit of pre-work is needed.
    // If we've been asked to do an interrupting animation, remember what our ambient anim
    //  was so we can go back to it.
    if (!ambient && band_is_ambient) {
        band_saved_anim_id = band_anim_id;
        band_saved_anim_type = band_anim_type;
    }

    band_is_ambient = ambient;

    band_current_anim = animation;

    band_anim_frame = 0; // This is our frame index in the animation.
    band_animation_state = 1; // animating

    band_anim_adjustment_index = 0;
    // TODO: Can we have a non-looping non-ambient? Are those the same?
    band_anim_looping = loop;
    band_anim_length = band_current_anim->len;

    // TODO: What to do with this?
    wiggle_mask = 0xff;

    band_set_steps_and_go();
}

void band_start_anim_by_id(uint8_t anim_id, uint8_t anim_type, uint8_t loop, uint8_t ambient) {
    if (ambient && !band_is_ambient) {
        // If we've been asked to switch our ambient animation, but we're currently in an
        //  interrupting animation, we need to change what we have saved so we go back to
        //  the new ambient animation.
        band_saved_anim_id = anim_id;
        band_saved_anim_type = anim_type;
        return;
    }

    band_start_anim_by_struct(legs_all_anim_sets[anim_id][anim_type], loop, ambient);

    band_anim_id = anim_id;
    band_anim_type = anim_type;
}

/// Load and display the next animation frame in the current animation.
void band_next_anim_frame() {
    band_anim_frame++; // This is our index in the animation.

    if (band_anim_frame >= band_anim_length) { // rolled over.
        if (band_is_ambient) { // we're ambient. (loop is dontcare)
            band_anim_frame = 0; // start over from beginning.
        } else if (band_anim_looping) { // not ambient; loops remaining
            band_anim_frame = 0;
            band_anim_looping--;
        } else { // not ambient, no loops remaining
            band_is_ambient = 1; // Now we're back to being ambient...
            band_start_anim_by_id(band_saved_anim_id, band_saved_anim_type, 0, 1);
            // TODO: Do any additional needs for the completion of a non-ambient animation.
            return; // skip the transitions_and_go because that's called in start_anim.
        }
    }

    band_set_steps_and_go();
}

/// Do a time step of the LED animation system.
void leds_timestep() {
    // If the ambient light correction has changed, mark everything dirty.
    if (current_ambient_correct != previous_ambient_correct) {
        previous_ambient_correct = current_ambient_correct;
        heart_dirty = 1;
        band_dirty = 1;
    }

    // Handle the heart.

    // TODO: Determine if animation tasks need to happen, and perform them.

    if (heart_dirty) {
        // TODO: Set up the display in tlc_gs.
    }

    // Handle the band:
    //  Apply our current delta animation timestep.
    switch(band_current_anim->anim_type) {
    case ANIM_TYPE_FASTTWINKLE:
        band_anim_adjustment_index++;
        if (band_anim_adjustment_index == BAND_TWINKLE_STEPS_FAST) {
            band_twinkle_bits = rand() % 256;
            band_anim_adjustment_index = 0;
            band_dirty = 1;
        }
        break;
    case ANIM_TYPE_SLOWTWINKLE:
        band_anim_adjustment_index++;
        if (band_anim_adjustment_index == BAND_TWINKLE_STEPS_SLOW) {
            band_twinkle_bits = rand() % 256;
            band_anim_adjustment_index = 0;
            band_dirty = 1;
        }
        break;
    case ANIM_TYPE_HARDTWINKLE:
        band_anim_adjustment_index++;
        if (band_anim_adjustment_index == BAND_TWINKLE_STEPS_HARD) {
            band_twinkle_bits = rand() % 256;
            band_anim_adjustment_index = 0;
            band_dirty = 1;
        }
        break;
    default:
        // SOLID
        break;
    }

    if (band_animation_state) {
        if (band_hold_index < band_hold_steps) {
            // Hold the same color.
            band_hold_index++;
        } else {
            // We're transitioning:
            band_transition_index++;
            if (band_transition_index >= band_transition_steps) {
                // next frame plx.
                band_next_anim_frame();
                band_dirty = 1;
            } else {
                band_fade_colors();
                band_dirty = 1;
            }
        }
    }

    if (band_dirty) {
        set_band_gs(band_colors_curr);
    }

    // If either the heart or the band was updated,
    if (band_dirty || heart_dirty) {
        // then re-send to the LED driver.
        tlc_set_gs();
        band_dirty = heart_dirty = 0;
    }

}
