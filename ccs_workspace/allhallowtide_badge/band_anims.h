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
// frames for boop
extern const rgbcolor_t def_boop_frames[][4];
extern uint16_t def_boop_durations[];
extern uint16_t def_boop_fade_durs[];
extern const band_animation_t def_boop;
// frames for bigboop
extern const rgbcolor_t def_bigboop_frames[][4];
extern uint16_t def_bigboop_durations[];
extern uint16_t def_bigboop_fade_durs[];
extern const band_animation_t def_bigboop;
extern const band_animation_t *def_anim_set[3];
// frames for camo
extern const rgbcolor_t doubleink_camo_frames[][4];
extern uint16_t doubleink_camo_durations[];
extern uint16_t doubleink_camo_fade_durs[];
extern const band_animation_t doubleink_camo;
// frames for boop
extern const rgbcolor_t doubleink_boop_frames[][4];
extern uint16_t doubleink_boop_durations[];
extern uint16_t doubleink_boop_fade_durs[];
extern const band_animation_t doubleink_boop;
// frames for bigboop
extern const rgbcolor_t doubleink_bigboop_frames[][4];
extern uint16_t doubleink_bigboop_durations[];
extern uint16_t doubleink_bigboop_fade_durs[];
extern const band_animation_t doubleink_bigboop;
extern const band_animation_t *doubleink_anim_set[3];
// frames for camo
extern const rgbcolor_t fire_camo_frames[][4];
extern uint16_t fire_camo_durations[];
extern uint16_t fire_camo_fade_durs[];
extern const band_animation_t fire_camo;
// frames for boop
extern const rgbcolor_t fire_boop_frames[][4];
extern uint16_t fire_boop_durations[];
extern uint16_t fire_boop_fade_durs[];
extern const band_animation_t fire_boop;
// frames for bigboop
extern const rgbcolor_t fire_bigboop_frames[][4];
extern uint16_t fire_bigboop_durations[];
extern uint16_t fire_bigboop_fade_durs[];
extern const band_animation_t fire_bigboop;
extern const band_animation_t *fire_anim_set[3];
// frames for camo
extern const rgbcolor_t found_camo_frames[][4];
extern uint16_t found_camo_durations[];
extern uint16_t found_camo_fade_durs[];
extern const band_animation_t found_camo;
// frames for boop
extern const rgbcolor_t found_boop_frames[][4];
extern uint16_t found_boop_durations[];
extern uint16_t found_boop_fade_durs[];
extern const band_animation_t found_boop;
// frames for bigboop
extern const rgbcolor_t found_bigboop_frames[][4];
extern uint16_t found_bigboop_durations[];
extern uint16_t found_bigboop_fade_durs[];
extern const band_animation_t found_bigboop;
extern const band_animation_t *found_anim_set[3];
// frames for camo
extern const rgbcolor_t gamer_camo_frames[][4];
extern uint16_t gamer_camo_durations[];
extern uint16_t gamer_camo_fade_durs[];
extern const band_animation_t gamer_camo;
// frames for boop
extern const rgbcolor_t gamer_boop_frames[][4];
extern uint16_t gamer_boop_durations[];
extern uint16_t gamer_boop_fade_durs[];
extern const band_animation_t gamer_boop;
// frames for bigboop
extern const rgbcolor_t gamer_bigboop_frames[][4];
extern uint16_t gamer_bigboop_durations[];
extern uint16_t gamer_bigboop_fade_durs[];
extern const band_animation_t gamer_bigboop;
extern const band_animation_t *gamer_anim_set[3];
// frames for camo
extern const rgbcolor_t geek_girl_camo_frames[][4];
extern uint16_t geek_girl_camo_durations[];
extern uint16_t geek_girl_camo_fade_durs[];
extern const band_animation_t geek_girl_camo;
// frames for boop
extern const rgbcolor_t geek_girl_boop_frames[][4];
extern uint16_t geek_girl_boop_durations[];
extern uint16_t geek_girl_boop_fade_durs[];
extern const band_animation_t geek_girl_boop;
// frames for bigboop
extern const rgbcolor_t geek_girl_bigboop_frames[][4];
extern uint16_t geek_girl_bigboop_durations[];
extern uint16_t geek_girl_bigboop_fade_durs[];
extern const band_animation_t geek_girl_bigboop;
extern const band_animation_t *geek_girl_anim_set[3];
// frames for camo
extern const rgbcolor_t giver_camo_frames[][4];
extern uint16_t giver_camo_durations[];
extern uint16_t giver_camo_fade_durs[];
extern const band_animation_t giver_camo;
// frames for boop
extern const rgbcolor_t giver_boop_frames[][4];
extern uint16_t giver_boop_durations[];
extern uint16_t giver_boop_fade_durs[];
extern const band_animation_t giver_boop;
// frames for bigboop
extern const rgbcolor_t giver_bigboop_frames[][4];
extern uint16_t giver_bigboop_durations[];
extern uint16_t giver_bigboop_fade_durs[];
extern const band_animation_t giver_bigboop;
extern const band_animation_t *giver_anim_set[3];
// frames for camo
extern const rgbcolor_t glam_camo_frames[][4];
extern uint16_t glam_camo_durations[];
extern uint16_t glam_camo_fade_durs[];
extern const band_animation_t glam_camo;
// frames for boop
extern const rgbcolor_t glam_boop_frames[][4];
extern uint16_t glam_boop_durations[];
extern uint16_t glam_boop_fade_durs[];
extern const band_animation_t glam_boop;
// frames for bigboop
extern const rgbcolor_t glam_bigboop_frames[][4];
extern uint16_t glam_bigboop_durations[];
extern uint16_t glam_bigboop_fade_durs[];
extern const band_animation_t glam_bigboop;
extern const band_animation_t *glam_anim_set[3];
// frames for camo
extern const rgbcolor_t handler_camo_frames[][4];
extern uint16_t handler_camo_durations[];
extern uint16_t handler_camo_fade_durs[];
extern const band_animation_t handler_camo;
// frames for boop
extern const rgbcolor_t handler_boop_frames[][4];
extern uint16_t handler_boop_durations[];
extern uint16_t handler_boop_fade_durs[];
extern const band_animation_t handler_boop;
// frames for bigboop
extern const rgbcolor_t handler_bigboop_frames[][4];
extern uint16_t handler_bigboop_durations[];
extern uint16_t handler_bigboop_fade_durs[];
extern const band_animation_t handler_bigboop;
extern const band_animation_t *handler_anim_set[3];
// frames for camo
extern const rgbcolor_t human_hat_camo_frames[][4];
extern uint16_t human_hat_camo_durations[];
extern uint16_t human_hat_camo_fade_durs[];
extern const band_animation_t human_hat_camo;
// frames for boop
extern const rgbcolor_t human_hat_boop_frames[][4];
extern uint16_t human_hat_boop_durations[];
extern uint16_t human_hat_boop_fade_durs[];
extern const band_animation_t human_hat_boop;
// frames for bigboop
extern const rgbcolor_t human_hat_bigboop_frames[][4];
extern uint16_t human_hat_bigboop_durations[];
extern uint16_t human_hat_bigboop_fade_durs[];
extern const band_animation_t human_hat_bigboop;
extern const band_animation_t *human_hat_anim_set[3];
// frames for camo
extern const rgbcolor_t karatekid_camo_frames[][4];
extern uint16_t karatekid_camo_durations[];
extern uint16_t karatekid_camo_fade_durs[];
extern const band_animation_t karatekid_camo;
// frames for boop
extern const rgbcolor_t karatekid_boop_frames[][4];
extern uint16_t karatekid_boop_durations[];
extern uint16_t karatekid_boop_fade_durs[];
extern const band_animation_t karatekid_boop;
// frames for bigboop
extern const rgbcolor_t karatekid_bigboop_frames[][4];
extern uint16_t karatekid_bigboop_durations[];
extern uint16_t karatekid_bigboop_fade_durs[];
extern const band_animation_t karatekid_bigboop;
extern const band_animation_t *karatekid_anim_set[3];
// frames for camo
extern const rgbcolor_t learned_camo_frames[][4];
extern uint16_t learned_camo_durations[];
extern uint16_t learned_camo_fade_durs[];
extern const band_animation_t learned_camo;
// frames for boop
extern const rgbcolor_t learned_boop_frames[][4];
extern uint16_t learned_boop_durations[];
extern uint16_t learned_boop_fade_durs[];
extern const band_animation_t learned_boop;
// frames for bigboop
extern const rgbcolor_t learned_bigboop_frames[][4];
extern uint16_t learned_bigboop_durations[];
extern uint16_t learned_bigboop_fade_durs[];
extern const band_animation_t learned_bigboop;
extern const band_animation_t *learned_anim_set[3];
// frames for camo
extern const rgbcolor_t lush_camo_frames[][4];
extern uint16_t lush_camo_durations[];
extern uint16_t lush_camo_fade_durs[];
extern const band_animation_t lush_camo;
// frames for boop
extern const rgbcolor_t lush_boop_frames[][4];
extern uint16_t lush_boop_durations[];
extern uint16_t lush_boop_fade_durs[];
extern const band_animation_t lush_boop;
// frames for bigboop
extern const rgbcolor_t lush_bigboop_frames[][4];
extern uint16_t lush_bigboop_durations[];
extern uint16_t lush_bigboop_fade_durs[];
extern const band_animation_t lush_bigboop;
extern const band_animation_t *lush_anim_set[3];
// frames for camo
extern const rgbcolor_t meta_social_camo_frames[][4];
extern uint16_t meta_social_camo_durations[];
extern uint16_t meta_social_camo_fade_durs[];
extern const band_animation_t meta_social_camo;
// frames for boop
extern const rgbcolor_t meta_social_boop_frames[][4];
extern uint16_t meta_social_boop_durations[];
extern uint16_t meta_social_boop_fade_durs[];
extern const band_animation_t meta_social_boop;
// frames for bigboop
extern const rgbcolor_t meta_social_bigboop_frames[][4];
extern uint16_t meta_social_bigboop_durations[];
extern uint16_t meta_social_bigboop_fade_durs[];
extern const band_animation_t meta_social_bigboop;
extern const band_animation_t *meta_social_anim_set[3];
// frames for camo
extern const rgbcolor_t meta_wakeup_camo_frames[][4];
extern uint16_t meta_wakeup_camo_durations[];
extern uint16_t meta_wakeup_camo_fade_durs[];
extern const band_animation_t meta_wakeup_camo;
// frames for boop
extern const rgbcolor_t meta_wakeup_boop_frames[][4];
extern uint16_t meta_wakeup_boop_durations[];
extern uint16_t meta_wakeup_boop_fade_durs[];
extern const band_animation_t meta_wakeup_boop;
// frames for bigboop
extern const rgbcolor_t meta_wakeup_bigboop_frames[][4];
extern uint16_t meta_wakeup_bigboop_durations[];
extern uint16_t meta_wakeup_bigboop_fade_durs[];
extern const band_animation_t meta_wakeup_bigboop;
extern const band_animation_t *meta_wakeup_anim_set[3];
// frames for camo
extern const rgbcolor_t mixologist_camo_frames[][4];
extern uint16_t mixologist_camo_durations[];
extern uint16_t mixologist_camo_fade_durs[];
extern const band_animation_t mixologist_camo;
// frames for boop
extern const rgbcolor_t mixologist_boop_frames[][4];
extern uint16_t mixologist_boop_durations[];
extern uint16_t mixologist_boop_fade_durs[];
extern const band_animation_t mixologist_boop;
// frames for bigboop
extern const rgbcolor_t mixologist_bigboop_frames[][4];
extern uint16_t mixologist_bigboop_durations[];
extern uint16_t mixologist_bigboop_fade_durs[];
extern const band_animation_t mixologist_bigboop;
extern const band_animation_t *mixologist_anim_set[3];
// frames for camo
extern const rgbcolor_t partytime_camo_frames[][4];
extern uint16_t partytime_camo_durations[];
extern uint16_t partytime_camo_fade_durs[];
extern const band_animation_t partytime_camo;
// frames for boop
extern const rgbcolor_t partytime_boop_frames[][4];
extern uint16_t partytime_boop_durations[];
extern uint16_t partytime_boop_fade_durs[];
extern const band_animation_t partytime_boop;
// frames for bigboop
extern const rgbcolor_t partytime_bigboop_frames[][4];
extern uint16_t partytime_bigboop_durations[];
extern uint16_t partytime_bigboop_fade_durs[];
extern const band_animation_t partytime_bigboop;
extern const band_animation_t *partytime_anim_set[3];
// frames for camo
extern const rgbcolor_t poolparty_camo_frames[][4];
extern uint16_t poolparty_camo_durations[];
extern uint16_t poolparty_camo_fade_durs[];
extern const band_animation_t poolparty_camo;
// frames for boop
extern const rgbcolor_t poolparty_boop_frames[][4];
extern uint16_t poolparty_boop_durations[];
extern uint16_t poolparty_boop_fade_durs[];
extern const band_animation_t poolparty_boop;
// frames for bigboop
extern const rgbcolor_t poolparty_bigboop_frames[][4];
extern uint16_t poolparty_bigboop_durations[];
extern uint16_t poolparty_bigboop_fade_durs[];
extern const band_animation_t poolparty_bigboop;
extern const band_animation_t *poolparty_anim_set[3];
// frames for camo
extern const rgbcolor_t powerhungry_camo_frames[][4];
extern uint16_t powerhungry_camo_durations[];
extern uint16_t powerhungry_camo_fade_durs[];
extern const band_animation_t powerhungry_camo;
// frames for boop
extern const rgbcolor_t powerhungry_boop_frames[][4];
extern uint16_t powerhungry_boop_durations[];
extern uint16_t powerhungry_boop_fade_durs[];
extern const band_animation_t powerhungry_boop;
// frames for bigboop
extern const rgbcolor_t powerhungry_bigboop_frames[][4];
extern uint16_t powerhungry_bigboop_durations[];
extern uint16_t powerhungry_bigboop_fade_durs[];
extern const band_animation_t powerhungry_bigboop;
extern const band_animation_t *powerhungry_anim_set[3];
// frames for camo
extern const rgbcolor_t pushover_camo_frames[][4];
extern uint16_t pushover_camo_durations[];
extern uint16_t pushover_camo_fade_durs[];
extern const band_animation_t pushover_camo;
// frames for boop
extern const rgbcolor_t pushover_boop_frames[][4];
extern uint16_t pushover_boop_durations[];
extern uint16_t pushover_boop_fade_durs[];
extern const band_animation_t pushover_boop;
// frames for bigboop
extern const rgbcolor_t pushover_bigboop_frames[][4];
extern uint16_t pushover_bigboop_durations[];
extern uint16_t pushover_bigboop_fade_durs[];
extern const band_animation_t pushover_bigboop;
extern const band_animation_t *pushover_anim_set[3];
// frames for camo
extern const rgbcolor_t shutdown_camo_frames[][4];
extern uint16_t shutdown_camo_durations[];
extern uint16_t shutdown_camo_fade_durs[];
extern const band_animation_t shutdown_camo;
// frames for boop
extern const rgbcolor_t shutdown_boop_frames[][4];
extern uint16_t shutdown_boop_durations[];
extern uint16_t shutdown_boop_fade_durs[];
extern const band_animation_t shutdown_boop;
// frames for bigboop
extern const rgbcolor_t shutdown_bigboop_frames[][4];
extern uint16_t shutdown_bigboop_durations[];
extern uint16_t shutdown_bigboop_fade_durs[];
extern const band_animation_t shutdown_bigboop;
extern const band_animation_t *shutdown_anim_set[3];
// frames for camo
extern const rgbcolor_t uber_camo_frames[][4];
extern uint16_t uber_camo_durations[];
extern uint16_t uber_camo_fade_durs[];
extern const band_animation_t uber_camo;
// frames for boop
extern const rgbcolor_t uber_boop_frames[][4];
extern uint16_t uber_boop_durations[];
extern uint16_t uber_boop_fade_durs[];
extern const band_animation_t uber_boop;
// frames for bigboop
extern const rgbcolor_t uber_bigboop_frames[][4];
extern uint16_t uber_bigboop_durations[];
extern uint16_t uber_bigboop_fade_durs[];
extern const band_animation_t uber_bigboop;
extern const band_animation_t *uber_anim_set[3];
// frames for camo
extern const rgbcolor_t wrapup_1_camo_frames[][4];
extern uint16_t wrapup_1_camo_durations[];
extern uint16_t wrapup_1_camo_fade_durs[];
extern const band_animation_t wrapup_1_camo;
// frames for boop
extern const rgbcolor_t wrapup_1_boop_frames[][4];
extern uint16_t wrapup_1_boop_durations[];
extern uint16_t wrapup_1_boop_fade_durs[];
extern const band_animation_t wrapup_1_boop;
// frames for bigboop
extern const rgbcolor_t wrapup_1_bigboop_frames[][4];
extern uint16_t wrapup_1_bigboop_durations[];
extern uint16_t wrapup_1_bigboop_fade_durs[];
extern const band_animation_t wrapup_1_bigboop;
extern const band_animation_t *wrapup_1_anim_set[3];
// frames for camo
extern const rgbcolor_t wrapup_2_camo_frames[][4];
extern uint16_t wrapup_2_camo_durations[];
extern uint16_t wrapup_2_camo_fade_durs[];
extern const band_animation_t wrapup_2_camo;
// frames for boop
extern const rgbcolor_t wrapup_2_boop_frames[][4];
extern uint16_t wrapup_2_boop_durations[];
extern uint16_t wrapup_2_boop_fade_durs[];
extern const band_animation_t wrapup_2_boop;
// frames for bigboop
extern const rgbcolor_t wrapup_2_bigboop_frames[][4];
extern uint16_t wrapup_2_bigboop_durations[];
extern uint16_t wrapup_2_bigboop_fade_durs[];
extern const band_animation_t wrapup_2_bigboop;
extern const band_animation_t *wrapup_2_anim_set[3];
// frames for camo
extern const rgbcolor_t wrapup_3_camo_frames[][4];
extern uint16_t wrapup_3_camo_durations[];
extern uint16_t wrapup_3_camo_fade_durs[];
extern const band_animation_t wrapup_3_camo;
// frames for boop
extern const rgbcolor_t wrapup_3_boop_frames[][4];
extern uint16_t wrapup_3_boop_durations[];
extern uint16_t wrapup_3_boop_fade_durs[];
extern const band_animation_t wrapup_3_boop;
// frames for bigboop
extern const rgbcolor_t wrapup_3_bigboop_frames[][4];
extern uint16_t wrapup_3_bigboop_durations[];
extern uint16_t wrapup_3_bigboop_fade_durs[];
extern const band_animation_t wrapup_3_bigboop;
extern const band_animation_t *wrapup_3_anim_set[3];
// frames for camo
extern const rgbcolor_t wrapup_4_camo_frames[][4];
extern uint16_t wrapup_4_camo_durations[];
extern uint16_t wrapup_4_camo_fade_durs[];
extern const band_animation_t wrapup_4_camo;
// frames for boop
extern const rgbcolor_t wrapup_4_boop_frames[][4];
extern uint16_t wrapup_4_boop_durations[];
extern uint16_t wrapup_4_boop_fade_durs[];
extern const band_animation_t wrapup_4_boop;
// frames for bigboop
extern const rgbcolor_t wrapup_4_bigboop_frames[][4];
extern uint16_t wrapup_4_bigboop_durations[];
extern uint16_t wrapup_4_bigboop_fade_durs[];
extern const band_animation_t wrapup_4_bigboop;
extern const band_animation_t *wrapup_4_anim_set[3];
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
#define HEAD_ANIM_COUNT 28
#define HEAD_ANIM_COUNT_INCL_META 30
#define HEAD_ANIM_DEF 0
#define HEAD_ANIM_DOUBLEINK 1
#define HEAD_ANIM_FIRE 2
#define HEAD_ANIM_FOUND 3
#define HEAD_ANIM_GAMER 4
#define HEAD_ANIM_GEEK_GIRL 5
#define HEAD_ANIM_GIVER 6
#define HEAD_ANIM_GLAM 7
#define HEAD_ANIM_HANDLER 8
#define HEAD_ANIM_HUMAN_HAT 9
#define HEAD_ANIM_KARATEKID 10
#define HEAD_ANIM_LEARNED 11
#define HEAD_ANIM_LUSH 12
#define HEAD_ANIM_MIXOLOGIST 13
#define HEAD_ANIM_PARTYTIME 14
#define HEAD_ANIM_POOLPARTY 15
#define HEAD_ANIM_POWERHUNGRY 16
#define HEAD_ANIM_PUSHOVER 17
#define HEAD_ANIM_SHUTDOWN 18
#define HEAD_ANIM_UBER 19
#define HEAD_ANIM_WRAPUP_1 20
#define HEAD_ANIM_WRAPUP_2 21
#define HEAD_ANIM_WRAPUP_3 22
#define HEAD_ANIM_WRAPUP_4 23
#define HEAD_ANIM_ZFLAG_BEAR 24
#define HEAD_ANIM_ZFLAG_BI 25
#define HEAD_ANIM_ZFLAG_LEATHER 26
#define HEAD_ANIM_ZFLAG_TRANS 27
#define HEAD_ANIM_META_SOCIAL 28
#define HEAD_ANIM_META_WAKEUP 29
#define ANIM_TYPE_SOLID 0
#define ANIM_TYPE_FASTTWINKLE 1
#define ANIM_TYPE_HARDTWINKLE 2
#define ANIM_TYPE_SLOWTWINKLE 3
#define ANIM_TYPE_SOFTTWINKLE 4
#define LEG_ANIM_TYPE_COUNT 5
extern const band_animation_t **legs_all_anim_sets[];
#endif // _H_
extern const rgbcolor_t sprays[];
