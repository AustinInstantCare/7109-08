/*
 * File:   ADXL345.c
 * Author: Austin
 *
 * Created on January 30, 2025, 10:44 AM
 */

#include "ADXL345.h"

const uint8_t ADXL345_init_settings[12] = {
	0x18,	// ~1.5 g
	0x03,	// ~0.1875 g
	0xFF,	// 255 seconds
	0x7F,	// 0b01111111
	0x07,	// 0.4375 g free fall threshold
	0x18,	// 120 ms free fall time threshold
	0x00,	// no tap detection
	0x00,	// read only register
	0x17,	// low power mode @ 12.5 Hz
	0x08,	// auto sleep
	0x04,	// interrupt on free fall
	0x00	// all interrupts are handled by INT1 pin
};

const uint8_t fall_init[4] = {0x18, 0x03, 0xFF, 0x7F};
const uint8_t impact_init[4] = {0x30, 0x03, 0x01, 0x7F};
const uint8_t no_motion_init[4] = {0x08, 0x03, 0x02, 0xFF};

bool ADXL345_validation(void) {
    bool passed = false;
    if (SPI1_Open(ADXL345)) {
        CS_ACC_SetLow();
        if (SPI1_ByteExchange(DEVICE_ID) == 0xE5) {
            passed = true;
        }
        CS_ACC_SetHigh();
    }
    SPI1_Close();
    return passed;
}

bool ADXL345_init(void) {
    if (!SPI1_Open(ADXL345)) {
        return false;
    }
    
    struct Message msg;
    msg.registerAddr = THRESH_ACT;
    memset(msg.data, 0, sizeof(msg.data));
    memcpy(msg.data, ADXL345_init_settings, sizeof(ADXL345_init_settings));
    CS_ACC_SetLow();
    SPI1_BufferWrite(&msg, sizeof(ADXL345_init_settings) + 1);
    CS_ACC_SetHigh();

    msg.registerAddr = DATA_FORMAT;
    memset(msg.data, 0, sizeof(msg.data));
    msg.data[0] = 0x0B;
    CS_ACC_SetLow();
    SPI1_BufferWrite(&msg, 2);
    CS_ACC_SetHigh();
    
    SPI1_Close();
    return true;
}

bool SetupForFreefall(void) {
    if (!SPI1_Open(ADXL345)) {
        return false;
    }
    
    // Clear any pending interrupts
    CS_ACC_SetLow();
    SPI1_ByteExchange(INT_SOURCE);
    CS_ACC_SetHigh();
    
    /* Setup free fall parameters
     * Addr: 0x24 (Activity Threshold) = 1.5 g
     * Addr: 0x25 (Inactivity Threshold) = 0.1875 g
     * Addr: 0x26 (Inactivity Time) = 255 sec
     * Addr: 0x27 (Axis enable control) = 0b01111111
     */
    struct Message msg;
    msg.registerAddr = THRESH_ACT;
    memset(msg.data, 0, sizeof(msg.data));
    memcpy(msg.data, fall_init, sizeof(fall_init));
    CS_ACC_SetLow();
    SPI1_BufferWrite(&msg, sizeof(fall_init) + 1);
    CS_ACC_SetHigh();
    
    // Low power enabled & data rate of 12.5 Hz
    msg.registerAddr = BW_RATE;
    memset(msg.data, 0, sizeof(msg.data));
    msg.data[0] = 0x17;
    CS_ACC_SetLow();
    SPI1_BufferWrite(&msg, 2);
    CS_ACC_SetHigh();
    
    // Set interrupt to trigger on Activity
    msg.registerAddr = INT_ENABLE;
    memset(msg.data, 0, sizeof(msg.data));
    msg.data[0] = 0x10;
    CS_ACC_SetLow();
    SPI1_BufferWrite(&msg, 2);
    CS_ACC_SetHigh();
    
    // Clear any pending interrupts
    CS_ACC_SetLow();
    SPI1_ByteExchange(INT_SOURCE);
    CS_ACC_SetHigh();
    
    //Motion_State = Waiting_For_Freefall;
    
    SPI1_Close();
    return true;
}

bool setupForImpact(void) {
    if (!SPI1_Open(ADXL345)) {
        return false;
    }
    
    // Clear any pending interrupts
    CS_ACC_SetLow();
    SPI1_ByteExchange(INT_SOURCE);
    CS_ACC_SetHigh();
    
    /* Setup impact parameters
     * Addr: 0x24 (Activity Threshold) = 3 g
     * Addr: 0x25 (Inactivity Threshold) = 0.1875 g
     * Addr: 0x26 (Inactivity Time) = 1 sec
     * Addr: 0x27 (Axis enable control) = 0b01111111
     */
    struct Message msg;
    msg.registerAddr = THRESH_ACT;
    memset(msg.data, 0, sizeof(msg.data));
    memcpy(msg.data, impact_init, sizeof(impact_init));
    CS_ACC_SetLow();
    SPI1_BufferWrite(&msg, sizeof(impact_init) + 1);
    CS_ACC_SetHigh();
    
    // Low power enabled & data rate of 100 Hz
    msg.registerAddr = BW_RATE;
    memset(msg.data, 0, sizeof(msg.data));
    msg.data[0] = 0x1A;
    CS_ACC_SetLow();
    SPI1_BufferWrite(&msg, 2);
    CS_ACC_SetHigh();
    
    // Set interrupt to trigger on free fall
    msg.registerAddr = INT_ENABLE;
    memset(msg.data, 0, sizeof(msg.data));
    msg.data[0] = 0x04;
    CS_ACC_SetLow();
    SPI1_BufferWrite(&msg, 2);
    CS_ACC_SetHigh();
    
    // Clear any pending interrupts
    CS_ACC_SetLow();
    SPI1_ByteExchange(INT_SOURCE);
    CS_ACC_SetHigh();
    
    SPI1_Close();
    return true;
}

bool setupForInactivity(void) {
    
}