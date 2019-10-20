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
extern const rgbcolor_t found_camo_frames[][4];
extern uint16_t found_camo_durations[];
extern uint16_t found_camo_fade_durs[];
extern const band_animation_t found_camo;
extern const band_animation_t *found_anim_set[3];
// frames for camo
extern const rgbcolor_t gamer_camo_frames[][4];
extern uint16_t gamer_camo_durations[];
extern uint16_t gamer_camo_fade_durs[];
extern const band_animation_t gamer_camo;
extern const band_animation_t *gamer_anim_set[3];
// frames for camo
extern const rgbcolor_t geek_girl_camo_frames[][4];
extern uint16_t geek_girl_camo_durations[];
extern uint16_t geek_girl_camo_fade_durs[];
extern const band_animation_t geek_girl_camo;
extern const band_animation_t *geek_girl_anim_set[3];
// frames for camo
extern const rgbcolor_t learned_camo_frames[][4];
extern uint16_t learned_camo_durations[];
extern uint16_t learned_camo_fade_durs[];
extern const band_animation_t learned_camo;
extern const band_animation_t *learned_anim_set[3];
// frames for camo
extern const rgbcolor_t lush_camo_frames[][4];
extern uint16_t lush_camo_durations[];
extern uint16_t lush_camo_fade_durs[];
extern const band_animation_t lush_camo;
extern const band_animation_t *lush_anim_set[3];
// frames for camo
extern const rgbcolor_t mixologist_camo_frames[][4];
extern uint16_t mixologist_camo_durations[];
extern uint16_t mixologist_camo_fade_durs[];
extern const band_animation_t mixologist_camo;
extern const band_animation_t *mixologist_anim_set[3];
// frames for camo
extern const rgbcolor_t poolparty_camo_frames[][4];
extern uint16_t poolparty_camo_durations[];
extern uint16_t poolparty_camo_fade_durs[];
extern const band_animation_t poolparty_camo;
extern const band_animation_t *poolparty_anim_set[3];
// frames for camo
extern const rgbcolor_t pushover_camo_frames[][4];
extern uint16_t pushover_camo_durations[];
extern uint16_t pushover_camo_fade_durs[];
extern const band_animation_t pushover_camo;
extern const band_animation_t *pushover_anim_set[3];
// frames for camo
extern const rgbcolor_t wrapup_3_camo_frames[][4];
extern uint16_t wrapup_3_camo_durations[];
extern uint16_t wrapup_3_camo_fade_durs[];
extern const band_animation_t wrapup_3_camo;
extern const band_animation_t *wrapup_3_anim_set[3];
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
#define HEAD_ANIM_COUNT 15
#define HEAD_ANIM_COUNT_INCL_META 15
#define HEAD_ANIM_DEF 0
#define HEAD_ANIM_FIRE 1
#define HEAD_ANIM_FOUND 2
#define HEAD_ANIM_GAMER 3
#define HEAD_ANIM_GEEK_GIRL 4
#define HEAD_ANIM_LEARNED 5
#define HEAD_ANIM_LUSH 6
#define HEAD_ANIM_MIXOLOGIST 7
#define HEAD_ANIM_POOLPARTY 8
#define HEAD_ANIM_PUSHOVER 9
#define HEAD_ANIM_WRAPUP_3 10
#define HEAD_ANIM_ZFLAG_BEAR 11
#define HEAD_ANIM_ZFLAG_BI 12
#define HEAD_ANIM_ZFLAG_LEATHER 13
#define HEAD_ANIM_ZFLAG_TRANS 14
#define ANIM_TYPE_SOLID 0
#define ANIM_TYPE_FASTTWINKLE 1
#define ANIM_TYPE_HARDTWINKLE 2
#define ANIM_TYPE_SLOWTWINKLE 3
#define ANIM_TYPE_SOFTTWINKLE 4
#define LEG_ANIM_TYPE_COUNT 5
extern const band_animation_t **legs_all_anim_sets[];
#endif // _H_
extern const rgbcolor_t sprays[];
