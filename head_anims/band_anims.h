#ifndef BANDANIMS_H_
#define BANDANIMS_H_

#include "leds.h"

#define LEG_CAMO_INDEX 0
#define LEG_INK_INDEX 1
#define LEG_DOUBLEINK_INDEX 2
#define LEG_ANIM_TYPE_NONE 201
#define LEG_ANIM_NONE 211

// frames for camo
extern const rgbcolor_t def_camo_frames[][4];
extern uint16_t def_camo_durations[];
extern uint16_t def_camo_fade_durs[];
extern const band_animation_t def_camo;
extern const band_animation_t *def_anim_set[3];
// frames for camo
extern const rgbcolor_t fire_camo_frames[][4];
extern uint16_t fire_camo_durations[];
extern uint16_t fire_camo_fade_durs[];
extern const band_animation_t fire_camo;
extern const band_animation_t *fire_anim_set[3];
// frames for camo
extern const rgbcolor_t geek_girl_camo_frames[][4];
extern uint16_t geek_girl_camo_durations[];
extern uint16_t geek_girl_camo_fade_durs[];
extern const band_animation_t geek_girl_camo;
extern const band_animation_t *geek_girl_anim_set[3];
// frames for camo
extern const rgbcolor_t rainbow_camo_frames[][4];
extern uint16_t rainbow_camo_durations[];
extern uint16_t rainbow_camo_fade_durs[];
extern const band_animation_t rainbow_camo;
extern const band_animation_t *rainbow_anim_set[3];
// frames for camo
extern const rgbcolor_t zflag_bear_camo_frames[][4];
extern uint16_t zflag_bear_camo_durations[];
extern uint16_t zflag_bear_camo_fade_durs[];
extern const band_animation_t zflag_bear_camo;
extern const band_animation_t *zflag_bear_anim_set[3];
// frames for camo
extern const rgbcolor_t zflag_bi_camo_frames[][4];
extern uint16_t zflag_bi_camo_durations[];
extern uint16_t zflag_bi_camo_fade_durs[];
extern const band_animation_t zflag_bi_camo;
extern const band_animation_t *zflag_bi_anim_set[3];
// frames for camo
extern const rgbcolor_t zflag_leather_camo_frames[][4];
extern uint16_t zflag_leather_camo_durations[];
extern uint16_t zflag_leather_camo_fade_durs[];
extern const band_animation_t zflag_leather_camo;
extern const band_animation_t *zflag_leather_anim_set[3];
// frames for camo
extern const rgbcolor_t zflag_trans_camo_frames[][4];
extern uint16_t zflag_trans_camo_durations[];
extern uint16_t zflag_trans_camo_fade_durs[];
extern const band_animation_t zflag_trans_camo;
extern const band_animation_t *zflag_trans_anim_set[3];
#define HEAD_ANIM_COUNT 8
#define HEAD_ANIM_COUNT_INCL_META 8
#define HEAD_ANIM_DEF 0
#define HEAD_ANIM_FIRE 1
#define HEAD_ANIM_GEEK_GIRL 2
#define HEAD_ANIM_RAINBOW 3
#define HEAD_ANIM_ZFLAG_BEAR 4
#define HEAD_ANIM_ZFLAG_BI 5
#define HEAD_ANIM_ZFLAG_LEATHER 6
#define HEAD_ANIM_ZFLAG_TRANS 7
#define ANIM_TYPE_SLOWTWINKLE 0
#define ANIM_TYPE_SOLID 1
#define ANIM_TYPE_FASTTWINKLE 2
#define ANIM_TYPE_HARDTWINKLE 3
#define LEG_ANIM_TYPE_COUNT 4
extern const band_animation_t **legs_all_anim_sets[];
#endif // _H_
extern const rgbcolor_t sprays[];
