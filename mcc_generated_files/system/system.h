/**
 * System Driver Header File
 * 
 * @file system.h
 * 
 * @defgroup systemdriver System Driver
 * 
 * @brief This file contains the API prototype for the System Driver.
 *
 * @version Driver Version 1.0.1
 *
 * @version Package Version 1.0.3
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

#ifndef SYSTEM_H
#define	SYSTEM_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "config_bits.h"
#include "../system/pins.h"
#include "../system/interrupt.h"
#include "../system/clock.h"

#define WATCHDOG_SLEEP_1ms      0b00000
#define WATCHDOG_SLEEP_2ms      0b00001
#define WATCHDOG_SLEEP_4ms      0b00010
#define WATCHDOG_SLEEP_8ms      0b00011
#define WATCHDOG_SLEEP_16ms     0b00100
#define WATCHDOG_SLEEP_32ms     0b00101
#define WATCHDOG_SLEEP_64ms     0b00110
#define WATCHDOG_SLEEP_128ms    0b00111
#define WATCHDOG_SLEEP_256ms    0b01000
#define WATCHDOG_SLEEP_512ms    0b01001
#define WATCHDOG_SLEEP_1S       0b01010
#define WATCHDOG_SLEEP_2S       0b01011 // <-- Default Value
#define WATCHDOG_SLEEP_4S       0b01100
#define WATCHDOG_SLEEP_8S       0b01101
#define WATCHDOG_SLEEP_16S      0b01110
#define WATCHDOG_SLEEP_32S      0b01111
#define WATCHDOG_SLEEP_64S      0b10000
#define WATCHDOG_SLEEP_128S     0b10001
#define WATCHDOG_SLEEP_256S     0b10010

/**
 * @ingroup systemdriver
 * @brief Initializes the system module.
 * This routine is called only once during system initialization, before calling other APIs.
 * @param None.
 * @return None.
*/
void SYSTEM_Initialize(void);

#endif	/* SYSTEM_H */
/**
 End of File
*/
