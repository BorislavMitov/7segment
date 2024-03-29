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

#include "const.h"
#include <stdint.h>        /* Includes uint16_t definition   */
#include <stdbool.h>
#include <libpic30.h>       /* Includes true/false definition */

/******************************************************************************/
/* Interrupt Vector Options                                                   */
/******************************************************************************/
/*                                                                            */
/* Refer to the C30 (MPLAB C Compiler for PIC24F MCUs and dsPIC33F DSCs) User */
/* Guide for an up to date list of the available interrupt options.           */
/* Alternately these names can be pulled from the device linker scripts.      */
/*                                                                            */
/* dsPIC33F Primary Interrupt Vector Names:                                   */
/*                                                                            */
/* _INT0Interrupt      _C1Interrupt                                           */
/* _IC1Interrupt       _DMA3Interrupt                                         */
/* _OC1Interrupt       _IC3Interrupt                                          */
/* _T1Interrupt        _IC4Interrupt                                          */
/* _DMA0Interrupt      _IC5Interrupt                                          */
/* _IC2Interrupt       _IC6Interrupt                                          */
/* _OC2Interrupt       _OC5Interrupt                                          */
/* _T2Interrupt        _OC6Interrupt                                          */
/* _T3Interrupt        _OC7Interrupt                                          */
/* _SPI1ErrInterrupt   _OC8Interrupt                                          */
/* _SPI1Interrupt      _DMA4Interrupt                                         */
/* _U1RXInterrupt      _T6Interrupt                                           */
/* _U1TXInterrupt      _T7Interrupt                                           */
/* _ADC1Interrupt      _SI2C2Interrupt                                        */
/* _DMA1Interrupt      _MI2C2Interrupt                                        */
/* _SI2C1Interrupt     _T8Interrupt                                           */
/* _MI2C1Interrupt     _T9Interrupt                                           */
/* _CNInterrupt        _INT3Interrupt                                         */
/* _INT1Interrupt      _INT4Interrupt                                         */
/* _ADC2Interrupt      _C2RxRdyInterrupt                                      */
/* _DMA2Interrupt      _C2Interrupt                                           */
/* _OC3Interrupt       _DCIErrInterrupt                                       */
/* _OC4Interrupt       _DCIInterrupt                                          */
/* _T4Interrupt        _DMA5Interrupt                                         */
/* _T5Interrupt        _U1ErrInterrupt                                        */
/* _INT2Interrupt      _U2ErrInterrupt                                        */
/* _U2RXInterrupt      _DMA6Interrupt                                         */
/* _U2TXInterrupt      _DMA7Interrupt                                         */
/* _SPI2ErrInterrupt   _C1TxReqInterrupt                                      */
/* _SPI2Interrupt      _C2TxReqInterrupt                                      */
/* _C1RxRdyInterrupt                                                          */
/*                                                                            */
/* dsPIC33E Primary Interrupt Vector Names:                                   */
/*                                                                            */
/* _INT0Interrupt     _IC4Interrupt      _U4TXInterrupt                       */
/* _IC1Interrupt      _IC5Interrupt      _SPI3ErrInterrupt                    */
/* _OC1Interrupt      _IC6Interrupt      _SPI3Interrupt                       */
/* _T1Interrupt       _OC5Interrupt      _OC9Interrupt                        */
/* _DMA0Interrupt     _OC6Interrupt      _IC9Interrupt                        */
/* _IC2Interrupt      _OC7Interrupt      _PWM1Interrupt                       */
/* _OC2Interrupt      _OC8Interrupt      _PWM2Interrupt                       */
/* _T2Interrupt       _PMPInterrupt      _PWM3Interrupt                       */
/* _T3Interrupt       _DMA4Interrupt     _PWM4Interrupt                       */
/* _SPI1ErrInterrupt  _T6Interrupt       _PWM5Interrupt                       */
/* _SPI1Interrupt     _T7Interrupt       _PWM6Interrupt                       */
/* _U1RXInterrupt     _SI2C2Interrupt    _PWM7Interrupt                       */
/* _U1TXInterrupt     _MI2C2Interrupt    _DMA8Interrupt                       */
/* _AD1Interrupt      _T8Interrupt       _DMA9Interrupt                       */
/* _DMA1Interrupt     _T9Interrupt       _DMA10Interrupt                      */
/* _NVMInterrupt      _INT3Interrupt     _DMA11Interrupt                      */
/* _SI2C1Interrupt    _INT4Interrupt     _SPI4ErrInterrupt                    */
/* _MI2C1Interrupt    _C2RxRdyInterrupt  _SPI4Interrupt                       */
/* _CM1Interrupt      _C2Interrupt       _OC10Interrupt                       */
/* _CNInterrupt       _QEI1Interrupt     _IC10Interrupt                       */
/* _INT1Interrupt     _DCIEInterrupt     _OC11Interrupt                       */
/* _AD2Interrupt      _DCIInterrupt      _IC11Interrupt                       */
/* _IC7Interrupt      _DMA5Interrupt     _OC12Interrupt                       */
/* _IC8Interrupt      _RTCCInterrupt     _IC12Interrupt                       */
/* _DMA2Interrupt     _U1ErrInterrupt    _DMA12Interrupt                      */
/* _OC3Interrupt      _U2ErrInterrupt    _DMA13Interrupt                      */
/* _OC4Interrupt      _CRCInterrupt      _DMA14Interrupt                      */
/* _T4Interrupt       _DMA6Interrupt     _OC13Interrupt                       */
/* _T5Interrupt       _DMA7Interrupt     _IC13Interrupt                       */
/* _INT2Interrupt     _C1TxReqInterrupt  _OC14Interrupt                       */
/* _U2RXInterrupt     _C2TxReqInterrupt  _IC14Interrupt                       */
/* _U2TXInterrupt     _QEI2Interrupt     _OC15Interrupt                       */
/* _SPI2ErrInterrupt  _U3ErrInterrupt    _IC15Interrupt                       */
/* _SPI2Interrupt     _U3RXInterrupt     _OC16Interrupt                       */
/* _C1RxRdyInterrupt  _U3TXInterrupt     _IC16Interrupt                       */
/* _C1Interrupt       _USB1Interrupt     _ICDInterrupt                        */
/* _DMA3Interrupt     _U4ErrInterrupt    _PWMSpEventMatchInterrupt            */
/* _IC3Interrupt      _U4RXInterrupt     _PWMSecSpEventMatchInterrupt         */
/*                                                                            */
/* For alternate interrupt vector naming, simply add 'Alt' between the prim.  */
/* interrupt vector name '_' and the first character of the primary interrupt */
/* vector name.  There is no Alternate Vector or 'AIVT' for the 33E family.   */
/*                                                                            */
/* For example, the vector name _ADC2Interrupt becomes _AltADC2Interrupt in   */
/* the alternate vector table.                                                */
/*                                                                            */
/* Example Syntax:                                                            */
/*                                                                            */
/* void __attribute__((interrupt,auto_psv)) <Vector Name>(void)               */
/* {                                                                          */
/*     <Clear Interrupt Flag>                                                 */
/* }                                                                          */
/*                                                                            */
/* For more comprehensive interrupt examples refer to the C30 (MPLAB C        */
/* Compiler for PIC24 MCUs and dsPIC DSCs) User Guide in the                  */
/* <C30 compiler instal directory>/doc directory for the latest compiler      */
/* release.  For XC16, refer to the MPLAB XC16 C Compiler User's Guide in the */
/* <XC16 compiler instal directory>/doc folder.                               */
/*                                                                            */
/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* TODO Add interrupt routine code here. */

