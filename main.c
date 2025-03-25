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
#include "mcc_generated_files/adc/adc.h"

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
    
//    uint8_t dataToSend2[32] = {9, 100, 110, 120, 130, 140, 150, 16};
    
    nrf24_WriteRegister(0x07, (1 << 5));
    
    ADC_Enable();
    TMR0_Start();

    static uint8_t index = 0;

    while(1)
    {
        extern uint8_t irq_ready;
        extern uint8_t ready;
        extern uint8_t done;
        extern uint8_t transmitted;
        extern uint8_t last_sample;
        extern uint8_t ctrl_ind;
        extern uint8_t pins_to_sample[3];
        extern uint8_t control_packet[32];
        extern uint16_t counter;
        
        if (last_sample == 1){
            if (ctrl_ind == 3){
                nrf24_WritePayload(&control_packet[0], 32);
                ready = 0;
                last_sample = 0;
                ctrl_ind = 0;
                ADPCH = (1 << _ADPCH_PCH_POSITION);
            }
            else {
                last_sample = 0;
                ADPCH = (uint8_t)( pins_to_sample[ctrl_ind] << _ADPCH_PCH_POSITION);
                ADC_ConversionStart();
            }
        }
        else {if (ready == 1){

            extern uint8_t micData [AUDIO_SIZE]; //Something wrong with accesing array, array has values but 0s received
            
            //passing a pointer so just increment it like 32*i and pass that to write payload
            //TODO write loop to wrire all 2k bytes and also write logic to only do the restart in the pin manager, do some counter with modulo
            
            
            nrf24_WritePayload(&micData[index*32], 32);
            index ++;
            CE = 1;         // Set CE high, should be handled by the interrupt of irq
            ready = 0;
        }
        
//        else {if payload_ready == 1}
        else {if (irq_ready == 1){
            CE = 0;
            nrf24_WriteRegister(STATUS, (1 << 5));
            irq_ready = 0;
            
            if (done == 1){
                ready = 0;
                done = 0;
                TMR0_Start();
                index = 0;
            }
            else {
                ready = 1;
            }
        }
        }
        }
        /// maybe act dont stop the timer??? for smoother audio, 
    }    
}