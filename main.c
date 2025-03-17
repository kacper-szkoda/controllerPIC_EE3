 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
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
//#pragma config WDTE = OFF

#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/system/pins.h"
#include "nrf24.h"
#include "mcc_generated_files/timer/tmr0.h"

extern uint8_t ready;

/*
    Main application
*/

int main(void)
{
    SYSTEM_Initialize();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 
    
    
    ANSELBbits.ANSELB2 = 0; // Set RB0 as digital
    TRISBbits.TRISB2 = 1; //set port b as digital input for irq
    WPUBbits.WPUB2 = 1;    // Enable weak pull-up on RB0

//     set VCC high
    LATFbits.LATF3 = 1;
    __delay_ms(15);
    
//     set CE and CSN as outputs
//     Configure CS pin (RC3)
    TRISAbits.TRISA4 = 0;       // Set RC3 as output
    ANSELAbits.ANSELA4 = 0;     // Set RC3 as digital
    LATAbits.LATA4 = 0;         // Set CS high (inactive)

    // Configure CE pin (RC2)
    TRISAbits.TRISA6 = 0;       // Set RC2 as output
    ANSELAbits.ANSELA6 = 0;     // Set RC2 as digital
    LATAbits.LATA6 = 0;         // Set CE high (inactive)
    
    CSN = 1;

    SPI1_Initialize();   
    SPI1_Open(2);
    
    NRF24_INIT_STATUS init = nrf24_Initialize();
    
    uint8_t dataToSend2[32] = {9, 100, 110, 120, 130, 140, 150, 16};
    
    nrf24_WriteRegister(0x07, (1 << 5));
    static uint8_t counter;

    while(1)
    {
        TMR0_Stop();
//        nrf24_WriteRegister(0x07, (1 << 4)); 

        nrf24_WritePayload(dataToSend2, 32);
        
        CE = 1;         // Set CE high, should be handled by the interrupt of irq
        
        if (counter > 41){
            counter =0;
        }
        counter += 1;
        for (uint8_t i = 0; i < 32; i++){
            dataToSend2[i] = counter;
        };
        
        // Delay to avoid continuous retransmissions
        __delay_ms(3000);
    }    
}