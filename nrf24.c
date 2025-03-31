/* 
 * File:   nrf24.c
 * Author: Marie Berx
 * 
 * Inspired from the functions in the .h file of Noyel
 * debugged using chatGPT
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "nrf24.h"
#include "mcc_generated_files/spi/spi1.h"

void nrf24_WriteRegister(unsigned char address, unsigned char value){
        uint8_t fulladd = (W_REGISTER | (address & 0x1F));

        uint8_t buffer[2] = {fulladd, value};
        CSN = 0;
        SPI1_BufferExchange(buffer, 2);
        CSN = 1;
//        __delay_us(10000);  hopefully doesnt have to be there
}

unsigned char nrf24_ReadRegister(unsigned char address){
    uint8_t fulladd = (R_REGISTER | (address & 0x1F));
    uint8_t buffer[2] = {fulladd, 0xFF};
    CSN = 0;
    SPI1_BufferExchange(buffer, 2);
    CSN = 1;
    __delay_us(15);

    return buffer[1]; 
}

void nrf24_WriteBuffer(unsigned char address, unsigned char *buffer, unsigned char size){
    
    //only writes payloads now
    uint8_t command = (address);
    
    CSN = 0;
    SPI1_ByteWrite(command);
    SPI1_BufferWrite(buffer, size);
    CSN = 1;
}

void nrf24_WritePayload(unsigned char *buffer, unsigned char size){
    //only writes payloads now
    
    CSN = 0;
    SPI1_ByteWrite(0xA0);
    SPI1_BufferWrite(buffer, size);
    CSN = 1;
}

void nrf24_ReadBuffer(unsigned char address, unsigned char *buffer, unsigned char size){
    CSN = 0; // Chip Select Low
    SPI1_BufferExchange(&address, 1);
    SPI1_BufferExchange(buffer, size);
    CSN = 1; // Chip Select High
    __delay_us(15); //delay

}

NRF24_INIT_STATUS nrf24_Initialize() {
    CE = 0; // Pull CE low during configuration
    uint8_t stattestres = nrf24_ReadRegister(CONFIG);
    uint8_t cht = nrf24_ReadRegister(RF_CH);

    // Default CONFIG: Power up, enable CRC
    nrf24_WriteRegister(CONFIG, 0x02); // PWR_UP=1, EN_CRC=0, PRIM_RX=0 (default TX mode)
    __delay_us(1500); // Stabilization delay

    // Set common settings
    nrf24_WriteRegister(EN_RXADDR, 0x01);        // Enable Pipe 0
    nrf24_WriteRegister(SETUP_RETR, 0x00);       // Disable retransmit
    nrf24_WriteRegister(RF_CH, 0x77);            // Set channel to 2519 MHz
    nrf24_WriteRegister(STATUS, 0x70);           // Clear interrupt flags
    nrf24_WriteRegister(0xE1, 0);                // FLUSH_TX
//    nrf24_WriteRegister(RX_PW_P0, PAYLOAD_SIZE); // Set payload size                    SHOULD BE TX????????
//    nrf24_WriteBuffer(RX_ADDR_P0, RXPIPE0, 5);   // Set RX address
    nrf24_WriteBuffer(TX_ADDR, TXPIPE0, 5);      // Set TX address maybe wrong?         doesnt match the ds
    nrf24_WriteRegister(EN_AA, 0x00);

    // Validate basic initialization
    uint8_t stat = nrf24_ReadRegister(CONFIG);
    uint8_t fifostat_not = nrf24_ReadRegister(FIFO_STATUS);
    CSN = 0;                            // Pull CSN low
    SPI1_ByteWrite(FLUSH_TX);           // Send the flush command (0xE1)
    CSN = 1;                            // Release CSN
    __delay_us(10); 

    if (stat & (1 << 1)) { // Check if PWR_UP bit is set
        return NRF24_INIT_OK;
    } else {
        return NRF24_INIT_FAILED;
    }
}



void nrf24_SetMode(NRF24_OPERATION_MODE mode){
    if (mode == TX_MODE) {
        nrf24_WriteRegister(CONFIG, 0x0A); // Clear PRIM_RX for Tx Mode
    } else {
        nrf24_WriteRegister(CONFIG, 0x0B); // Set PRIM_RX for Rx Mode
    }
}

void nrf24_SendData(unsigned char *buffer){
    nrf24_SetMode(TX_MODE);
    nrf24_WriteBuffer(W_TX_PAYLOAD, buffer, PAYLOAD_SIZE); // Write TX Payload Command
    CE = 1;
    __delay_us(10);
    CE = 0;
}

unsigned char nrf24_DataAvailable(){
    unsigned char status = (nrf24_ReadRegister(STATUS) & 0x40);
    if(status == 0x40){
        return 0;   // no data available
    }
    return 1;   // data available
}

void nrf24_ReadData(unsigned char *buffer){
    nrf24_ReadBuffer(R_RX_PAYLOAD, buffer, PAYLOAD_SIZE);
    nrf24_WriteRegister(STATUS, 0x70); // Clear STATUS.
    
    // flush rx and tx
    CSN = 0;
    SPI_WRITE_BYTE(FLUSH_TX);
    __delay_ms(10);
    CSN = 1;
    
    CSN = 0;
    SPI_WRITE_BYTE(FLUSH_RX);
    __delay_ms(10);    
    CSN = 1;
}




