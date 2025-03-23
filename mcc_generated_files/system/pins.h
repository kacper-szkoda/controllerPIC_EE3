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
 * @version Driver Version  3.1.1
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

// get/set RA1 aliases
#define IO_RA1_TRIS                 TRISAbits.TRISA1
#define IO_RA1_LAT                  LATAbits.LATA1
#define IO_RA1_PORT                 PORTAbits.RA1
#define IO_RA1_WPU                  WPUAbits.WPUA1
#define IO_RA1_OD                   ODCONAbits.ODCA1
#define IO_RA1_ANS                  ANSELAbits.ANSELA1
#define IO_RA1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define IO_RA1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define IO_RA1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define IO_RA1_GetValue()           PORTAbits.RA1
#define IO_RA1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define IO_RA1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define IO_RA1_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define IO_RA1_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define IO_RA1_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define IO_RA1_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define IO_RA1_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define IO_RA1_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set RA4 aliases
#define CSN_TRIS                 TRISAbits.TRISA4
#define CSN_LAT                  LATAbits.LATA4
#define CSN_PORT                 PORTAbits.RA4
#define CSN_WPU                  WPUAbits.WPUA4
#define CSN_OD                   ODCONAbits.ODCA4
#define CSN_ANS                  ANSELAbits.ANSELA4
#define CSN_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define CSN_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define CSN_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define CSN_GetValue()           PORTAbits.RA4
#define CSN_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define CSN_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define CSN_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define CSN_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define CSN_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define CSN_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define CSN_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define CSN_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set RA6 aliases
#define CE_TRIS                 TRISAbits.TRISA6
#define CE_LAT                  LATAbits.LATA6
#define CE_PORT                 PORTAbits.RA6
#define CE_WPU                  WPUAbits.WPUA6
#define CE_OD                   ODCONAbits.ODCA6
#define CE_ANS                  ANSELAbits.ANSELA6
#define CE_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define CE_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define CE_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define CE_GetValue()           PORTAbits.RA6
#define CE_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define CE_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define CE_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define CE_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define CE_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define CE_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define CE_SetAnalogMode()      do { ANSELAbits.ANSELA6 = 1; } while(0)
#define CE_SetDigitalMode()     do { ANSELAbits.ANSELA6 = 0; } while(0)

// get/set RB2 aliases
#define IRQ_TRIS                 TRISBbits.TRISB2
#define IRQ_LAT                  LATBbits.LATB2
#define IRQ_PORT                 PORTBbits.RB2
#define IRQ_WPU                  WPUBbits.WPUB2
#define IRQ_OD                   ODCONBbits.ODCB2
#define IRQ_ANS                  ANSELBbits.ANSELB2
#define IRQ_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define IRQ_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define IRQ_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define IRQ_GetValue()           PORTBbits.RB2
#define IRQ_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define IRQ_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define IRQ_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define IRQ_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define IRQ_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define IRQ_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define IRQ_SetAnalogMode()      do { ANSELBbits.ANSELB2 = 1; } while(0)
#define IRQ_SetDigitalMode()     do { ANSELBbits.ANSELB2 = 0; } while(0)
#define RB2_SetInterruptHandler  IRQ_SetInterruptHandler

// get/set RC3 aliases
#define SCK_TRIS                 TRISCbits.TRISC3
#define SCK_LAT                  LATCbits.LATC3
#define SCK_PORT                 PORTCbits.RC3
#define SCK_WPU                  WPUCbits.WPUC3
#define SCK_OD                   ODCONCbits.ODCC3
#define SCK_ANS                  ANSELCbits.ANSELC3
#define SCK_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SCK_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SCK_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SCK_GetValue()           PORTCbits.RC3
#define SCK_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SCK_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define SCK_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define SCK_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define SCK_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define SCK_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define SCK_SetAnalogMode()      do { ANSELCbits.ANSELC3 = 1; } while(0)
#define SCK_SetDigitalMode()     do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 aliases
#define MOSI_TRIS                 TRISCbits.TRISC4
#define MOSI_LAT                  LATCbits.LATC4
#define MOSI_PORT                 PORTCbits.RC4
#define MOSI_WPU                  WPUCbits.WPUC4
#define MOSI_OD                   ODCONCbits.ODCC4
#define MOSI_ANS                  ANSELCbits.ANSELC4
#define MOSI_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define MOSI_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define MOSI_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define MOSI_GetValue()           PORTCbits.RC4
#define MOSI_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define MOSI_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define MOSI_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define MOSI_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define MOSI_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define MOSI_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define MOSI_SetAnalogMode()      do { ANSELCbits.ANSELC4 = 1; } while(0)
#define MOSI_SetDigitalMode()     do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set RC5 aliases
#define MISO_TRIS                 TRISCbits.TRISC5
#define MISO_LAT                  LATCbits.LATC5
#define MISO_PORT                 PORTCbits.RC5
#define MISO_WPU                  WPUCbits.WPUC5
#define MISO_OD                   ODCONCbits.ODCC5
#define MISO_ANS                  ANSELCbits.ANSELC5
#define MISO_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define MISO_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define MISO_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define MISO_GetValue()           PORTCbits.RC5
#define MISO_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define MISO_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define MISO_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define MISO_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define MISO_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define MISO_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define MISO_SetAnalogMode()      do { ANSELCbits.ANSELC5 = 1; } while(0)
#define MISO_SetDigitalMode()     do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set RD1 aliases
#define IO_RD1_TRIS                 TRISDbits.TRISD1
#define IO_RD1_LAT                  LATDbits.LATD1
#define IO_RD1_PORT                 PORTDbits.RD1
#define IO_RD1_WPU                  WPUDbits.WPUD1
#define IO_RD1_OD                   ODCONDbits.ODCD1
#define IO_RD1_ANS                  ANSELDbits.ANSELD1
#define IO_RD1_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define IO_RD1_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define IO_RD1_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define IO_RD1_GetValue()           PORTDbits.RD1
#define IO_RD1_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define IO_RD1_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define IO_RD1_SetPullup()          do { WPUDbits.WPUD1 = 1; } while(0)
#define IO_RD1_ResetPullup()        do { WPUDbits.WPUD1 = 0; } while(0)
#define IO_RD1_SetPushPull()        do { ODCONDbits.ODCD1 = 0; } while(0)
#define IO_RD1_SetOpenDrain()       do { ODCONDbits.ODCD1 = 1; } while(0)
#define IO_RD1_SetAnalogMode()      do { ANSELDbits.ANSELD1 = 1; } while(0)
#define IO_RD1_SetDigitalMode()     do { ANSELDbits.ANSELD1 = 0; } while(0)

