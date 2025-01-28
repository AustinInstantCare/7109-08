/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.0.0
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

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RA0 aliases
#define CTS_TRIS                 TRISAbits.TRISA0
#define CTS_LAT                  LATAbits.LATA0
#define CTS_PORT                 PORTAbits.RA0
#define CTS_WPU                  WPUAbits.WPUA0
#define CTS_OD                   ODCONAbits.
#define CTS_ANS                  ANSELAbits.ANSA0
#define CTS_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define CTS_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define CTS_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define CTS_GetValue()           PORTAbits.RA0
#define CTS_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define CTS_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define CTS_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define CTS_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define CTS_SetPushPull()        do { ODCONAbits. = 0; } while(0)
#define CTS_SetOpenDrain()       do { ODCONAbits. = 1; } while(0)
#define CTS_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define CTS_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)
// get/set IO_RA1 aliases
#define SW1_TRIS                 TRISAbits.TRISA1
#define SW1_LAT                  LATAbits.LATA1
#define SW1_PORT                 PORTAbits.RA1
#define SW1_WPU                  WPUAbits.WPUA1
#define SW1_OD                   ODCONAbits.
#define SW1_ANS                  ANSELAbits.ANSA1
#define SW1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define SW1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define SW1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define SW1_GetValue()           PORTAbits.RA1
#define SW1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define SW1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define SW1_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define SW1_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define SW1_SetPushPull()        do { ODCONAbits. = 0; } while(0)
#define SW1_SetOpenDrain()       do { ODCONAbits. = 1; } while(0)
#define SW1_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define SW1_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)
#define RA1_SetInterruptHandler  SW1_SetInterruptHandler
// get/set IO_RA2 aliases
#define INT1_TRIS                 TRISAbits.TRISA2
#define INT1_LAT                  LATAbits.LATA2
#define INT1_PORT                 PORTAbits.RA2
#define INT1_WPU                  WPUAbits.WPUA2
#define INT1_OD                   ODCONAbits.
#define INT1_ANS                  ANSELAbits.ANSA2
#define INT1_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define INT1_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define INT1_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define INT1_GetValue()           PORTAbits.RA2
#define INT1_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define INT1_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define INT1_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define INT1_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define INT1_SetPushPull()        do { ODCONAbits. = 0; } while(0)
#define INT1_SetOpenDrain()       do { ODCONAbits. = 1; } while(0)
#define INT1_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define INT1_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)
// get/set IO_RA4 aliases
#define GRN_LED_TRIS                 TRISAbits.TRISA4
#define GRN_LED_LAT                  LATAbits.LATA4
#define GRN_LED_PORT                 PORTAbits.RA4
#define GRN_LED_WPU                  WPUAbits.WPUA4
#define GRN_LED_OD                   ODCONAbits.
#define GRN_LED_ANS                  ANSELAbits.ANSA4
#define GRN_LED_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define GRN_LED_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define GRN_LED_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define GRN_LED_GetValue()           PORTAbits.RA4
#define GRN_LED_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define GRN_LED_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define GRN_LED_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define GRN_LED_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define GRN_LED_SetPushPull()        do { ODCONAbits. = 0; } while(0)
#define GRN_LED_SetOpenDrain()       do { ODCONAbits. = 1; } while(0)
#define GRN_LED_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define GRN_LED_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)
// get/set IO_RA5 aliases
#define RED_LED_TRIS                 TRISAbits.TRISA5
#define RED_LED_LAT                  LATAbits.LATA5
#define RED_LED_PORT                 PORTAbits.RA5
#define RED_LED_WPU                  WPUAbits.WPUA5
#define RED_LED_OD                   ODCONAbits.
#define RED_LED_ANS                  ANSELAbits.
#define RED_LED_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define RED_LED_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define RED_LED_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define RED_LED_GetValue()           PORTAbits.RA5
#define RED_LED_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define RED_LED_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define RED_LED_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define RED_LED_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define RED_LED_SetPushPull()        do { ODCONAbits. = 0; } while(0)
#define RED_LED_SetOpenDrain()       do { ODCONAbits. = 1; } while(0)
#define RED_LED_SetAnalogMode()      do { ANSELAbits. = 1; } while(0)
#define RED_LED_SetDigitalMode()     do { ANSELAbits. = 0; } while(0)
// get/set IO_RC0 aliases
#define SCLK_TRIS                 TRISCbits.TRISC0
#define SCLK_LAT                  LATCbits.LATC0
#define SCLK_PORT                 PORTCbits.RC0
#define SCLK_WPU                  WPUCbits.WPUC0
#define SCLK_OD                   ODCONCbits.
#define SCLK_ANS                  ANSELCbits.ANSC0
#define SCLK_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define SCLK_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define SCLK_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define SCLK_GetValue()           PORTCbits.RC0
#define SCLK_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define SCLK_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define SCLK_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define SCLK_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define SCLK_SetPushPull()        do { ODCONCbits. = 0; } while(0)
#define SCLK_SetOpenDrain()       do { ODCONCbits. = 1; } while(0)
#define SCLK_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define SCLK_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)
// get/set IO_RC1 aliases
#define MISO_TRIS                 TRISCbits.TRISC1
#define MISO_LAT                  LATCbits.LATC1
#define MISO_PORT                 PORTCbits.RC1
#define MISO_WPU                  WPUCbits.WPUC1
#define MISO_OD                   ODCONCbits.
#define MISO_ANS                  ANSELCbits.ANSC1
#define MISO_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define MISO_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define MISO_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define MISO_GetValue()           PORTCbits.RC1
#define MISO_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define MISO_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define MISO_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define MISO_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define MISO_SetPushPull()        do { ODCONCbits. = 0; } while(0)
#define MISO_SetOpenDrain()       do { ODCONCbits. = 1; } while(0)
#define MISO_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define MISO_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)
// get/set IO_RC2 aliases
#define MOSI_TRIS                 TRISCbits.TRISC2
#define MOSI_LAT                  LATCbits.LATC2
#define MOSI_PORT                 PORTCbits.RC2
#define MOSI_WPU                  WPUCbits.WPUC2
#define MOSI_OD                   ODCONCbits.
#define MOSI_ANS                  ANSELCbits.ANSC2
#define MOSI_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define MOSI_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define MOSI_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define MOSI_GetValue()           PORTCbits.RC2
#define MOSI_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define MOSI_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define MOSI_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define MOSI_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define MOSI_SetPushPull()        do { ODCONCbits. = 0; } while(0)
#define MOSI_SetOpenDrain()       do { ODCONCbits. = 1; } while(0)
#define MOSI_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define MOSI_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)
// get/set IO_RC3 aliases
#define CS_RF_TRIS                 TRISCbits.TRISC3
#define CS_RF_LAT                  LATCbits.LATC3
#define CS_RF_PORT                 PORTCbits.RC3
#define CS_RF_WPU                  WPUCbits.WPUC3
#define CS_RF_OD                   ODCONCbits.
#define CS_RF_ANS                  ANSELCbits.ANSC3
#define CS_RF_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define CS_RF_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define CS_RF_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define CS_RF_GetValue()           PORTCbits.RC3
#define CS_RF_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define CS_RF_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define CS_RF_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define CS_RF_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define CS_RF_SetPushPull()        do { ODCONCbits. = 0; } while(0)
#define CS_RF_SetOpenDrain()       do { ODCONCbits. = 1; } while(0)
#define CS_RF_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define CS_RF_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)
// get/set IO_RC4 aliases
#define CS_ACC_TRIS                 TRISCbits.TRISC4
#define CS_ACC_LAT                  LATCbits.LATC4
#define CS_ACC_PORT                 PORTCbits.RC4
#define CS_ACC_WPU                  WPUCbits.WPUC4
#define CS_ACC_OD                   ODCONCbits.
#define CS_ACC_ANS                  ANSELCbits.
#define CS_ACC_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define CS_ACC_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define CS_ACC_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define CS_ACC_GetValue()           PORTCbits.RC4
#define CS_ACC_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define CS_ACC_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define CS_ACC_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define CS_ACC_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define CS_ACC_SetPushPull()        do { ODCONCbits. = 0; } while(0)
#define CS_ACC_SetOpenDrain()       do { ODCONCbits. = 1; } while(0)
#define CS_ACC_SetAnalogMode()      do { ANSELCbits. = 1; } while(0)
#define CS_ACC_SetDigitalMode()     do { ANSELCbits. = 0; } while(0)
// get/set IO_RC5 aliases
#define SDN_TRIS                 TRISCbits.TRISC5
#define SDN_LAT                  LATCbits.LATC5
#define SDN_PORT                 PORTCbits.RC5
#define SDN_WPU                  WPUCbits.WPUC5
#define SDN_OD                   ODCONCbits.
#define SDN_ANS                  ANSELCbits.
#define SDN_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define SDN_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define SDN_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define SDN_GetValue()           PORTCbits.RC5
#define SDN_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define SDN_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define SDN_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define SDN_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define SDN_SetPushPull()        do { ODCONCbits. = 0; } while(0)
#define SDN_SetOpenDrain()       do { ODCONCbits. = 1; } while(0)
#define SDN_SetAnalogMode()      do { ANSELCbits. = 1; } while(0)
#define SDN_SetDigitalMode()     do { ANSELCbits. = 0; } while(0)
/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the SW1 pin functionality
 * @param none
 * @return none
 */
void SW1_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for SW1 pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for SW1 at application runtime.
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void SW1_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for SW1 pin.
 *        This is a dynamic interrupt handler to be used together with the SW1_SetInterruptHandler() method.
 *        This handler is called every time the SW1 ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*SW1_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for SW1 pin. 
 *        This is a predefined interrupt handler to be used together with the SW1_SetInterruptHandler() method.
 *        This handler is called every time the SW1 ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void SW1_DefaultInterruptHandler(void);


#endif // PINS_H
/**
 End of File
*/