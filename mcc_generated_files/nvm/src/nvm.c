/**
 * @file nvm.c
 *
 * @ingroup nvm_driver
 *
 * @brief Contains the implementation file for the NVM driver.
 *
 * @version NVM Driver Version 1.0.1
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

#include "../nvm.h"

/*
 * AoU: These variables are placed in the Access RAM using the "__near" qualifier.
 *      Additionally, "Address Qualifiers" must be configured to the "Require" under
 *      "Project Properties -> XC8 Compiler -> Optimizations".
 */
__near volatile static uint8_t unlockKeyLow;
__near volatile static uint8_t unlockKeyHigh;

void NVM_Initialize(void)
{
    NVM_StatusClear();
}

bool NVM_IsBusy(void)
{
    return (EECON1bits.WR || EECON1bits.RD);
}

nvm_status_t NVM_StatusGet(void)
{
    if (EECON1bits.WRERR == 1)
    {
        return NVM_ERROR;
    }
    else
    {
        return NVM_OK;
    }
}

void NVM_StatusClear(void)
{
    EECON1bits.WRERR = 0;
}

void NVM_UnlockKeySet(uint16_t unlockKey)
{
    unlockKeyHigh = (uint8_t) (unlockKey >> 8);
    unlockKeyLow = (uint8_t) unlockKey;
}

void NVM_UnlockKeyClear(void)
{
    unlockKeyHigh = 0x00;
    unlockKeyLow = 0x00;
}

flash_data_t FLASH_Read(flash_address_t address)
{
    //Save global interrupt enable bit value
    uint8_t globalInterruptBitValue = INTCONbits.GIE; 

    //Load EEADR with address of the word
    EEADRH = (uint8_t) (address >> 8);
    EEADRL = (uint8_t) address;

    //Disable global interrupt
    INTCONbits.GIE = 0;   

    //Access Program Flash Memory
    EECON1bits.CFGS = 0;
    EECON1bits.EEPGD = 1;    
    
    //Initiate Read
    EECON1bits.RD = 1;
    NOP();
    NOP();    

    //Restore global interrupt enable bit value
    INTCONbits.GIE = globalInterruptBitValue; 

    return ((flash_data_t) ((EEDATH << 8) | EEDATL));
}

nvm_status_t FLASH_RowWrite(flash_address_t address, flash_data_t *dataBuffer)
{    
    uint8_t flashDataCount = PROGMEM_PAGE_SIZE;
    
    //Save global interrupt enable bit value
    uint8_t globalInterruptBitValue = INTCONbits.GIE;   

    //Access program Flash memory
    EECON1bits.CFGS = 0;
    EECON1bits.EEPGD = 1;   
    
    //Enable write operation
    EECON1bits.WREN = 1;   
    
    //Load Write Latches Only
    LWLO = 1;
    
    while (flashDataCount-- > 0U)
    {
        EEADRH = (uint8_t) (address >> 8);
        EEADRL = (uint8_t) address;
        address++;
        
        EEDATH = (uint8_t) (*dataBuffer >> 8);
        EEDATL = (uint8_t) (*dataBuffer);
        dataBuffer++;
        
        //If last latch to be written
        if (flashDataCount == 0U)
        {
            //Write program Flash memory 
            LWLO = 0;
        }
        
        //Disable global interrupt
        INTCONbits.GIE = 0;    
        
        //Perform the unlock sequence
        EECON2 = unlockKeyLow;
        EECON2 = unlockKeyHigh;
        EECON1bits.WR = 1;
        NOP();
        NOP();
          
        //Restore global interrupt enable bit value
        INTCONbits.GIE = globalInterruptBitValue; 
    }
    
    //Disable write operation
    EECON1bits.WREN = 0;      
    
    if (EECON1bits.WRERR == 1) 
    {
        return NVM_ERROR;
    } 
    else 
    {
        return NVM_OK;
    }
}

nvm_status_t FLASH_PageErase(flash_address_t address)
{
    //Save global interrupt enable bit value
    uint8_t globalInterruptBitValue = INTCONbits.GIE;    
    
    //Load EEADR with the start address of the memory row
    EEADRH = (uint8_t) (address >> 8);
    EEADRL = (uint8_t) address;

    //Access program Flash memory
    EECON1bits.CFGS = 0;
    EECON1bits.EEPGD = 1;
    
    //Performs an erase operation with the next WR command
    EECON1bits.FREE = 1;   
    
    //Enable erase operation
    EECON1bits.WREN = 1;    

    //Disable global interrupt
    INTCONbits.GIE = 0; 
    
    //Perform the unlock sequence
    EECON2 = unlockKeyLow;
    EECON2 = unlockKeyHigh;
    EECON1bits.WR = 1;
    NOP();
    NOP();
    
    //Restore global interrupt enable bit value
    INTCONbits.GIE = globalInterruptBitValue;	

    //Disable erase operation
    EECON1bits.WREN = 0;      
    
    if (EECON1bits.WRERR == 1) 
    {
        return NVM_ERROR;
    } 
    else 
    {
        return NVM_OK;
    }
}

flash_address_t FLASH_PageAddressGet(flash_address_t address)
{
    return (flash_address_t) (address & ((PROGMEM_SIZE - 1U) ^ (PROGMEM_PAGE_SIZE - 1U)));
}

uint16_t FLASH_PageOffsetGet(flash_address_t address)
{
    return (uint16_t) (address & (PROGMEM_PAGE_SIZE - 1U));
}

eeprom_data_t EEPROM_Read(eeprom_address_t address)
{
    //Access EEPROM
    EECON1bits.CFGS = 0;
    EECON1bits.EEPGD = 0;  
    
    //Load EEADR with the EEPROM address
    EEADRH = (uint8_t) (address >> 8);
    EEADRL = (uint8_t) address;
    
    //Initiate Read
    EECON1bits.RD = 1;
    NOP();  // NOPs may be required for latency at high frequencies
    NOP();

    return EEDATL;
}

void EEPROM_Write(eeprom_address_t address, eeprom_data_t data)
{
    //Save global interrupt enable bit value
    uint8_t globalInterruptBitValue = INTCONbits.GIE;

    //Access EEPROM
    EECON1bits.CFGS = 0;
    EECON1bits.EEPGD = 0;
    
    //Enable write operation
    EECON1bits.WREN = 1;

    //Load EEADR with the EEPROM address
    EEADRH = (uint8_t) (address >> 8);
    EEADRL = (uint8_t) address;

    //Load NVMDAT with the desired value
    EEDATL = data;

    //Disable global interrupt
    INTCONbits.GIE = 0;

    //Perform the unlock sequence
    EECON2 = unlockKeyLow;
    EECON2 = unlockKeyHigh;
    EECON1bits.WR = 1;
    NOP();
    NOP();

    //Restore global interrupt enable bit value
    INTCONbits.GIE = globalInterruptBitValue; 

    //Disable write operation
    EECON1bits.WREN = 0;
}
