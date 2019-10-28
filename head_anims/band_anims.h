#ifndef BANDANIMS_H_
#define BANDANIMS_H_

#include "leds.h"

#define LEG_CAMO_INDEX 0
#define LEG_INK_INDEX 1
#define LEG_DOUBLEINK_INDEX 2
#define LEG_ANIM_TYPE_NONE 201
#define LEG_ANIM_NONE 211

// frames for the band:
extern const rgbcolor_t fire_band_frames[][4];
extern const uint16_t fire_band_durations[];
extern const uint16_t fire_band_fade_durs[];
extern const band_animation_t fire_band;
extern const band_animation_t *fire_anim_set[1];
// frames for the band:
extern const rgbcolor_t geek_girl_band_frames[][4];
extern const uint16_t geek_girl_band_durations[];
extern const uint16_t geek_girl_band_fade_durs[];
extern const band_animation_t geek_girl_band;
extern const band_animation_t *geek_girl_anim_set[1];
// frames for the band:
extern const rgbcolor_t ice_band_frames[][4];
extern const uint16_t ice_band_durations[];
extern const uint16_t ice_band_fade_durs[];
extern const band_animation_t ice_band;
extern const band_animation_t *ice_anim_set[1];
// frames for the band:
extern const rgbcolor_t lagoon_band_frames[][4];
extern const uint16_t lagoon_band_durations[];
extern const uint16_t lagoon_band_fade_durs[];
extern const band_animation_t lagoon_band;
extern const band_animation_t *lagoon_anim_set[1];
// frames for the band:
extern const rgbcolor_t meta_boop_band_frames[][4];
extern const uint16_t meta_boop_band_durations[];
extern const uint16_t meta_boop_band_fade_durs[];
extern const band_animation_t meta_boop_band;
extern const band_animation_t *meta_boop_anim_set[1];
// frames for the band:
extern const rgbcolor_t meta_newpair_band_frames[][4];
extern const uint16_t meta_newpair_band_durations[];
extern const uint16_t meta_newpair_band_fade_durs[];
extern const band_animation_t meta_newpair_band;
extern const band_animation_t *meta_newpair_anim_set[1];
// frames for the band:
extern const rgbcolor_t meta_pair_band_frames[][4];
extern const uint16_t meta_pair_band_durations[];
extern const uint16_t meta_pair_band_fade_durs[];
extern const band_animation_t meta_pair_band;
extern const band_animation_t *meta_pair_anim_set[1];
// frames for the band:
extern const rgbcolor_t pan_band_frames[][4];
extern const uint16_t pan_band_durations[];
extern const uint16_t pan_band_fade_durs[];
extern const band_animation_t pan_band;
extern const band_animation_t *pan_anim_set[1];
// frames for the band:
extern const rgbcolor_t rainbow_band_frames[][4];
extern const uint16_t rainbow_band_durations[];
extern const uint16_t rainbow_band_fade_durs[];
extern const band_animation_t rainbow_band;
extern const band_animation_t *rainbow_anim_set[1];
// frames for the band:
extern const rgbcolor_t wiggle_band_frames[][4];
extern const uint16_t wiggle_band_durations[];
extern const uint16_t wiggle_band_fade_durs[];
extern const band_animation_t wiggle_band;
extern const band_animation_t *wiggle_anim_set[1];
// frames for the band:
extern const rgbcolor_t zflag_bear_band_frames[][4];
extern const uint16_t zflag_bear_band_durations[];
extern const uint16_t zflag_bear_band_fade_durs[];
extern const band_animation_t zflag_bear_band;
extern const band_animation_t *zflag_bear_anim_set[1];
// frames for the band:
extern const rgbcolor_t zflag_bi_band_frames[][4];
extern const uint16_t zflag_bi_band_durations[];
extern const uint16_t zflag_bi_band_fade_durs[];
extern const band_animation_t zflag_bi_band;
extern const band_animation_t *zflag_bi_anim_set[1];
// frames for the band:
extern const rgbcolor_t zflag_leather_band_frames[][4];
extern const uint16_t zflag_leather_band_durations[];
extern const uint16_t zflag_leather_band_fade_durs[];
extern const band_animation_t zflag_leather_band;
extern const band_animation_t *zflag_leather_anim_set[1];
// frames for the band:
extern const rgbcolor_t zflag_trans_band_frames[][4];
extern const uint16_t zflag_trans_band_durations[];
extern const uint16_t zflag_trans_band_fade_durs[];
extern const band_animation_t zflag_trans_band;
extern const band_animation_t *zflag_trans_anim_set[1];
#define HEAD_ANIM_COUNT 11
#define HEAD_ANIM_COUNT_INCL_META 14
#define HEAD_ANIM_FIRE 0
#define HEAD_ANIM_GEEK_GIRL 1
#define HEAD_ANIM_ICE 2
#define HEAD_ANIM_LAGOON 3
#define HEAD_ANIM_PAN 4
#define HEAD_ANIM_RAINBOW 5
#define HEAD_ANIM_WIGGLE 6
#define HEAD_ANIM_ZFLAG_BEAR 7
#define HEAD_ANIM_ZFLAG_BI 8
#define HEAD_ANIM_ZFLAG_LEATHER 9
#define HEAD_ANIM_ZFLAG_TRANS 10
#define HEAD_ANIM_META_BOOP 11
#define HEAD_ANIM_META_NEWPAIR 12
#define HEAD_ANIM_META_PAIR 13
#define ANIM_TYPE_FASTTWINKLE 0
#define ANIM_TYPE_SOLID 1
#define ANIM_TYPE_SLOWTWINKLE 2
#define LEG_ANIM_TYPE_COUNT 3
extern const band_animation_t **legs_all_anim_sets[];
#endif // _H_
