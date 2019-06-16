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
#include "user.h"            /* variables/params used by user.c               */
#include "const.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
   
    /* Setup analog functionality and port direction */

    /* Initialize peripherals */
     configureTimer();
     ConfigureInterrupts();

}

void ConfigureInterrupts(void){
    CNEN1bits.CN6IE = 1;    // Enable CN interrupt on CN6(RB2) pin
    CNEN1bits.CN7IE = 1;    // Enable CN interrupt on CN7(RB3) pin
    CNEN1bits.CN8IE = 1;    // Enable CN interrupt on CN8(RC0) pin
    CNEN1bits.CN9IE = 1;    // Enable CN interrupt on CN9(RC1) pin
    
    IFS1bits.CNIF = 0;      // Clear CN interrupt flag 
    IEC1bits.CNIE = 1;      // Enable CN interrupts
}//ConfigureInterrupts

void configureTimer(void){
    /* Disable Timer */
    T2CONbits.TON = 0;
    
    /*  Enable 16-bit Timer mode */
    T2CONbits.T32 = 0;
    
    /* Select internal instruction cycle clock */
    T2CONbits.TCS = 0;
    
    /* Disable Gated Timer mod */
    T2CONbits.TGATE = 0;
    
    /*  Select 1:8 Prescaler */
    T2CONbits.TCKPS = 0b01;
    
    /* Clear timer register */
    TMR2 = 0x00;
        
    /* timer period value Period Register 2 && 3 */
/* Ftimer = FCY/8 = 1MHz  ;  Ttimer = 1/1MHz = 1us  ;  The 7 segement display will refresh every 50ms = 20Hz ==> 20ms/1us = 20 0000  ;   maxCycles = 2^32  ;
 * 2x7segment display, so for each displays to be refreshed every 20ms, we need to generate interupts each 20ms/2 = 10ms ==> 10ms/1us = 10 0000 */
    
    /* Load the period value */
    PR2 = 10000;
    
    /* Clear Timer2 Interrupt Flag */
    IFS0bits.T2IF = 0;
    
    /* Enable Timer2 interrupt */
    IEC0bits.T2IE= 1;
    
    /* Continue operation in Idle mode  */
    T2CONbits.TSIDL = 0;
   
    /* tart 32-bit Timer */
    T2CONbits.TON = 1;
}
