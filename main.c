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

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/
int a, b, c ,d = 0;
int A, B, C, D, E, F, G = 0;
int i = 0;

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */

#include "const.h"
#include <libpic30.h>   

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{
    /* Initialize IO ports and peripherals */
    InitApp();

    /* TODO <INSERT USER APPLICATION CODE HERE> */
    
    /* OUTPUTS */
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    
    /* INPUTS */
    TRISCbits.TRISC0 = 1;       // a
    TRISCbits.TRISC1 = 1;       // b
    TRISBbits.TRISB3 = 1;       // c
    TRISBbits.TRISB2 = 1;       // d
    
    AD1PCFGLbits.PCFG4 = 1;     // Port pin in Digital mode AN4/RB2
    AD1PCFGLbits.PCFG5 = 1;     // Port pin in Digital mode AN5/RB3
    AD1PCFGLbits.PCFG6 = 1;     // Port pin in Digital mode AN6/RC0
    AD1PCFGLbits.PCFG7 = 1;     // Port pin in Digital mode AN7/RC1 
    
    /* Read inputs */
    a = PORTCbits.RC1;
    b = PORTCbits.RC0;
    c = PORTBbits.RB3;
    d = PORTBbits.RB2;
    
    /* 7 segment decoder */ 
    A = (!b&&!c&&!d)||(!a&&!b&&!d)||(!b&&c&&!d)||(a&&!b&&!d)||(a&&!c&&!d)||(a&&!b&&!c)||(!a&&b&&d)||(!a&&c)||(b&&c)||(c&&!d);
    B = (!b&&!c&&!d)||(a&&!b&&!d)||(!b&&c&&!d)||(!a&&!b&&!d)||(!a&&!c&&!d)||(!a&&!b)||(a&&!b&&!c)||(a&&!c&&d)||(!a&&c&&d);   
    C = (!b&&!c&&!d)||(a&&!b&&!d)||(!a&&!c)||(!a&&d)||(!c&&d)||(a&&!b)||(!a&&b&&c);
    D = (!a&&!b&&!d)||(!b&&!c&&!d)||(a&&!c)||(b&&!c&&d)||(a&&!b&&d)||(!a&&!b&&c)||(!a&&c&&!d)||(b&&c&&!d);
    E = (!b&&!c&&!d)||(a&&!b&&!d)||(!b&&c&&!d)||(!a&&!b&&!d)||(a&&!c&&!d)||(a&&b)||(a&&c)||(c&&!d);
    F = (!b&&!c&&!d)||(a&&!b&&!d)||(!c&&!d)||(a&&!b)||(!a&&b&&!c)||(a&&c)||(b&&c&&!d);
    G = (a&&!b&&!d)||(!b&&c&&!d)||(!a&&b&&!c)||(b&&!c&&d)||(a&&d)||(a&&c)||(a&&!b)||(c&&!d)||(!a&&!b&&c);
    
    while(1)
    {
        /* Put the device into IDLE mode */
        asm("PWRSAV #0x0001");
    }
}
