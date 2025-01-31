/*
 * File:   ADXL345.c
 * Author: Austin
 *
 * Created on January 30, 2025, 10:44 AM
 */

#include "ADXL345.h"

const uint8_t ADXL345_init_settings[13] = {
    THRESH_ACT, // Start register address
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

const uint8_t ADXL345_data_format[2] = {
    DATA_FORMAT,    // register Address
    0x0B            // 0b00001011
};

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
    CS_ACC_SetLow();
    SPI1_BufferWrite(ADXL345_init_settings, sizeof(ADXL345_init_settings));
    CS_ACC_SetHigh();
    NOP();
    CS_ACC_SetLow();
    SPI1_BufferWrite(ADXL345_data_format, sizeof(ADXL345_data_format));
    CS_ACC_SetHigh();
    return true;
}

void ADXL345_write(uint8_t registerAddr, size_t buffer_size, uint8_t *data) {
    data[0] = registerAddr;
    
    SPI1_Open(ADXL345);
    CS_ACC_SetLow();
    SPI1_BufferExchange(data, buffer_size);
    CS_ACC_SetHigh();
    SPI1_Close();
}
