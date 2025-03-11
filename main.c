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
© [2024] Microchip Technology Inc. and its subsidiaries.

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

// LED debugging
#define LED_RED_LAT LATFbits.LATF2 // LED connected to RF2
#define LED_RED_TRIS TRISFbits.TRISF2

#define LED_GREEN_LAT LATDbits.LATD1 // LED connected to RD1
#define LED_GREEN_TRIS TRISDbits.TRISD1

void LED_Initialize(void)
{
    // Set the LED pin as an output
    //LED_RED_TRIS = 0;     // Configure RFZ as output
    LED_RED_LAT = 0;      // Initialize LED to off
    
    //LED_GREEN_TRIS = 0;
    LED_GREEN_LAT = 0;
}

void LEDR_Toggle(void)
{
    // Toggle the LED state
    LED_RED_LAT = !LED_RED_LAT;
}
void LEDG_Toggle(void)
{
    // Toggle the LED state
    LED_GREEN_LAT = !LED_GREEN_LAT;
}

// main application
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
    
    LED_Initialize();
    
    ANSELBbits.ANSELB0 = 0; // Set RB0 as digital
    TRISBbits.TRISB0 = 1; //set port b as digital input for irq
    WPUBbits.WPUB0 = 1;    // Enable weak pull-up on RB0

    // set VCC high
    LATFbits.LATF3 = 1;
    __delay_ms(15);
    
    // set CE and CSN as outputs
    // Configure CS pin (RC3)
    TRISCbits.TRISC3 = 0;       // Set RC3 as output
    ANSELCbits.ANSELC3 = 0;     // Set RC3 as digital
    LATCbits.LATC3 = 1;         // Set CS high (inactive)

    // Configure CE pin (RC2)
    TRISCbits.TRISC5 = 0;       // Set RC2 as output
    ANSELCbits.ANSELC5 = 0;     // Set RC2 as digital
    LATCbits.LATC5 = 0;         // Set CE high (inactive)
    
    LEDG_Toggle();
    __delay_ms(1000);
    LEDR_Toggle();
    __delay_ms(1000);
    LEDG_Toggle();
    LEDR_Toggle();
    
    CSN = 1;

    SPI1_Initialize();   
    SPI1_Open(2);
    
//    if (PORTBbits.RB0 == 0){
//        LEDR_Toggle();
//        __delay_ms(1000);       
//        LEDR_Toggle();
//    }
    
    NRF24_INIT_STATUS init = nrf24_Initialize();
    
    if(init == NRF24_INIT_OK){
        LEDG_Toggle();
        __delay_ms(1000);    
    }
    
    uint8_t dataToSend2[32] = {9, 100, 110, 120, 130, 140, 150, 16};
    
    nrf24_WriteRegister(0x07, (1 << 5));
    static uint8_t counter;

    while(1)
    {
        nrf24_WriteRegister(0x07, (1 << 4)); 
        uint8_t stat = nrf24_ReadRegister(0x07);
        uint8_t fifo_stat = nrf24_ReadRegister(FIFO_STATUS);  // FIFO_STATUS is 0x17
        uint8_t rf = nrf24_ReadRegister(0x06);
        uint8_t txadrr = nrf24_ReadRegister(0x10);
        uint8_t carr = nrf24_ReadRegister(0x05);
        uint8_t conf = nrf24_ReadRegister(0x00);

//    bool tx_full = (fifo_stat & (1 << 0)) != 0;            // bit0 = TX_FULL
//
//    // 2) If TX_FULL is set, flush TX
//    if(tx_full)
//    {
//        // Issue the FLUSH_TX command (0xE1)
//        CSN = 0;
//        SPI1_ByteWrite(FLUSH_TX);
//        CSN = 1;
//        __delay_us(10);  // short delay
//
//        // (Optional) also clear any interrupts if needed, e.g. TX_DS (bit5), MAX_RT (bit4):
//        // If a payload got stuck, you might need to clear these bits so the radio
//        // can accept future transmissions:
//        nrf24_WriteRegister(STATUS, (1 << 5) | (1 << 4)); // clear TX_DS and MAX_RT
//    }
//        nrf24_WriteRegister(0xE1, 0); // FLUSH_TX command
//        nrf24_WriteRegister(0x07, 0x70); // Clear STATUS register

        
        
        nrf24_WritePayload(dataToSend2, 32);
        
        uint8_t status = nrf24_ReadRegister(STATUS);
        fifo_stat = nrf24_ReadRegister(FIFO_STATUS);

        __delay_us(100);
        fifo_stat = nrf24_ReadRegister(FIFO_STATUS);
        // Pulse CE pin to send the payload
        CE = 1;         // Set CE high
        __delay_us(300);           // Minimum 10 µs pulse width
        CE = 0;         // Set CE low
        

        
        status = nrf24_ReadRegister(STATUS);
        fifo_stat = nrf24_ReadRegister(FIFO_STATUS);
        if (status & (1 << 5)) {          // if TX_DS bit set
            // Clear it by writing a ?1? to that bit
            nrf24_WriteRegister(STATUS, (1 << 5));
        }
        status = nrf24_ReadRegister(STATUS);
        
        if (counter > 41){
            counter =0;
        }
        counter += 1;
        for (uint8_t i = 0; i < 32; i++){
            dataToSend2[i] = counter;
//            dataToSend2[i] = 39; //works now as well
        };
        

        // Delay to avoid continuous retransmissions
        __delay_ms(3000);
    }    
}