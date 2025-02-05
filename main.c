 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
� [2025] Microchip Technology Inc. and its subsidiaries.

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
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "ADXL345.h"
#include "fall.h"

/*
    Main application
*/

uint8_t dataBuffer[256] = {0};

int main(void)
{
    SYSTEM_Initialize();
    SPI1_Initialize();
    
    CS_ACC_SetHigh();
    CS_RF_SetHigh();
    
    if (ADXL345_validation()) {
        GRN_LED_SetHigh();
        __delay_ms(250);
        GRN_LED_SetLow();
    } else {
        RED_LED_SetHigh();
        __delay_ms(250);
        RED_LED_SetLow();
    }
    
    ADXL345_init();
    State_t current_state = WAITING_FOR_FREEFALL;
    
    while(1)
    {           
        PIN_MANAGER_IOC();
        MotionEventHandler(&current_state);
        SLEEP();
        NOP();
    }    
}