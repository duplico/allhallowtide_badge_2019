#include "driverlib.h"
#include <msp430fr2512.h>

#include "tlc5948a.h"

#include "captivate.h"
#include "band_anims.h"

#include "leds.h"
#include "badge.h"
#include "serial.h"

#pragma NOINIT(badge_conf)
badge_conf_t badge_conf;

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
    FRCTL0 = FRCTLPW | NWAITS_1;

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
    // P1.3     GSCLK       (SEL 00; DIR 1)
    // P1.4     loopback    (SEL 00; DIR 0)
    // P1.5     cap         (SEL 11; DIR 0) // EYE
    // P1.6     unused      (SEL 00; DIR 0)
    // P1.7     cap         (SEL 11; DIR 0) // BOOP
    P1DIR = 0b00001011;
    P1SEL0 = 0b10100110; // LSB
    P1SEL1 = 0b10100000; // MSB
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

/// How many band animations are available?
uint8_t band_unlocked_count() {
    // You start with 2, and get a new one for every badge you pair with.
    // But, your own badge ID number is counted as "seen", so really you
    // start with 1:
    if ((1 + badge_conf.badge_seen_count) > HEAD_ANIM_COUNT) {
        return HEAD_ANIM_COUNT;
    }

    return 1 + badge_conf.badge_seen_count;
}

uint8_t badge_seen(uint8_t id) {
    if (badge_conf.badges_seen & (BIT0 << id))
        return 1;
    return 0;
}

void set_badge_seen(uint8_t id) {
    uint8_t anim_count_pre;

    if (badge_seen(id) || id >= 32) {
        return;
    }

    anim_count_pre = band_unlocked_count();

    __bic_SR_register(GIE);
//    // Unlock FRAM access:
    SYSCFG0 = FRWPPW | DFWP_0 | PFWP_1;
    badge_conf.badges_seen |= (BIT0 << id);
    badge_conf.badge_seen_count++;
//    // Lock FRAM access:
    SYSCFG0 = FRWPPW | DFWP_1 | PFWP_1;
    __bis_SR_register(GIE);

    // Is a new animation allowed, now? If so, start using it.
    if (band_unlocked_count() > anim_count_pre) {
        band_start_anim_by_id(band_unlocked_count()-1, 0, 1);
    }
}

/// Callback for pressing the nose in CapTIvate.
void boop_cb(tSensor* pSensor)
{
    if(!pSensor || ((pSensor->bSensorTouch == true) && (pSensor->bSensorPrevTouch == false))) {
        current_ambient_correct = 5;
        if (serial_ll_state == SERIAL_LL_PAIRED) {
            UCA0TXBUF = REMOTE_BOOP_MSG;
        }
        band_start_anim_by_struct(&meta_boop, 0, 0);
        if (!heart_state) {
            heart_is_boop = 1;
            heart_color = heart_color_options[badge_conf.badge_id % HEART_COLOR_COUNT];
            heart_state = 3;
        }
    }
}

/// Callback for pressing the eye in CapTIvate.
void eye_cb(tSensor* pSensor)
{
    if((pSensor->bSensorTouch == true) && (pSensor->bSensorPrevTouch == false))
    {
        SYSCFG0 = FRWPPW | DFWP_0 | PFWP_1;
        badge_conf.current_band_id = (badge_conf.current_band_id + 1) % band_unlocked_count();
        SYSCFG0 = FRWPPW | DFWP_1 | PFWP_1;

        band_start_anim_by_id(badge_conf.current_band_id, 0, 1);
    }
}

/// Initialize the timer for (a) LED frames, and (b) LED GSCLK.
void init_timers() {
    // For our timer, we're going to use ACLK, which is sourced from REFO.
    //  (REFO is 32k)
    // We'd like to have this run at like 60-100 Hz, I think.
    // We'll divide our 32k clock by 64 to get 512 Hz.
    // Then, we'll use a period of 8 to get 64ish frames per second.
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

    // Then, this is the GSCLK timer. It's much faster, and sourced from
    //  SMCLK/8 so it's about 0.5 MHz.
    next_channel_timer_init.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    next_channel_timer_init.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_8;
    next_channel_timer_init.timerPeriod = 1;
    next_channel_timer_init.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    next_channel_timer_init.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE;
    next_channel_timer_init.timerClear = TIMER_A_SKIP_CLEAR;
    next_channel_timer_init.startTimer = false;

    Timer_A_initUpMode(TIMER_A1_BASE, &next_channel_timer_init);
    Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);
}

