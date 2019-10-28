#include "driverlib.h"
#include <msp430fr2512.h>

#include "tlc5948a.h"

#include "captivate.h"
#include "band_anims.h"

#include "leds.h"
#include "badge.h"
#include "serial.h"

extern tSensor BTN1_BOOP;
extern tSensor BTN3_EYE;

volatile uint8_t f_time_loop;
volatile uint8_t f_paired;
volatile uint8_t f_remote_boop;

/// Initialize clock signals and the three system clocks.
/**
 ** We'll take the DCO to 16 MHz, and divide it by 2 for MCLK.
 ** Then we'll divide MCLK by 1 to get 8 MHz SMCLK.
 **
 ** Our available clock sources are:
 **  VLO:     10kHz very low power low-freq
 **  REFO:    32.768kHz (typ) reference oscillator
 **  DCO:     Digitally controlled oscillator (1MHz default)
 **           Specifically, 1048576 Hz typical.
 **
 ** At startup, our clocks are as follows:
 **  MCLK:  Sourced by the DCO
 **         (Available: DCO, REFO, VLO)
 **  SMCLK: Sourced from MCLK, with no divider
 **         (Available dividers: {1,2,4,8})
 **  ACLK: Sourced from REFO
 **         (the only available internal source)
 */
void init_clocks() {
    // DCO  (Digitally-controlled oscillator)
    //  Let's bring this up to 8 MHz or so.

    // Configure FRAM wait state (set to 1 to support 16MHz MCLK)
    FRAMCtl_configureWaitStateControl(FRAMCTL_ACCESS_TIME_CYCLES_1);

    __bis_SR_register(SCG0);                // disable FLL
    CSCTL3 |= SELREF__REFOCLK;              // Set REFO as FLL reference source
    CSCTL0 = 0;                             // clear DCO and MOD registers
    CSCTL1 &= ~(DCORSEL_7);                 // Clear DCO frequency select bits first
    CSCTL1 |= DCORSEL_5;                    // Set DCO = 16MHz
    // CSCTL feedback loop:
    CSCTL2 = FLLD_0 + 487;                  // DCODIV = /1

    __delay_cycles(3);
    __bic_SR_register(SCG0);                // enable FLL
    while(CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)); // Poll until FLL is locked

    // SYSTEM CLOCKS
    // =============

    // MCLK (16 MHz)
    //  All sources but MODOSC are available at up to /128
    //  Set to DCO/1 = 8 MHz
    // DIVM__1;

    // SMCLK (8 MHz)
    //  Derived from MCLK with divider up to /8
    //  Set to MCLK/2 = 8 MHz
    // DIVS__1;

    CSCTL5 = VLOAUTOOFF_1 | DIVS__2 | DIVM__1;
}

/// Apply the initial configuration of the GPIO and peripheral pins.
/**
 **
 */
void init_io() {
    // Set up the alternate pinout for UCA0
    SYSCFG3 |= USCIARMP;

    // GPIO:
    // P1.0     LAT         (SEL 00; DIR 1)
    // P1.1     UCB0 SCLK   (SEL 01; DIR 1)
    // P1.2     UCB0SIMO    (SEL 01; DIR 0)
    // P1.3     MCLK/GSCLK  (SEL 10; DIR 1)
    // P1.4     loopback    (SEL 00; DIR 0)
    // P1.5     cap         (SEL 11; DIR 0) // EYE
    // P1.6     unused      (SEL 00; DIR 0)
    // P1.7     cap         (SEL 11; DIR 0) // BOOP
    P1DIR = 0b00001011;
    P1SEL0 = 0b10100110; // LSB
//    P1SEL1 = 0b10101000; // MSB - GSCLK enabled
    P1SEL1 = 0b10100000; // MSB - GSCLK disabled (GPIO output instead)
    P1REN = 0x00;
    P1OUT = 0x00;

    // P2.0     UCA0TXD     (SEL 01; DIR 1)
    // P2.1     UCA0RXD     (SEL 01; DIR 0)
    // P2.2     ohai        (SEL 00; DIR 0) (pull-up)
    P2DIR = 0b001;
    P2SEL0 = 0b011;
    P2SEL1 = 0b000;
    P2REN = 0b100;
    P2OUT = 0b100;

    // Unlock the pins from high-impedance mode:
    // (AKA the MSP430FR magic make-it-work command)
    PM5CTL0 &= ~LOCKLPM5;
}

#pragma NOINIT(badge_conf)
badge_conf_t badge_conf;

uint8_t badge_seen(uint8_t id) {
    if (badge_conf.badges_seen & (BIT0 << id))
        return 1;
    return 0;
}

void set_badge_seen(uint8_t id) {
    if (badge_seen(id)) {
        return;
    }
    __bic_SR_register(GIE);
//    // Unlock FRAM access:
    SYSCFG0 = FRWPPW | DFWP_0;
    badge_conf.badges_seen |= (BIT0 << id);
    badge_conf.badge_seen_count++;
//    // Lock FRAM access:
    SYSCFG0 = FRWPPW | DFWP_1;
    __bis_SR_register(GIE);

    // TODO: Is a new animation allowed, now?
    // If so, start using it.

}

uint8_t band_unlocked_count() {
    if (1 + badge_conf.badge_seen_count / 2 > HEAD_ANIM_COUNT) {
        return HEAD_ANIM_COUNT;
    }
    return 1 + badge_conf.badge_seen_count / 2;
}

void boop_cb(tSensor* pSensor)
{
    if(!pSensor || ((pSensor->bSensorTouch == true) && (pSensor->bSensorPrevTouch == false))) {
        current_ambient_correct = 4;
        band_start_anim_by_struct(&meta_boop_band, 0, 0);
        if (!heart_state) {
            // TODO: color
            heart_state = 3;
        }
    }
}

