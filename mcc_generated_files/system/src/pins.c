/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 3.0.0
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIPS 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "../pins.h"
#include "../system.h"

void (*SW1_InterruptHandler)(void);

void PIN_MANAGER_Initialize(void)
{
   /**
    LATx registers
    */
    LATA = 0x0;
    LATC = 0x18;

    /**
    TRISx registers
    */
    TRISA = 0xF;
    TRISC = 0x2;

    /**
    ANSELx registers
    */
    ANSELA = 0x0;
    ANSELC = 0x0;

    /**
    WPUx registers
    */
    WPUA = 0xA;
    WPUC = 0x0;
    OPTION_REGbits.nWPUEN = 0x0;
  
    /**
    ODx registers
    */
   
    /**
    SLRCONx registers
    */
    /**
    INLVLx registers
    */
    INLVLA = 0x0;
    INLVLC = 0x0;

    /**
    PPS registers
    */

    /**
    APFCON registers
    */
    APFCON0 = 0x0; //RC2->MSSP:SDO;

   /**
    IOCx registers 
    */
    IOCAP = 0x0;
    IOCAN = 0x2;
    IOCAF = 0x0;

//    SW1_SetInterruptHandler(SW1_DefaultInterruptHandler);

    // Enable INTCONbits.IOCIE interrupt 
    INTCONbits.IOCIE = 1; 
}
  
void PIN_MANAGER_IOC(void)
{
    // interrupt on change for pin SW1}
    if(IOCAFbits.IOCAF1 == 1)
    {
//        SW1_ISR();
    }
}
   
/**
   SW1 Interrupt Service Routine
*/
void SW1_ISR(void) {

    // Add custom IOCAF1 code

    // Call the interrupt handler for the callback registered at runtime
    if(SW1_InterruptHandler)
    {
        SW1_InterruptHandler();
    }
    IOCAFbits.IOCAF1 = 0;
}

/**
  Allows selecting an interrupt handler for IOCAF1 at application runtime
*/
void SW1_SetInterruptHandler(void (* InterruptHandler)(void)){
    SW1_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCAF1
*/
void SW1_DefaultInterruptHandler(void){
    // add your SW1 interrupt custom code
    // or set custom function using SW1_SetInterruptHandler()
    __delay_ms(60);
    if (SW1_GetValue() == LOW) {
        GRN_LED_Toggle();
    }
}
/**
 End of File
*/