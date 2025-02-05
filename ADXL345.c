/*
 * File:   ADXL345.c
 * Author: Austin
 *
 * Created on January 30, 2025, 10:44 AM
 */

#include "ADXL345.h"

#define NUM_SAMPLES 128 // number of acc readings during calibration

const uint16_t acceleration_squared_threshold = 1200; // calculated by George

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

bool ADXL345_init(void) {
    while (!SPI1_Open(ADXL345)) {
        SPI1_Close();
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

void saveOffsets(uint8_t x_axis, uint8_t y_axis, uint8_t z_axis) {
    while (!SPI1_Open(ADXL345)) {
        SPI1_Close();
    }
    
    struct Message msg;
    msg.registerAddr = OFSX;
    memset(msg.data, 0, sizeof(msg.data));
    msg.data[0] = x_axis;
    CS_ACC_SetLow();
    SPI1_BufferWrite(&msg, 2);
    CS_ACC_SetHigh();
    
    msg.registerAddr = OFSY;
    msg.data[0] = y_axis;
    CS_ACC_SetLow();
    SPI1_BufferWrite(&msg, 2);
    CS_ACC_SetHigh();
    
    msg.registerAddr = OFSZ;
    msg.data[0] = z_axis;
    CS_ACC_SetLow();
    SPI1_BufferWrite(&msg, 2);
    CS_ACC_SetHigh();
    
    SPI1_Close();
}

void ADXL345_ClearInterrupt(void) {
    while (!SPI1_Open(ADXL345)) {
        SPI1_Close();
    }
    
    // Clear any pending interrupts
    CS_ACC_SetLow();
    SPI1_ByteExchange(INT_SOURCE);
    CS_ACC_SetHigh();
    
    SPI1_Close();
}

void setupForFreefall(void) {
    while (!SPI1_Open(ADXL345)) {
        SPI1_Close();
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
        
    SPI1_Close();
}

void setupForImpact(void) {
    while (!SPI1_Open(ADXL345)) {
        SPI1_Close();
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
}

void setupForInactivity(void) {
    while (!SPI1_Open(ADXL345)) {
        SPI1_Close();
    }
    
    // Clear any pending interrupts
    CS_ACC_SetLow();
    SPI1_ByteExchange(INT_SOURCE);
    CS_ACC_SetHigh();
    
    /* Setup impact parameters
     * Addr: 0x24 (Activity Threshold) = 0.5 g
     * Addr: 0x25 (Inactivity Threshold) = 0.1875 g
     * Addr: 0x26 (Inactivity Time) = 2 sec
     * Addr: 0x27 (Axis enable control) = 0b11111111
     */
    struct Message msg;
    msg.registerAddr = THRESH_ACT;
    memset(msg.data, 0, sizeof(msg.data));
    memcpy(msg.data, no_motion_init, sizeof(no_motion_init));
    CS_ACC_SetLow();
    SPI1_BufferWrite(&msg, sizeof(no_motion_init) + 1);
    CS_ACC_SetHigh();
    
    // Low power enabled & data rate of 12.5 Hz
    msg.registerAddr = BW_RATE;
    memset(msg.data, 0, sizeof(msg.data));
    msg.data[0] = 0x17;
    CS_ACC_SetLow();
    SPI1_BufferWrite(&msg, 2);
    CS_ACC_SetHigh();
    
    // Set interrupt to trigger on inactivity
    msg.registerAddr = INT_ENABLE;
    memset(msg.data, 0, sizeof(msg.data));
    msg.data[0] = 0x08;
    CS_ACC_SetLow();
    SPI1_BufferWrite(&msg, 2);
    CS_ACC_SetHigh();
    
    // Clear any pending interrupts
    CS_ACC_SetLow();
    SPI1_ByteExchange(INT_SOURCE);
    CS_ACC_SetHigh();
    
    SPI1_Close();
}

bool orientation_Up(void) {
    while (!SPI1_Open(ADXL345)) {
        SPI1_Close();
    }
    int8_t acc_data[6] = {0};
    int16_t g_deltaX, g_deltaY, g_deltaZ;
    
    struct Message msg;
    msg.registerAddr = DATA_FORMAT;
    msg.data[0] = 0x0C; // change to 2G, left justified, full resolution
    CS_ACC_SetLow();
    SPI1_BufferWrite(&msg, 2);
    CS_ACC_SetHigh();
    
    __delay_ms(10);
    
    // Read accelerometer data
    CS_ACC_SetLow();
    SPI1_ByteWrite(DATAX0);
    SPI1_BufferRead((uint8_t *)acc_data, sizeof(acc_data));
    CS_ACC_SetHigh();
    SPI1_Close();
    
    // Save X,Y,Z readings
    g_deltaX = (int8_t)acc_data[1] - 0x40;
    g_deltaY = (int8_t)acc_data[3];
    g_deltaZ = (int8_t)acc_data[5];
    
    // Calculate magnitude of acceleration and compare to threshold
    g_deltaX *= g_deltaX;
    g_deltaY *= g_deltaY;
    g_deltaZ *= g_deltaZ;
    int g_magnitude = g_deltaX + g_deltaY + g_deltaZ;
    if (g_magnitude < acceleration_squared_threshold) {
        return true;
    } else {
        return false;
    }
}

bool calibrate(void) {
    int offset_0g_X, offset_0g_Y, offset_0g_Z;
    int acc_data[6] = {0};
    int sum_X = 0, sum_Y = 0, sum_Z = 0;
    int sum_X_avg, sum_Y_avg, sum_Z_avg;
    
    while (!SPI1_Open(ADXL345)) {
        SPI1_Close();
    }
    
    struct Message msg;
    msg.registerAddr = DATA_FORMAT;
    msg.data[0] = 0x0C; // change to 2G, left justified, full resolution
    CS_ACC_SetLow();
    SPI1_BufferWrite(&msg, 2);
    CS_ACC_SetHigh();
    
    /* Blink Green */
    while(!SW1_GetValue()) {
        GRN_LED_SetHigh();
        __delay_ms(100);
        CLRWDT();
        GRN_LED_SetLow();
        __delay_ms(100);
        CLRWDT();
    }
    
    CLRWDT();
    __delay_ms(1500); // wait 1.5 seconds for device to settle;
    CLRWDT();
    
    for(int i = 0; i < NUM_SAMPLES; i++) {
        // Read accelerometer data
        CS_ACC_SetLow();
        SPI1_ByteWrite(DATAX0);
        SPI1_BufferRead((uint8_t *)acc_data, sizeof(acc_data));
        CS_ACC_SetHigh();
        
        sum_X += acc_data[1];
        sum_Y += acc_data[3];
        sum_Z += acc_data[5];
        
        __delay_ms(5); // wait before next sample
        CLRWDT();
    }
    
    // There should never be an offset of 0
    if (sum_Z == 0) return false;
    
    // Bit shift instead of divide to find the average
    sum_X_avg = sum_X >> 7;
    sum_Y_avg = sum_Y >> 7;
    
    /* Check if offsets are within the datasheets spec */
    // handle negative vs positive
    if (sum_X_avg & 0x80) {
        if (~(sum_X_avg) + 1 >= 0x10) return false;
    } else {
        if (sum_X_avg >= 0x10) return false;
    }
    
    if (sum_Y_avg & 0x80) {
        if (~(sum_Y_avg) + 1 >= 0x10) return false;
    } else {
        if (sum_Y_avg >= 0x10) return false;
    }
    
    offset_0g_X = -sum_X_avg;
    offset_0g_Y = -sum_Y_avg;
    
    sum_Z_avg = sum_Z >> 7; // average of Z samples
    sum_Z = 0; // reset sum for next test
    
    /* Blink RED */
    while(!SW1_GetValue()) {
        RED_LED_SetHigh();
        __delay_ms(100);
        CLRWDT();
        RED_LED_SetLow();
        __delay_ms(100);
        CLRWDT();
    }
    
    CLRWDT();
    __delay_ms(1500); // wait 1.5 seconds for device to settle;
    CLRWDT();
    
    for(int i = 0; i < NUM_SAMPLES; i++) {
        // Read accelerometer data
        CS_ACC_SetLow();
        SPI1_ByteWrite(DATAX0);
        SPI1_BufferRead((uint8_t *)acc_data, sizeof(acc_data));
        CS_ACC_SetHigh();
        
        sum_Z += acc_data[5];
        
        __delay_ms(5); // wait before next sample
        CLRWDT();
    }
    
    int16_t Z_n1g = sum_Z >> 7; // calculate average of Z samples
    sum_Z_avg = (Z_n1g + sum_Z_avg) >> 1; // average of negative and positive
    
    /* Check if offsets are within the datasheets spec */
    // handle negative vs positive
    if (sum_Z_avg & 0x80) {
        if (~(sum_Z_avg) + 1 >= 0x20) return false;
    } else {
        if (sum_Z_avg >= 0x20) return false;
    }
    
    offset_0g_Z = -sum_Z_avg;
    
    saveOffsets((uint8_t)offset_0g_X, (uint8_t)offset_0g_Y, (uint8_t)offset_0g_Z); // write offsets to acc
    
    // save offsets to eeprom in the case of a reset
    EEPROM_Write(EE_X_OFFSET_ADDR, (uint8_t)offset_0g_X);
    EEPROM_Write(EE_Y_OFFSET_ADDR, (uint8_t)offset_0g_Y);
    EEPROM_Write(EE_Z_OFFSET_ADDR, (uint8_t)offset_0g_Z);
    
    EEPROM_Write(EE_CAL_STATUS_ADDR, CAL_DONE);
    
    msg.registerAddr = DATA_FORMAT;
    msg.data[0] = 0x0B; // change to 16G, right justified, full resolution
    CS_ACC_SetLow();
    SPI1_BufferWrite(&msg, 2);
    CS_ACC_SetHigh();
    
    SPI1_Close();
    return true;
}