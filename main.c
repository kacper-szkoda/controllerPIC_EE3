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
    
        extern volatile uint8_t irq_ready;
        extern volatile uint8_t ready;
        extern volatile uint8_t done;
        extern volatile uint8_t last_sample;
        extern volatile uint8_t ctrl_ind;
        extern uint8_t pins_to_sample[3];
        extern uint8_t control_packet[32];
        extern volatile uint16_t counter;
        extern uint8_t micData [AUDIO_SIZE+32];
        extern volatile uint16_t packets_to_send;
        extern volatile uint8_t ind;
        extern volatile enum state_t current_state;

        
        irq_ready = 0;
        ready = 0;
        done = 0;
        last_sample = 0;
        ctrl_ind = 0;
        counter = 0;
        current_state = STATE_SAMPLING;
        CE = 0;
        
    CSN = 1;

    SPI1_Initialize();   
    SPI1_Open(2);
    
    NRF24_INIT_STATUS init = nrf24_Initialize();
        
    nrf24_WriteRegister(0x07, (1 << 5));
    
    ADC_Enable();
    TMR0_Start();

    while(1)
    {
        if (counter == AUDIO_SIZE){
            ready = 1;
        }
        if (last_sample == 1 && packets_to_send == 0 && CE == 0) {
            if (current_state == STATE_CONTROL && ctrl_ind == 3) {
                TMR0_Stop();
                micData[AUDIO_SIZE]   = 'j'; //never actually being sent, b is set correctly, j is not????
                micData[AUDIO_SIZE+1] = 'b';  
                ready = 1;
                last_sample = 0;
                current_state = STATE_RESET;
                packets_to_send++;  
                ADPCH = (uint8_t)(1 << _ADPCH_PCH_POSITION);  //i think
            }
            else if (current_state == STATE_CONTROL && ctrl_ind < 3) {
                last_sample = 0;
                ADPCH = (uint8_t)(pins_to_sample[ctrl_ind] << _ADPCH_PCH_POSITION);
                ADC_ConversionStart(); //act why do i only measure two things xd
            }
        }
        if ((ready == 1 && CE == 0 && irq_ready == 0)){
            if (packets_to_send > 0){
//                nrf24_WriteRegister(STATUS, (1 << 5));  
//                if (ind != 63){
//                        for (int i = 1; i < 30; i++) {
//                    micData[ind*32+i] = (ind * 2 + i);
//                    }
//                        micData[ind*32] = ind;
//                }
                if (ind == 63) {
                    for (int i = 5; i < 30; i++) {
                        micData[ind*32+i] = (ind * 2 + i);
                        } //to avoid duplicate detection
                }
                uint8_t fifo_status = nrf24_ReadRegister(FIFO_STATUS);
                if (!(fifo_status & (1 << 5))){
                    nrf24_WritePayload(&micData[ind*32], 32);
                    packets_to_send -=1;
                    ind ++;
                    ready = 0;
                    CE = 1;     
                }
            }
        }
        if (irq_ready == 1){
            CE = 0;
            irq_ready = 0;
            nrf24_WriteRegister(STATUS, (1 << 5));        

            if (done == 1){
                ready = 0;
                done = 0;
                ind = 0;
                counter = 0;
                packets_to_send = 0;
                transmitted = 0;
                irq_ready = 0;
                last_sample = 0;
                ctrl_ind = 0;
                counter = 0;
        
                current_state = STATE_SAMPLING;
                TMR0_Start();
            }
            else {
                ready = 1;
            }
        }
        }
        }
        /// maybe act dont stop the timer??? for smoother audio,   
