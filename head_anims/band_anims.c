#include "leds.h"
#include "band_anims.h"

///////////////// FIRE:
// frames for the band:
const rgbcolor_t fire_band_frames[][4] = {
    {{0xff, 0x0, 0x0}, {0xff, 0x22, 0x0}, {0xff, 0x46, 0x0}, {0xff, 0x0, 0x0}},
    {{0xff, 0x22, 0x0}, {0xff, 0x46, 0x0}, {0xff, 0x22, 0x0}, {0xff, 0x46, 0x0}},
    {{0xff, 0x46, 0x0}, {0xff, 0x0, 0x0}, {0xff, 0x46, 0x0}, {0xff, 0x22, 0x0}},
    {{0xff, 0x0, 0x0}, {0xff, 0x46, 0x0}, {0xff, 0x22, 0x0}, {0xff, 0x46, 0x0}},
    {{0xff, 0x46, 0x0}, {0xff, 0x22, 0x0}, {0xff, 0x0, 0x0}, {0xff, 0x22, 0x0}},
};
const uint16_t fire_band_durations[] = {100, 100, 100, 100, 100};
const uint16_t fire_band_fade_durs[] = {50, 50, 50, 50, 50};
// the animation:
const band_animation_t fire_band = {fire_band_frames, fire_band_durations, fire_band_fade_durs, 5, ANIM_TYPE_FASTTWINKLE, 8};

const band_animation_t *fire_anim_set[1] = {&fire_band};

///////////////// GEEK_GIRL:
// frames for the band:
const rgbcolor_t geek_girl_band_frames[][4] = {
    {{0xf0, 0x14, 0x3c}, {0x0, 0x40, 0x0}, {0x0, 0x40, 0x0}, {0xf0, 0x14, 0x3c}},
    {{0x0, 0x40, 0x0}, {0xf0, 0x14, 0x3c}, {0xf0, 0x14, 0x3c}, {0x0, 0x40, 0x0}},
};
const uint16_t geek_girl_band_durations[] = {400, 400};
const uint16_t geek_girl_band_fade_durs[] = {200, 200};
// the animation:
const band_animation_t geek_girl_band = {geek_girl_band_frames, geek_girl_band_durations, geek_girl_band_fade_durs, 2, ANIM_TYPE_SOLID, 5};

const band_animation_t *geek_girl_anim_set[1] = {&geek_girl_band};