void eye_cb(tSensor* pSensor)
{
    if((pSensor->bSensorTouch == true) && (pSensor->bSensorPrevTouch == false))
    {

        SYSCFG0 = FRWPPW | DFWP_0;
        badge_conf.current_band_id = (badge_conf.current_band_id + 1) % band_unlocked_count();
        SYSCFG0 = FRWPPW | DFWP_1;

        band_start_anim_by_id(badge_conf.current_band_id, 0, 0, 1);
    }
}

int main(void) {
    // TODO:
    WDTCTL = WDTPW | WDTHOLD;

    init_clocks();
    init_io();

    __bis_SR_register(GIE);
    tlc_init();
    serial_init();

    // TODO: Refactor to another function.
    // For our timer, we're going to use ACLK, which is sourced from REFO.
    //  (REFO is 32k)
    // We'd like to have this run at like 60-100 Hz, I think.
    // We'll divide our 32k clock by 64 to get 512 Hz.
    // Then, we'll use a period of 8 to get 64ish frames per second.
    // TODO: Eliminate driverlib.
    Timer_A_initUpModeParam next_channel_timer_init = {};
    next_channel_timer_init.clockSource = TIMER_A_CLOCKSOURCE_ACLK;
    next_channel_timer_init.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_64;
    next_channel_timer_init.timerPeriod = 8;
    next_channel_timer_init.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    next_channel_timer_init.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE;
    next_channel_timer_init.timerClear = TIMER_A_SKIP_CLEAR;
    next_channel_timer_init.startTimer = false;

    Timer_A_initUpMode(TIMER_A0_BASE, &next_channel_timer_init);
    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);


    next_channel_timer_init.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    next_channel_timer_init.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_8;
    next_channel_timer_init.timerPeriod = 1;
    next_channel_timer_init.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    next_channel_timer_init.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE;
    next_channel_timer_init.timerClear = TIMER_A_SKIP_CLEAR;
    next_channel_timer_init.startTimer = false;

    if (!(P1SEL1 & BIT3)) {
        Timer_A_initUpMode(TIMER_A1_BASE, &next_channel_timer_init);
        Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);
    }

    tlc_stage_blank(0);
    tlc_set_fun();

    CAPT_initUI(&g_uiApp);
    CAPT_calibrateUI(&g_uiApp);
    MAP_CAPT_registerCallback(&BTN1_BOOP, &boop_cb);
    MAP_CAPT_registerCallback(&BTN3_EYE, &eye_cb);
    MAP_CAPT_selectTimerSource(CAPT_TIMER_SRC_ACLK);
    MAP_CAPT_writeTimerCompRegister(CAPT_MS_TO_CYCLES(g_uiApp.ui16ActiveModeScanPeriod));
    MAP_CAPT_startTimer();
    MAP_CAPT_enableISR(CAPT_TIMER_INTERRUPT);


    if (badge_conf.current_band_id >= HEAD_ANIM_COUNT) {
        SYSCFG0 = FRWPPW | DFWP_0;
        badge_conf.current_band_id = 0;
        SYSCFG0 = FRWPPW | DFWP_1;
    }
    band_start_anim_by_id(badge_conf.current_band_id, 0, 0, 1);

    uint8_t ohai_state_prev = 0;
    uint8_t ohai_state = 0;
    uint8_t ohai_buildup = 0;

    while(1)
    {
        if (g_bConvTimerFlag == true)
        {
            //
            // If it is time to update the button,
            // update it here with the generic library call.
            //
            g_bConvTimerFlag = false;
            CAPT_updateUI(&g_uiApp);
        }

        if (f_time_loop) {
            leds_timestep();

            ohai_state_prev = ohai_state;
            ohai_state = (P2IN & BIT2) ? 1 : 0;

            if (serial_ll_state == SERIAL_LL_IDLE) {
                // We're looking for o_hai to go low.
                if (ohai_state == ohai_state_prev && ohai_state == 0) {
                    ohai_buildup++;
                    if (ohai_buildup > 120) {
                        serial_ll_state = SERIAL_LL_OPEN_WAIT;
                        ohai_buildup = 0;
                    }
                } else {
                    ohai_buildup = 0;
                }
            } else {
                // We're looking for o_hai to go high.
                if (ohai_state == ohai_state_prev && ohai_state == 1) {
                    // unplugged
                    serial_ll_state = SERIAL_LL_IDLE;
                } else {
                    serial_timeout();
                }

                // Keep the heart on full until unplug.
                if (heart_state)
                    heart_state = 127;
            }

            f_time_loop = 0;
        }

        if (f_paired) {
            if (badge_seen(paired_id)) {
                // do the already-seen thing
                current_ambient_correct = 1;
                band_start_anim_by_struct(&meta_pair_band, 10, 0);
            } else {
                // do the NEW thing
                current_ambient_correct = 6;
                band_start_anim_by_struct(&meta_newpair_band, 20, 0);
                set_badge_seen(paired_id);
            }
            // TODO: pick our heart color based on (badge_conf.badge_id + paired_id) % badges_in_system
            heart_state = 127;

            f_paired = 0;
        }

        if (f_remote_boop) {
            boop_cb(0);
            f_remote_boop = 0;
        }

        __bis_SR_register(LPM0_bits);
    } // End background loop
}

// Dedicated ISR for CCR0. Vector is cleared on service.
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR_HOOK(void)
{
    f_time_loop = 1;
    LPM0_EXIT;
}

// Dedicated ISR for CCR0. Vector is cleared on service.
#pragma vector=TIMER1_A0_VECTOR
__attribute__((ramfunc))__interrupt void TIMER1_A0_ISR_HOOK(void)
{
    P1OUT ^= BIT3;
}
