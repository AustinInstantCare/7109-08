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
        
    EEPROM_Write(EE_CAL_STATUS_ADDR, CAL_DONE); // skip calibration
        
    if (ADXL345_validation()) {
        GRN_LED_SetHigh();
        __delay_ms(250);
        GRN_LED_SetLow();
    } else {
        RED_LED_SetHigh();
        __delay_ms(250);
        RED_LED_SetLow();
    }
    
    CLRWDT();
    __delay_ms(250);
    CLRWDT();
    
    if (ADXL345_init()) {
        GRN_LED_SetHigh();
        __delay_ms(250);
        GRN_LED_SetLow();
    } else {
        RED_LED_SetHigh();
        __delay_ms(250);
        RED_LED_SetLow();
    }
    
    CLRWDT();
    if (EEPROM_Read(EE_CAL_STATUS_ADDR) == CAL_DONE) {
        uint8_t X_val = EEPROM_READ(EE_X_OFFSET_ADDR);
        uint8_t Y_val = EEPROM_READ(EE_Y_OFFSET_ADDR);
        uint8_t Z_val = EEPROM_READ(EE_Z_OFFSET_ADDR);
        saveOffsets(X_val, Y_val, Z_val);
    } else {
        while(!calibrate()) {
            GRN_LED_SetHigh();
            RED_LED_SetHigh();
            __delay_ms(100);
            GRN_LED_SetLow();
            RED_LED_SetLow();
        };
    }
    
    State_t current_state = WAITING_FOR_FREEFALL;
    
    while(1)
    {           
        PIN_MANAGER_IOC();
        MotionEventHandler(&current_state);
        if (current_state == FALL_DETECTED) {
            current_state = WAITING_FOR_FREEFALL;
            for (int i = 0; i < 3; i++) {
                GRN_LED_SetHigh();
                __delay_ms(100);
                GRN_LED_SetLow();
            }
        }
        SLEEP();
        NOP();
    }    
}