///////////////// META_BOOP:
// frames for the band:
const rgbcolor_t meta_boop_band_frames[][4] = {
    {{0x22, 0x45, 0x22}, {0xda, 0x52, 0x20}, {0xff, 0x22, 0x0}, {0xb2, 0x11, 0x22}},
    {{0x22, 0x45, 0x22}, {0x20, 0x59, 0xaa}, {0x80, 0x0, 0x80}, {0xb2, 0x11, 0x22}},
    {{0xff, 0x22, 0x0}, {0xda, 0x52, 0x20}, {0x22, 0x45, 0x22}, {0x20, 0x59, 0xaa}},
    {{0xb2, 0x11, 0x22}, {0x22, 0x45, 0x22}, {0x20, 0x59, 0xaa}, {0x80, 0x0, 0x80}},
    {{0x80, 0x0, 0x80}, {0x22, 0x45, 0x22}, {0xff, 0x22, 0x0}, {0xb2, 0x11, 0x22}},
    {{0x22, 0x45, 0x22}, {0xda, 0x52, 0x20}, {0xff, 0x22, 0x0}, {0xb2, 0x11, 0x22}},
    {{0x22, 0x45, 0x22}, {0x20, 0x59, 0xaa}, {0x80, 0x0, 0x80}, {0xb2, 0x11, 0x22}},
    {{0xff, 0x22, 0x0}, {0xda, 0x52, 0x20}, {0x22, 0x45, 0x22}, {0x20, 0x59, 0xaa}},
    {{0xb2, 0x11, 0x22}, {0x22, 0x45, 0x22}, {0x20, 0x59, 0xaa}, {0x80, 0x0, 0x80}},
    {{0x80, 0x0, 0x80}, {0x22, 0x45, 0x22}, {0xff, 0x22, 0x0}, {0xb2, 0x11, 0x22}},
    {{0x22, 0x45, 0x22}, {0xda, 0x52, 0x20}, {0xff, 0x22, 0x0}, {0xb2, 0x11, 0x22}},
    {{0x22, 0x45, 0x22}, {0x20, 0x59, 0xaa}, {0x80, 0x0, 0x80}, {0xb2, 0x11, 0x22}},
    {{0xff, 0x22, 0x0}, {0xda, 0x52, 0x20}, {0x22, 0x45, 0x22}, {0x20, 0x59, 0xaa}},
    {{0xb2, 0x11, 0x22}, {0x22, 0x45, 0x22}, {0x20, 0x59, 0xaa}, {0x80, 0x0, 0x80}},
    {{0x80, 0x0, 0x80}, {0x22, 0x45, 0x22}, {0xff, 0x22, 0x0}, {0xb2, 0x11, 0x22}},
    {{0x22, 0x45, 0x22}, {0xda, 0x52, 0x20}, {0xff, 0x22, 0x0}, {0xb2, 0x11, 0x22}},
    {{0x22, 0x45, 0x22}, {0x20, 0x59, 0xaa}, {0x80, 0x0, 0x80}, {0xb2, 0x11, 0x22}},
    {{0xff, 0x22, 0x0}, {0xda, 0x52, 0x20}, {0x22, 0x45, 0x22}, {0x20, 0x59, 0xaa}},
    {{0xb2, 0x11, 0x22}, {0x22, 0x45, 0x22}, {0x20, 0x59, 0xaa}, {0x80, 0x0, 0x80}},
    {{0x80, 0x0, 0x80}, {0x22, 0x45, 0x22}, {0xff, 0x22, 0x0}, {0xb2, 0x11, 0x22}},
    {{0x22, 0x45, 0x22}, {0xda, 0x52, 0x20}, {0xff, 0x22, 0x0}, {0xb2, 0x11, 0x22}},
    {{0x22, 0x45, 0x22}, {0x20, 0x59, 0xaa}, {0x80, 0x0, 0x80}, {0xb2, 0x11, 0x22}},
    {{0xff, 0x22, 0x0}, {0xda, 0x52, 0x20}, {0x22, 0x45, 0x22}, {0x20, 0x59, 0xaa}},
    {{0xb2, 0x11, 0x22}, {0x22, 0x45, 0x22}, {0x20, 0x59, 0xaa}, {0x80, 0x0, 0x80}},
    {{0x80, 0x0, 0x80}, {0x22, 0x45, 0x22}, {0xff, 0x22, 0x0}, {0xb2, 0x11, 0x22}},
    {{0x22, 0x45, 0x22}, {0x0, 0x0, 0x0}, {0xff, 0x22, 0x0}, {0xb2, 0x11, 0x22}},
    {{0x22, 0x45, 0x22}, {0x0, 0x0, 0x0}, {0x80, 0x0, 0x80}, {0x0, 0x0, 0x0}},
    {{0xff, 0x22, 0x0}, {0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}},
    {{0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}},
};
const uint16_t meta_boop_band_durations[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1000};
const uint16_t meta_boop_band_fade_durs[] = {45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 1000};
// the animation:
const band_animation_t meta_boop_band = {meta_boop_band_frames, meta_boop_band_durations, meta_boop_band_fade_durs, 29, ANIM_TYPE_SOLID, 1};

const band_animation_t *meta_boop_anim_set[1] = {&meta_boop_band};

