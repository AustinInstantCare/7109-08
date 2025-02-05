/*
 * File:   fall.c
 * Author: Austin
 *
 * Created on February 4, 2025, 1:21 PM
 */


#include "fall.h"

uint16_t timer_20ms;
uint16_t orientation_check_timer_20ms;
uint8_t good_orientation_count;

void MotionEventHandler(State_t *state) {
    timer_20ms++;
    orientation_check_timer_20ms++;
    
    switch (*state) {
        case WAITING_FOR_FREEFALL:
            // free fall detected
            if (INT1_GetValue()) {
                setupForImpact();
                timer_20ms = 0;
                *state = WAITING_FOR_IMPACT;
            }
            break;
        
        case WAITING_FOR_IMPACT:
            // impact detected
            if (INT1_GetValue()) {
                setupForInactivity();
                *state = WAITING_FOR_INACTIVITY;
            }
            // No impact detected - Timeout!
            else if (timer_20ms >= WAITING_FOR_IMPACT_TIMEOUT) {
                setupForFreefall();
                *state = WAITING_FOR_FREEFALL;
            }
            break;
        
        case WAITING_FOR_INACTIVITY:
            // inactivity detected
            if (INT1_GetValue()) {
                if (!orientation_Up()) {
                    RED_LED_SetHigh();
                    __delay_ms(100);
                    RED_LED_SetLow();
                    orientation_check_timer_20ms = 0;
                    good_orientation_count = 0;
                    ADXL345_ClearInterrupt();
                    *state = WAITING_FOR_TIMEOUT;
                } else {
                    setupForFreefall();
                    *state = WAITING_FOR_FREEFALL;
                }
            }
            // activity detected - Timeout!
            else if (timer_20ms >= WAITING_FOR_INACTIVITY_TIMEOUT) {
                setupForFreefall();
                *state = WAITING_FOR_FREEFALL;
            }
            break;
        
        case WAITING_FOR_TIMEOUT:
            // valid fall detected
            if (timer_20ms >= WAITING_FOR_FREEFALL) {
                *state = FALL_DETECTED;
            }
            // Check orientation every 100 ms
            else if (orientation_check_timer_20ms >= ORIENTATION_CHECK_TIMEOUT) {
                orientation_check_timer_20ms = 0;
                if (orientation_Up()) {
                    // Cancel Fall if good orientation for 1 second straight
                    if (good_orientation_count++ >= GOOD_ORIENTATION_TIMEOUT) {
                        GRN_LED_SetHigh();
                        __delay_ms(100);
                        GRN_LED_SetLow();
                        setupForFreefall();
                        *state = WAITING_FOR_FREEFALL;
                    }
                } else {
                    good_orientation_count = 0; // reset count
                }
            }
            break;
        
        case FALL_DETECTED:
            // State must be handled in main loop
            break;
    }
}