// get/set RF2 aliases
#define IO_RF2_TRIS                 TRISFbits.TRISF2
#define IO_RF2_LAT                  LATFbits.LATF2
#define IO_RF2_PORT                 PORTFbits.RF2
#define IO_RF2_WPU                  WPUFbits.WPUF2
#define IO_RF2_OD                   ODCONFbits.ODCF2
#define IO_RF2_ANS                  ANSELFbits.ANSELF2
#define IO_RF2_SetHigh()            do { LATFbits.LATF2 = 1; } while(0)
#define IO_RF2_SetLow()             do { LATFbits.LATF2 = 0; } while(0)
#define IO_RF2_Toggle()             do { LATFbits.LATF2 = ~LATFbits.LATF2; } while(0)
#define IO_RF2_GetValue()           PORTFbits.RF2
#define IO_RF2_SetDigitalInput()    do { TRISFbits.TRISF2 = 1; } while(0)
#define IO_RF2_SetDigitalOutput()   do { TRISFbits.TRISF2 = 0; } while(0)
#define IO_RF2_SetPullup()          do { WPUFbits.WPUF2 = 1; } while(0)
#define IO_RF2_ResetPullup()        do { WPUFbits.WPUF2 = 0; } while(0)
#define IO_RF2_SetPushPull()        do { ODCONFbits.ODCF2 = 0; } while(0)
#define IO_RF2_SetOpenDrain()       do { ODCONFbits.ODCF2 = 1; } while(0)
#define IO_RF2_SetAnalogMode()      do { ANSELFbits.ANSELF2 = 1; } while(0)
#define IO_RF2_SetDigitalMode()     do { ANSELFbits.ANSELF2 = 0; } while(0)

// get/set RF3 aliases
#define PWR_TRIS                 TRISFbits.TRISF3
#define PWR_LAT                  LATFbits.LATF3
#define PWR_PORT                 PORTFbits.RF3
#define PWR_WPU                  WPUFbits.WPUF3
#define PWR_OD                   ODCONFbits.ODCF3
#define PWR_ANS                  ANSELFbits.ANSELF3
#define PWR_SetHigh()            do { LATFbits.LATF3 = 1; } while(0)
#define PWR_SetLow()             do { LATFbits.LATF3 = 0; } while(0)
#define PWR_Toggle()             do { LATFbits.LATF3 = ~LATFbits.LATF3; } while(0)
#define PWR_GetValue()           PORTFbits.RF3
#define PWR_SetDigitalInput()    do { TRISFbits.TRISF3 = 1; } while(0)
#define PWR_SetDigitalOutput()   do { TRISFbits.TRISF3 = 0; } while(0)
#define PWR_SetPullup()          do { WPUFbits.WPUF3 = 1; } while(0)
#define PWR_ResetPullup()        do { WPUFbits.WPUF3 = 0; } while(0)
#define PWR_SetPushPull()        do { ODCONFbits.ODCF3 = 0; } while(0)
#define PWR_SetOpenDrain()       do { ODCONFbits.ODCF3 = 1; } while(0)
#define PWR_SetAnalogMode()      do { ANSELFbits.ANSELF3 = 1; } while(0)
#define PWR_SetDigitalMode()     do { ANSELFbits.ANSELF3 = 0; } while(0)

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
 * @brief Interrupt on Change Handler for the IRQ pin functionality
 * @param none
 * @return none
 */
void IRQ_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IRQ pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for IRQ at application runtime
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void IRQ_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for IRQ pin.
 *        This is a dynamic interrupt handler to be used together with the IRQ_SetInterruptHandler() method.
 *        This handler is called every time the IRQ ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*IRQ_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IRQ pin. 
 *        This is a predefined interrupt handler to be used together with the IRQ_SetInterruptHandler() method.
 *        This handler is called every time the IRQ ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void IRQ_DefaultInterruptHandler(void);


#endif // PINS_H
/**
 End of File
*/