///////////////// RAINBOW:
// frames for the band:
const rgbcolor_t rainbow_band_frames[][4] = {
    {{0xff, 0x0, 0x0}, {0xff, 0x52, 0x0}, {0xff, 0x7f, 0x0}, {0x0, 0x40, 0x0}},
    {{0x80, 0x0, 0x80}, {0xff, 0x0, 0x0}, {0xff, 0x52, 0x0}, {0xff, 0x7f, 0x0}},
    {{0x0, 0x0, 0xff}, {0x80, 0x0, 0x80}, {0xff, 0x0, 0x0}, {0xff, 0x52, 0x0}},
    {{0x0, 0x40, 0x0}, {0x0, 0x0, 0xff}, {0x80, 0x0, 0x80}, {0xff, 0x0, 0x0}},
    {{0xff, 0x7f, 0x0}, {0x0, 0x40, 0x0}, {0x0, 0x0, 0xff}, {0x80, 0x0, 0x80}},
    {{0xff, 0x52, 0x0}, {0xff, 0x7f, 0x0}, {0x0, 0x40, 0x0}, {0x0, 0x0, 0xff}},
};
const uint16_t rainbow_band_durations[] = {100, 100, 100, 100, 100, 100};
const uint16_t rainbow_band_fade_durs[] = {150, 150, 150, 150, 150, 150};
// the animation:
const band_animation_t rainbow_band = {rainbow_band_frames, rainbow_band_durations, rainbow_band_fade_durs, 6, ANIM_TYPE_SOLID, 4};

const band_animation_t *rainbow_anim_set[1] = {&rainbow_band};

///////////////// ZFLAG_BEAR:
// frames for the band:
const rgbcolor_t zflag_bear_band_frames[][4] = {
    {{0xc5, 0x20, 0x4}, {0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}, {0xc5, 0x20, 0x4}},
    {{0xc5, 0x20, 0x4}, {0xc5, 0x20, 0x4}, {0xc5, 0x20, 0x4}, {0xc5, 0x20, 0x4}},
    {{0xd5, 0x63, 0x0}, {0xc5, 0x20, 0x4}, {0xc5, 0x20, 0x4}, {0xd5, 0x63, 0x0}},
    {{0xd5, 0x63, 0x0}, {0xd5, 0x63, 0x0}, {0xd5, 0x63, 0x0}, {0xd5, 0x63, 0x0}},
    {{0xd5, 0x63, 0x0}, {0xd5, 0x63, 0x0}, {0xd5, 0x63, 0x0}, {0xd5, 0x63, 0x0}},
    {{0xc5, 0x20, 0x4}, {0xd5, 0x63, 0x0}, {0xd5, 0x63, 0x0}, {0xc5, 0x20, 0x4}},
    {{0x0, 0x0, 0x0}, {0xc5, 0x20, 0x4}, {0xc5, 0x20, 0x4}, {0x0, 0x0, 0x0}},
    {{0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}},
};
const uint16_t zflag_bear_band_durations[] = {50, 50, 50, 50, 50, 50, 50, 50};
const uint16_t zflag_bear_band_fade_durs[] = {180, 180, 180, 180, 180, 180, 180, 180};
// the animation:
const band_animation_t zflag_bear_band = {zflag_bear_band_frames, zflag_bear_band_durations, zflag_bear_band_fade_durs, 8, ANIM_TYPE_SOLID, 3};

const band_animation_t *zflag_bear_anim_set[1] = {&zflag_bear_band};

///////////////// ZFLAG_BI:
// frames for the band:
const rgbcolor_t zflag_bi_band_frames[][4] = {
    {{0xff, 0x0, 0xb0}, {0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}},
    {{0xff, 0x0, 0xb0}, {0xff, 0x0, 0xb0}, {0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}},
    {{0xff, 0x0, 0xb0}, {0xff, 0x0, 0xb0}, {0xff, 0x0, 0xb0}, {0x0, 0x0, 0x0}},
    {{0x50, 0x0, 0xff}, {0xff, 0x0, 0xb0}, {0xff, 0x0, 0xb0}, {0xff, 0x0, 0xb0}},
    {{0x50, 0x0, 0xff}, {0x50, 0x0, 0xff}, {0xff, 0x0, 0xb0}, {0xff, 0x0, 0xb0}},
    {{0x0, 0x0, 0xff}, {0x50, 0x0, 0xff}, {0x50, 0x0, 0xff}, {0xff, 0x0, 0xb0}},
    {{0x0, 0x0, 0xff}, {0x0, 0x0, 0xff}, {0x50, 0x0, 0xff}, {0x50, 0x0, 0xff}},
    {{0x0, 0x0, 0x0}, {0x0, 0x0, 0xff}, {0x0, 0x0, 0xff}, {0x0, 0x0, 0xff}},
    {{0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}, {0x0, 0x0, 0xff}, {0x0, 0x0, 0xff}},
    {{0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}, {0x0, 0x0, 0xff}},
};
const uint16_t zflag_bi_band_durations[] = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50};
const uint16_t zflag_bi_band_fade_durs[] = {180, 180, 180, 180, 180, 180, 180, 180, 180, 180};
// the animation:
const band_animation_t zflag_bi_band = {zflag_bi_band_frames, zflag_bi_band_durations, zflag_bi_band_fade_durs, 10, ANIM_TYPE_SLOWTWINKLE, 2};

