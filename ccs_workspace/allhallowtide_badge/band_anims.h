#ifndef BANDANIMS_H_
#define BANDANIMS_H_

#include "leds.h"

#define LEG_CAMO_INDEX 0
#define LEG_INK_INDEX 1
#define LEG_DOUBLEINK_INDEX 2
#define LEG_ANIM_TYPE_NONE 201
#define LEG_ANIM_NONE 211
#define LEG_ANIM_TYPE_COUNT 1

// frames for camo
extern const rgbcolor_t def_camo_frames[][4];
extern uint16_t def_camo_durations[];
extern uint16_t def_camo_fade_durs[];
extern const band_animation_t def_camo;
extern const band_animation_t *def_anim_set[3];
#define HEAD_ANIM_COUNT 1
#define HEAD_ANIM_COUNT_INCL_META 1
#define HEAD_ANIM_DEF 0
#define ANIM_TYPE_SOLID 0
#define ANIM_TYPE_FASTTWINKLE 202
#define ANIM_TYPE_SLOWTWINKLE 203
#define ANIM_TYPE_HARDTWINKLE 204

extern const band_animation_t **legs_all_anim_sets[];
#endif // _H_
extern const rgbcolor_t sprays[];
