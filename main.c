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
    
        extern uint8_t irq_ready;
        extern uint8_t ready;
        extern uint8_t done;
        extern uint8_t ready;
        extern uint8_t last_sample;
        extern uint8_t ctrl_ind;
        extern uint8_t pins_to_sample[3];
        extern uint8_t control_packet[32];
        extern uint16_t counter;
        extern uint8_t micData [AUDIO_SIZE+32];
        extern uint8_t index;
        extern uint8_t packets_in_flight;
        
        irq_ready = 0;
        ready = 0;
        done = 0;
        ready = 0;
        last_sample = 0;
        ctrl_ind = 0;
        counter = 0;
        index = 0;
        packets_in_flight = 0;
        
    CSN = 1;

    SPI1_Initialize();   
    SPI1_Open(2);
    
    NRF24_INIT_STATUS init = nrf24_Initialize();
        
    nrf24_WriteRegister(0x07, (1 << 5));
    
    ADC_Enable();
    TMR0_Start();
    
    while(1)
{
        
        
    if (last_sample == 1)
    {
        if (ctrl_ind == 3)
        {
            micData[0] = 'j';
            micData[1] = 'b';
            ready = 1;
            last_sample = 0;
            ctrl_ind = 0;
            counter = 0;
            ADPCH = (1 << _ADPCH_PCH_POSITION);
        }
        else
        {
            last_sample = 0;
            ADPCH = (uint8_t)(pins_to_sample[ctrl_ind] << _ADPCH_PCH_POSITION);
            ADC_ConversionStart();
        }
    }
    else
    {
        if (ready == 1)
        {
            packets_in_flight = 0;
            for (uint8_t i = 0; i < 3; i++)
            {
                if (index < 63)
                {
                    nrf24_WritePayload(&micData[index * 32], 32);
                    index+=1;
                    packets_in_flight+=1;
                }
                else
                {
                    // No more data to send
                    break;
                }
            }
            CE = 1;    // Begin transmitting whatever we just queued
            ready = 0; // Wait for TX_DS interrupts to signal completion
        }
        else
        {
            if (irq_ready == 1)
            {
                irq_ready = 0;
                nrf24_WriteRegister(STATUS, (1 << 5));
                uint8_t fifoStatus = nrf24_ReadRegister(FIFO_STATUS);
                if (fifoStatus & (1 << 4)) 
                {
                    CE = 0;
                    if (index >= 63){
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
    }
    // maybe don't stop the timer??? for smoother audio
}

}