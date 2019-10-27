#ifndef BANDANIMS_H_
#define BANDANIMS_H_

#include "leds.h"

#define LEG_CAMO_INDEX 0
#define LEG_INK_INDEX 1
#define LEG_DOUBLEINK_INDEX 2
#define LEG_ANIM_TYPE_NONE 201
#define LEG_ANIM_NONE 211

// frames for the band:
extern const rgbcolor_t def_band_frames[][4];
extern uint16_t def_band_durations[];
extern uint16_t def_band_fade_durs[];
extern const band_animation_t def_band;
extern const band_animation_t *def_anim_set[1];
// frames for the band:
extern const rgbcolor_t fire_band_frames[][4];
extern uint16_t fire_band_durations[];
extern uint16_t fire_band_fade_durs[];
extern const band_animation_t fire_band;
extern const band_animation_t *fire_anim_set[1];
// frames for the band:
extern const rgbcolor_t geek_girl_band_frames[][4];
extern uint16_t geek_girl_band_durations[];
extern uint16_t geek_girl_band_fade_durs[];
extern const band_animation_t geek_girl_band;
extern const band_animation_t *geek_girl_anim_set[1];
// frames for the band:
extern const rgbcolor_t meta_boop_band_frames[][4];
extern uint16_t meta_boop_band_durations[];
extern uint16_t meta_boop_band_fade_durs[];
extern const band_animation_t meta_boop_band;
extern const band_animation_t *meta_boop_anim_set[1];
// frames for the band:
extern const rgbcolor_t rainbow_band_frames[][4];
extern uint16_t rainbow_band_durations[];
extern uint16_t rainbow_band_fade_durs[];
extern const band_animation_t rainbow_band;
extern const band_animation_t *rainbow_anim_set[1];
// frames for the band:
extern const rgbcolor_t zflag_bear_band_frames[][4];
extern uint16_t zflag_bear_band_durations[];
extern uint16_t zflag_bear_band_fade_durs[];
extern const band_animation_t zflag_bear_band;
extern const band_animation_t *zflag_bear_anim_set[1];
// frames for the band:
extern const rgbcolor_t zflag_bi_band_frames[][4];
extern uint16_t zflag_bi_band_durations[];
extern uint16_t zflag_bi_band_fade_durs[];
extern const band_animation_t zflag_bi_band;
extern const band_animation_t *zflag_bi_anim_set[1];
// frames for the band:
extern const rgbcolor_t zflag_leather_band_frames[][4];
extern uint16_t zflag_leather_band_durations[];
extern uint16_t zflag_leather_band_fade_durs[];
extern const band_animation_t zflag_leather_band;
extern const band_animation_t *zflag_leather_anim_set[1];
// frames for the band:
extern const rgbcolor_t zflag_trans_band_frames[][4];
extern uint16_t zflag_trans_band_durations[];
extern uint16_t zflag_trans_band_fade_durs[];
extern const band_animation_t zflag_trans_band;
extern const band_animation_t *zflag_trans_anim_set[1];
#define HEAD_ANIM_COUNT 8
#define HEAD_ANIM_COUNT_INCL_META 9
#define HEAD_ANIM_DEF 0
#define HEAD_ANIM_FIRE 1
#define HEAD_ANIM_GEEK_GIRL 2
#define HEAD_ANIM_RAINBOW 3
#define HEAD_ANIM_ZFLAG_BEAR 4
#define HEAD_ANIM_ZFLAG_BI 5
#define HEAD_ANIM_ZFLAG_LEATHER 6
#define HEAD_ANIM_ZFLAG_TRANS 7
#define HEAD_ANIM_META_BOOP 8
#define ANIM_TYPE_SOLID 0
#define ANIM_TYPE_FASTTWINKLE 1
#define ANIM_TYPE_SLOWTWINKLE 2
#define LEG_ANIM_TYPE_COUNT 3
extern const band_animation_t **legs_all_anim_sets[];
#endif // _H_
extern const rgbcolor_t sprays[];
