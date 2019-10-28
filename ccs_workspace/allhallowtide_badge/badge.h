/*
 * badge.h
 *
 *  Created on: Oct 17, 2019
 *      Author: george
 */

#ifndef BADGE_H_
#define BADGE_H_

#define REMOTE_BOOP_MSG 0xf1

typedef struct {
    uint8_t badge_id;
    uint32_t badges_seen;
    uint8_t badge_seen_count;
    uint8_t current_band_id;
} badge_conf_t;

extern volatile uint8_t f_paired;
// TODO: test:
extern volatile uint8_t f_remote_boop;
extern badge_conf_t badge_conf;

#endif /* BADGE_H_ */