const band_animation_t *zflag_bi_anim_set[1] = {&zflag_bi_band};

///////////////// ZFLAG_LEATHER:
// frames for the band:
const rgbcolor_t zflag_leather_band_frames[][4] = {
    {{0x0, 0x0, 0xff}, {0x0, 0x0, 0xff}, {0xff, 0x0, 0x0}, {0x0, 0x0, 0xff}},
    {{0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}, {0xff, 0x0, 0x0}, {0x0, 0x0, 0x0}},
    {{0x0, 0x0, 0xff}, {0x0, 0x0, 0xff}, {0xf, 0x0, 0x0}, {0x0, 0x0, 0xff}},
    {{0x0, 0x0, 0xff}, {0x0, 0x0, 0xff}, {0xf, 0x0, 0x0}, {0x0, 0x0, 0xff}},
    {{0xff, 0x80, 0xff}, {0xff, 0x80, 0xff}, {0xf, 0x0, 0x0}, {0xff, 0x80, 0xff}},
    {{0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}, {0xff, 0x0, 0x0}, {0x0, 0x0, 0x0}},
};
const uint16_t zflag_leather_band_durations[] = {200, 200, 200, 200, 200, 200};
const uint16_t zflag_leather_band_fade_durs[] = {500, 500, 500, 500, 500, 500};
// the animation:
const band_animation_t zflag_leather_band = {zflag_leather_band_frames, zflag_leather_band_durations, zflag_leather_band_fade_durs, 6, ANIM_TYPE_SOLID, 1};

const band_animation_t *zflag_leather_anim_set[1] = {&zflag_leather_band};

///////////////// ZFLAG_TRANS:
// frames for the band:
const rgbcolor_t zflag_trans_band_frames[][4] = {
    {{0x0, 0x5f, 0xff}, {0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}, {0x0, 0x5f, 0xff}},
    {{0xf0, 0x14, 0x3c}, {0x0, 0x5f, 0xff}, {0x0, 0x5f, 0xff}, {0xf0, 0x14, 0x3c}},
    {{0xff, 0x80, 0xff}, {0xf0, 0x14, 0x3c}, {0xf0, 0x14, 0x3c}, {0xff, 0x80, 0xff}},
    {{0xf0, 0x14, 0x3c}, {0xff, 0x80, 0xff}, {0xff, 0x80, 0xff}, {0xf0, 0x14, 0x3c}},
    {{0x0, 0x5f, 0xff}, {0xf0, 0x14, 0x3c}, {0xf0, 0x14, 0x3c}, {0x0, 0x5f, 0xff}},
    {{0x0, 0x0, 0x0}, {0x0, 0x5f, 0xff}, {0x0, 0x5f, 0xff}, {0x0, 0x0, 0x0}},
    {{0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}},
};
const uint16_t zflag_trans_band_durations[] = {150, 150, 150, 150, 150, 150, 150};
const uint16_t zflag_trans_band_fade_durs[] = {140, 140, 140, 140, 140, 140, 140};
// the animation:
const band_animation_t zflag_trans_band = {zflag_trans_band_frames, zflag_trans_band_durations, zflag_trans_band_fade_durs, 7, ANIM_TYPE_SOLID, 2};

const band_animation_t *zflag_trans_anim_set[1] = {&zflag_trans_band};

const band_animation_t **legs_all_anim_sets[] = {fire_anim_set, geek_girl_anim_set, rainbow_anim_set, zflag_bear_anim_set, zflag_bi_anim_set, zflag_leather_anim_set, zflag_trans_anim_set, meta_boop_anim_set};
