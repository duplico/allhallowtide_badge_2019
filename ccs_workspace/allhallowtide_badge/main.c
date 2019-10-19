#include "driverlib.h"
#include <msp430fr2512.h>

#include "tlc5948a.h"
#include "CAPT_App.h"

/// Initialize clock signals and the three system clocks.
/**
 ** We'll take the DCO to 16 MHz, and divide it by 1 for MCLK.
 ** Then we'll divide MCLK by 8 to get 2 MHz SMCLK.
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
    //  Let's bring this up to 16 MHz or so.

    __bis_SR_register(SCG0);                // disable FLL
    CSCTL3 |= SELREF__REFOCLK;              // Set REFO as FLL reference source
    CSCTL0 = 0;                             // clear DCO and MOD registers
    CSCTL1 &= ~(DCORSEL_7);                 // Clear DCO frequency select bits first
    CSCTL1 |= DCORSEL_5;                    // Set DCO = 16MHz

    // CSCTL feedback loop:
    // (f_output = (FLLN + 1) * (322768 Hz / outputDiv)
    CSCTL2 = FLLD_0 + 487;                  // DCODIV = /1
    __delay_cycles(3);
    __bic_SR_register(SCG0);                // enable FLL
    while(CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)); // Poll until FLL is locked

    // SYSTEM CLOCKS
    // =============

    // MCLK (16 MHz)
    //  All sources but MODOSC are available at up to /128
    //  Set to DCO/1 = 16 MHz
    // DIVM__1;

    // SMCLK (8 MHz)
    //  Derived from MCLK with divider up to /8
    //  Set to MCLK/8 = 2 MHz
    // DIVS__8;

    CSCTL5 = VLOAUTOOFF_1 | DIVS__8 | DIVM__1;
}

/// Apply the initial configuration of the GPIO and peripheral pins.
/**
 **
 */
void init_io() {
    // TODO:
    // USCIARMP=1

    // GPIO:
    // P1.0     LAT         (SEL 00; DIR 1)
    // P1.1     UCB0 SCLK   (SEL 01; DIR 0)
    // P1.2     UCB0SIMO    (SEL 01; DIR 0)
    // P1.3     MCLK/GSCLK  (SEL 10; DIR 1)
    // P1.4     cap         (SEL 00; DIR 0)
    // P1.5     ohai        (SEL 00; DIR 0) (pull-up)
    // P1.6     cap         (SEL 00; DIR 0)
    // P1.7     cap         (SEL 00; DIR 0)
    P1DIR = 0b00001001;
    P1SEL0 = 0b00000110; // LSB
    P1SEL1 = 0b00001000; // MSB
    P1REN = 0b00100000;
    P1OUT = 0b00100000;
    // TODO: P2.2: SYNC (SET OUTPUT LOW UNLESS USED)
    // P2.0     UCA0TXD     (SEL 01; DIR 1)
    // P2.1     UCA0RXD     (SEL 01; DIR 0)
    // P2.2     unused      (SEL 00; DIR 0)
    P2DIR = 0b001;
    P2SEL0 = 0b011;
    P2SEL1 = 0b000;
    P2REN = 0b000;
    P2OUT = 0b000;

    // Unlock the pins from high-impedance mode:
    // (AKA the MSP430FR magic make-it-work command)
    PM5CTL0 &= ~LOCKLPM5;
}

void write_conf() {
//    __bic_SR_register(GIE);
//    // Unlock FRAM access:
//    SYSCFG0 = FRWPPW | PFWP_0;
//    memcpy(&badge_conf_persistent, &badge_conf, sizeof(cbadge_conf_t));
//    // Lock FRAM access:
//    SYSCFG0 = FRWPPW | PFWP_1;
//    __bis_SR_register(GIE);
}

void generate_config() {
//    // We treat this like FIRST BOOT. Need to initialize the config.
//    // The run time initializes badge_conf to all 0s for us.
//    badge_conf.badge_id = CBADGE_ID_MAX_UNASSIGNED;
//    badge_conf.initialized = 1;
//    badge_conf.element_selected = ELEMENT_COUNT_NONE;
//    // The handle is all zeroes. Empty string. That's fine.
//    write_conf();
}

int main(void) {

    WDTCTL = WDTPW | WDTHOLD;

    // TODO:
    // Configure FRAM wait state (set to 1 to support 16MHz MCLK)
    FRAMCtl_configureWaitStateControl(FRAMCTL_ACCESS_TIME_CYCLES_1);

    init_clocks();
    init_io();

    tlc_init();

    __bis_SR_register(GIE);

    CAPT_appStart();

    while(1)
    {
        //
        // Run the captivate application handler.
        //
        CAPT_appHandler();

        //
        // This is a great place to add in any
        // background application code.
        //
        __no_operation();

        //
        // End of background loop iteration
        // Go to sleep if there is nothing left to do
        //
        CAPT_appSleep();

    } // End background loop
}

int _system_pre_init(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    return 1;
}