/// Make snafucated.
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;

    init_clocks();
    init_io();
    init_timers();

    __bis_SR_register(GIE);
    tlc_init();
    current_ambient_correct = 1;
    serial_init();

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
        SYSCFG0 = FRWPPW | DFWP_0 | PFWP_1;
        badge_conf.current_band_id = 0;
        SYSCFG0 = FRWPPW | DFWP_1 | PFWP_1;
    }

    if (badge_conf.badge_id < 32 && !badge_seen(badge_conf.badge_id)) {
        set_badge_seen(badge_conf.badge_id);
    }

    band_start_anim_by_id(badge_conf.current_band_id, 0, 1);

    WDTCTL = WDTPW | WDTSSEL__ACLK | WDTIS__32K | WDTCNTCL; // 1 second WDT

    uint8_t ohai_state_prev = 0;
    uint8_t ohai_state = 0;
    uint8_t ohai_buildup = 0;

    while(1)
    {
        // Check whether CapTIvate needs to be serviced.
        if (g_bConvTimerFlag)
        {
            // Service the CapTIvate UI.
            CAPT_updateUI(&g_uiApp);

            g_bConvTimerFlag = false;
        }

        // Check whether the time loop flag has been set; this is our
        //  main animation and debouncing loop.
        if (f_time_loop) {
            // First off, pat the dog.
            WDTCTL = WDTPW | WDTSSEL__ACLK | WDTIS__32K | WDTCNTCL; // 1 second WDT

            // Service the LED animation timestep.
            leds_timestep();

            // Debounce and service the serial connection detection line,
            //  jauntily nicknamed the "o hai" signal, which is pulled UP
            //  internally on our MCU, and therefore is asserted when it
            //  is brought LOW by the connecting board.
            // Debounce:
            ohai_state_prev = ohai_state;
            ohai_state = (P2IN & BIT2) ? 1 : 0;

            // If we are in an IDLE state, we're looking for this signal
            //  to go low. But, because the connectors are fiddly, we'll
            //  do some fairly aggressive debouncing here.
            if (serial_ll_state == SERIAL_LL_IDLE) {
                if (ohai_state == ohai_state_prev && ohai_state == 0) {
                    // If the signal is low, and was also low last time
                    //  we checked, increment ohai_buildup. Once the signal
                    //  is asserted (low) for enough time loops, we decide
                    //  that the boards are likely firmly connected, and it's
                    //  time to transition in our serial state machine.
                    ohai_buildup++;
                    if (ohai_buildup > 120) {
                        // Bring the serial state machine active.
                        serial_ll_state = SERIAL_LL_OPEN_WAIT;
                        ohai_buildup = 0;
                    }
                } else {
                    // Unplugged, or unstable connection; start counting
                    //  again from 0.
                    ohai_buildup = 0;
                }
            } else {
                // If we're not in SERIAL_LL_IDLE, we are either in OPEN_WAIT
                //  or in PAIRED. In either case, we are monitoring for the
                //  other board to be unplugged. In this case, we're not really
                //  debouncing aggressively, because basically any change at
                //  all in the signal means they are no longer firmly plugged
                //  into each other.
                // We're looking for o_hai to go high.
                if (ohai_state == ohai_state_prev && ohai_state == 1) {
                    // unplugged
                    serial_ll_state = SERIAL_LL_IDLE;
                } else {
                    // If the connection is still stable, tell the serial
                    //  system that there's been another "timeout" (which is
                    //  really more of a timeSTEP than a timeOUT, but needs to
                    //  be serviced regardless.
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
                current_ambient_correct = 2;
                band_start_anim_by_struct(&meta_pair, 10, 0);
            } else {
                // do the NEW thing
                current_ambient_correct = 7;
                band_start_anim_by_struct(&meta_newpair, 20, 0);
                set_badge_seen(paired_id);
            }
            heart_color = heart_color_options[(badge_conf.badge_id+paired_id) % HEART_COLOR_COUNT];
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

// NB: In the below ISRs, for historical reasons, the vectors are named
//      in a confusing way.
//
// **** TL;DR: Timer A0 is TIMER0_A0_xxx; Timer A1 is TIMER1_A0_xxx.
//
//     This is, apparently, because originally devices only had a single
//      Timer A, Timer B, etc. So, the CCR registers' index determined
//      the major number: TIMER_A0 (Timer A, CCR0); TIMER_A1 (Timer A, CCR1),
//      etc. But now, devices like this one have multiple Timer As. So,
//      the naming convention must be Timer0_A... for Timer A0, and
//      Timer1_A... for A1, etc.
//     Anyway, that's why it looks like this.

// Dedicated ISR for CCR0. Vector is cleared on service.
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR_HOOK(void)
{
    f_time_loop = 1;
    LPM0_EXIT;
}

// Dedicated ISR for CCR0. Vector is cleared on service.
#pragma vector=TIMER1_A0_VECTOR
//__attribute__((ramfunc))
__interrupt void TIMER1_A0_ISR_HOOK(void)
{
    P1OUT ^= BIT3;
}
