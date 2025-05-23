/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 3.1.1
*/

/*
� [2024] Microchip Technology Inc. and its subsidiaries.

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

#include "../pins.h"
#include "../../../nrf24.h"
#include "../../timer/tmr0.h"


void PIN_MANAGER_Initialize(void)
{
   /**
    LATx registers
    */
    LATA = 0x0;
    LATB = 0x0;
    LATC = 0x0;
    LATD = 0x0;
    LATE = 0x0;
    LATF = 0x0;
    /**
    ODx registers
    */
    ODCONA = 0x0;
    ODCONB = 0x0;
    ODCONC = 0x0;
    ODCOND = 0x0;
    ODCONE = 0x0;
    ODCONF = 0x0;

    /**
    TRISx registers
    */
    TRISA = 0xAF;
    TRISB = 0xFF;
    TRISC = 0xE7; //0 for sck, act
    TRISD = 0xFF;
    TRISE = 0xF;
    TRISF = 0xFB;

    /**
    ANSELx registers
    */
    ANSELA = 0xAF;
    ANSELB = 0xFB;
    ANSELC = 0xC7;
    ANSELD = 0xFF;
    ANSELE = 0x7;
    ANSELF = 0xFB;

    /**
    WPUx registers
    */
    WPUA = 0x0;
    WPUB = 0x0;
    WPUC = 0x0;
    WPUD = 0x0;
    WPUE = 0x0;
    WPUF = 0x0;


    /**
    SLRCONx registers
    */
    SLRCONA = 0xFF;
    SLRCONB = 0xFF;
    SLRCONC = 0xFF;
    SLRCOND = 0xFF;
    SLRCONE = 0x7;
    SLRCONF = 0xFF;

    /**
    INLVLx registers
    */
    INLVLA = 0xFF;
    INLVLB = 0xFF;
    INLVLC = 0xFF;
    INLVLD = 0xFF;
    INLVLE = 0xF;
    INLVLF = 0xFF;

   /**
    RxyI2C | RxyFEAT registers   
    */
    RB1I2C = 0x0;
    RB2I2C = 0x0;
    RC3I2C = 0x0;
    RC4I2C = 0x0;
    /**
    PPS registers
    */
    SPI1SDIPPS = 0x15; //RC5->SPI1:SDI1;
    RC4PPS = 0x32;  //RC4->SPI1:SDO1;
    SPI1SCKPPS = 0x13;  //RC3->SPI1:SCK1;
    RC3PPS = 0x31;  //RC3->SPI1:SCK1;

   /**
    IOCx registers 
    */
    IOCAP = 0x0;
    IOCAN = 0x0;
    IOCAF = 0x0;
    IOCBP = 0x0;
    IOCBN = 0x0;
    IOCBF = 0x0;
    IOCCP = 0x0;
    IOCCN = 0x0;
    IOCCF = 0x0;
    IOCEP = 0x0;
    IOCEN = 0x0;
    IOCEF = 0x0;
    
    IOCBNbits.IOCBN2 = 1;
    
    

    PIE0bits.IOCIE = 1;      
    
    IN_MIC_SetAnalogMode();
    IN_MIC_SetDigitalInput();
    
    CSN_SetDigitalOutput();
    CSN_SetDigitalMode();
    
    CE_SetDigitalOutput();
    CE_SetDigitalMode();
    
    IR_BTN_SetAnalogMode();
    IR_BTN_SetDigitalInput();
    
    IRQ_SetDigitalInput();
    IRQ_SetDigitalMode();
    
    IN_BTN_SetAnalogMode();
    IN_BTN_SetDigitalInput();
    
    SCK_SetDigitalOutput();
    SCK_SetDigitalMode();
    
    MOSI_SetDigitalOutput();
    MOSI_SetDigitalMode();
    
    MISO_SetDigitalInput();
    MISO_SetDigitalMode();
    
    VRx_SetAnalogMode();
    VRx_SetDigitalInput();
    
    PWR_SetDigitalMode();
    PWR_SetDigitalOutput();
    PWR_SetHigh();
    
    VRy_SetAnalogMode();
    VRy_SetDigitalInput();
   
    
}
  
void PIN_MANAGER_IOC(void)
{
    extern volatile uint8_t transmitted;
    extern volatile uint8_t done;
    extern volatile uint8_t ind;
    uint8_t temp = IOCBF;  // Read the current IOC flags
    IOCBF &= ~temp;        // Clear only the bits that were set
    
    extern volatile uint8_t irq_ready;
    
    CE = 0;
    irq_ready = 1;
    
    transmitted += 1;
    if (transmitted == 64){ 
        done = 1;
    }
}
/**
 End of File
*/