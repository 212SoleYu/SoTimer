/**
 * @file timer.c
 *
 * Provides hardware and software delay and alarm/scheduling functions
 *
 * @author Aaron Parks
 */

#include <lib/math_lib/globals.h>
#include <lib/math_lib/timer.h>

//#include <mspbase.h>

static BOOL wakeOnDelayTimer;       // A flag indicating we are waiting for a delay timer to expire

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
/// Timer_LooseDelay
///
/// This function uses the timer to generate delays that are at least as long as
/// the specified duration
///
/// \param usTime32kHz - The minimum amount of time to delay in ~30.5us units (1/32768Hz)
/// @todo Move config register and value definitions to config.h
/////////////////////////////////////////////////////////////////////////////
void Timer_LooseDelay(uint16_t usTime32kHz)
{
    TA2CCTL0 = CCIE;                          // CCR0 interrupt enabled
    TA2CCR0 = usTime32kHz;
    TA2CTL = TASSEL_1 | MC_1 | TACLR;         // ACLK(=REFO), upmode, clear TAR

    wakeOnDelayTimer = TRUE;

    while(wakeOnDelayTimer) {
        __bis_SR_register(LPM3_bits | GIE);
    }

    TA2CCTL0 = 0x00;
    TA2CTL = 0;

}

//----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////
// INT_TimerA1
//
// Interrupt 0 for timer A2 (CCR0). Used in low power ACLK delay routine.
//
////////////////////////////////////////////////////////////////////////////

#if defined(__clang__)
__attribute__((interrupt(24))) // dummy even number in [0, 28]
#elif defined(__GNUC__)
__attribute__((interrupt(TIMER2_A0_VECTOR))) 
#elif defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER2_A0_VECTOR
__interrupt
#else
#error Compiler not supported!
#endif
void INT_Timer2A0 (void)
{
    if(wakeOnDelayTimer) {
        __bic_SR_register_on_exit(LPM3_bits);
        wakeOnDelayTimer = FALSE;
    }
}

#if defined(__clang__)
__attribute__ ((section("__interrupt_vector_timer2_a0"),aligned(2)))
void (*__vector_timer2_a0)(void) = INT_Timer2A0;
#endif

//----------------------------------------------------------------------------




