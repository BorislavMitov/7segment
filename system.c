/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__dsPIC33E__)
    	#include <p33Exxxx.h>
    #elif defined(__dsPIC33F__)
    	#include <p33Fxxxx.h>
    #endif
#endif


#include <stdint.h>          /* For uint16_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */

#include "system.h"          /* variables/params used by system.c             */

/******************************************************************************/
/* System Level Functions                                                     */
/*                                                                            */
/* Custom oscillator configuration funtions, reset source evaluation          */
/* functions, and other non-peripheral microcontroller initialization         */
/* functions get placed in system.c.                                          */
/*                                                                            */
/******************************************************************************/

/* Refer to the device Family Reference Manual Oscillator section for
information about available oscillator configurations.  Typically
this would involve configuring the oscillator tuning register or clock
switching useing the compiler's __builtin_write_OSCCON functions.
Refer to the C Compiler for PIC24 MCUs and dsPIC DSCs User Guide in the
compiler installation directory /doc folder for documentation on the
__builtin functions.*/

/* TODO Add clock switching code if appropriate.  An example stub is below.   */

void ConfigureOscillator(void)
{
    /* Disable Watch Dog Timer */
    RCONbits.SWDTEN = 0;
    
    /* 16MHz/2 = 8MHz   ;   8MHz*20=160MHz   ;   160MHz/2=80MHz */
    
    /* PLL VCO Output Divider Select bits (also denoted as ?N2?, PLL postscaler) */
    CLKDIVbits.PLLPOST = 0;         // Output/2
    
    /* PLL Phase Detector Input Divider bits (also denoted as ?N1?, PLL prescaler) */
    CLKDIVbits.PLLPRE  = 0;         // Input/2
    
    /* PLL Feedback Divisor bits (also denoted as ?M?, PLL multiplier) */
    PLLFBDbits.PLLDIV = 18;          // Minimum value of the multiplier is set to 2 and corresponds to bit 0, so in order to receive a multiplied by 20
                                     // we need to write a value of 18

    /* When clock switch occurs switch to Primary Osc (HS, XT, EC) */
    __builtin_write_OSCCONH(0x03);  /* Set OSCCONH for clock switch */
    __builtin_write_OSCCONL(0x01);  /* Start clock switching */
    while(OSCCONbits.COSC != 0b011);

    /* Wait for Clock switch to occur */
    /* Wait for PLL to lock, only if PLL is needed */
    while(OSCCONbits.LOCK != 1);
}