/* CN INTERRUPT */
void __attribute__((interrupt,auto_psv)) _CNInterrupt(void)
 {  
    // Input Change Notification Interrupt disabled
    IEC1bits.CNIE   = 0;
    
    // Clear CN interrupt flag
    IFS1bits.CNIF   = 0;
    
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

    /* Input Change Notification Interrupt disabled */
    IEC1bits.CNIE = 1;    
 }//CN interrupt 

  void __attribute__((interrupt,auto_psv)) _T2Interrupt(void)
{
    /* Clear Timer2 Interrupt Flag */
    IFS0bits.T2IF = 0;
    
    /* Switch on the first 7 segment display and switch off the second display */
    if( 0 == i){
        /* The first display is connected to RC9 port */
        LATCbits.LATC9 = 1;
        
        /* The second display is connected to RC8 port */
        LATCbits.LATC8 = 0;
        i++;
    }
    /* Switch off the first 7 segment display and switch on the second display */
    else if(1 == i){
        /* The first display is connected to RC9 port */
        LATCbits.LATC9 = 0;
        
        /* The second display is connected to RC8 port */
        LATCbits.LATC8 = 1;  
        i = 0;
    }
     
     /* OUTPUT */
    if( A == 1){
        LATBbits.LATB5 = 1;
    }
    else{
        LATBbits.LATB5 = 0;
    }

   if( B == 1){
        LATBbits.LATB6 = 1;
    }
    else{
        LATBbits.LATB6 = 0;
    }

    if( C == 1){
        LATBbits.LATB7 = 1;
    }
    else{
        LATBbits.LATB7 = 0;
    }

    if( D == 1){
        LATBbits.LATB8 = 1;
    }
    else{
        LATBbits.LATB8 = 0;
    }

    if( E == 1){
        LATBbits.LATB9 = 1;
    }
    else{
        LATBbits.LATB9 = 0;
    }

    if( F == 1){
        LATCbits.LATC4 = 1;
    }
    else{
        LATCbits.LATC4 = 0;
    }

    if( G == 1){
        LATCbits.LATC5 = 1;
    }
    else{
        LATCbits.LATC5 = 0;
    }
}