/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File: ADXL345.h
 * Author: Austin
 * Comments: All relevant functions necessary to communicate with an ADXL345
 * Revision history:
 *  2/4/2025 - initial creation
 */
  
#ifndef ADXL345_H
#define	ADXL345_H

#include "mcc_generated_files/system/system.h"

#define DEVICE_ID		0x00
#define THRESH_TAP      0x1D // Tap threshold
#define OFSX            0x1E // X-axis offset
#define OFSY            0x1F // Y-axis offset
#define OFSZ            0x20 // Z-axis offset
#define DUR             0x21 // Tap duration
#define LATENT          0x22 // Tap latency
#define WINDOW          0x23 // Tap window
#define THRESH_ACT      0x24 // Activity threshold
#define THRESH_INACT    0x25 // Inactivity threshold
#define TIME_INACT      0x26 // Inactivity time
#define ACT_INACT_CTL   0x27 // Axis enable control for activity and inactivity detection
#define THRESH_FF       0x28 // Free-fall threshold
#define TIME_FF         0x29 // Free-fall time
#define TAP_AXES        0x2A // Axis control for single tap/double tap
#define ACT_TAP_STATUS  0x2B // Source of single tap/double tap
#define BW_RATE         0x2C // Data rate and power mode control
#define POWER_CTL       0x2D // Power saving features control
#define INT_ENABLE      0x2E // Interrupt enable control
#define INT_MAP         0x2F // Interrupt mapping control
#define INT_SOURCE      0x30 // Source of interrupts
#define DATA_FORMAT     0x31 // Data format control
#define DATAX0          0x32 // X-Axis Data 0
#define DATAX1          0x33 // X-Axis Data 1
#define DATAY0          0x34 // Y-Axis Data 0
#define DATAY1          0x35 // Y-Axis Data 1
#define DATAZ0          0x36 // Z-Axis Data 0
#define DATAZ1          0x37 // Z-Axis Data 1
#define FIFO_CTL        0x38 // FIFO control
#define FIFO_STATUS     0x39 // FIFO status

struct Message {
    uint8_t registerAddr;
    uint8_t data[25];
};

bool ADXL345_init(void);
bool ADXL345_validation(void);
void saveOffsets(uint8_t x_axis, uint8_t y_axis, uint8_t z_axis);
void ADXL345_ClearInterrupt(void);
void setupForFreefall(void);
void setupForImpact(void);
void setupForInactivity(void);
bool orientation_Up(void);
bool calibrate(void);

#endif	/* ADXL345_H */

