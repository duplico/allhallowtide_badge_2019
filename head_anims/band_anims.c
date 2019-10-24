#include "leds.h"
#include "band_anims.h"

///////////////// DEF:
// frames for camo
const rgbcolor_t def_camo_frames[][4] = {
    {{0x78, 0x2d0, 0x216}, {0x78, 0x2d0, 0x216}, {0x78, 0x2d0, 0x216}, {0x78, 0x2d0, 0x216}},
};
uint16_t def_camo_durations[] = {500};
uint16_t def_camo_fade_durs[] = {0};
// the animation:
const band_animation_t def_camo = {def_camo_frames, def_camo_durations, def_camo_fade_durs, 1, ANIM_TYPE_SOLID, 1, 12};

const band_animation_t *def_anim_set[3] = {&def_camo};

const band_animation_t **legs_all_anim_sets[] = {def_anim_set};
const rgbcolor_t sprays[1] = {{0x78, 0x2d0, 0x216}};
