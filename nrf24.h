/*
 * File:   nrf24.h
 * Author: Noyel Seth (noyelseth@gamil.com)
 */

#ifndef NRF24_H
#define	NRF24_H

#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/system/pins.h"
#include "mcc_generated_files/spi/spi1.h"

// pinning
#define CE LATAbits.LATA6
#define SCK LATCbits.LATC3
#define CSN LATAbits.LATA4
#define MISO LATCbits.LATC5
#define MOSI LATCbits.LATC4


#define SPI_WRITE_BYTE(dt)               SPI1_ByteWrite(dt)
#define SPI_READ_BYTE(dt)                SPI1_ByteRead(dt)
#define SPI_INIT()                  SPI1_Open(SPI1_DEFAULT)

/******************************************************************************/
#define PAYLOAD_SIZE      32 // Sets the bytes to send or read.
#define AUDIO_SIZE        2016 //to not overflow, last 16 will be empty tho

// This data type sets the address data pipe 0.
unsigned char RXPIPE0[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
unsigned char TXPIPE0[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};

uint8_t ready = 0;
uint8_t irq_ready = 0;
uint8_t done;
uint8_t micData [AUDIO_SIZE];
uint8_t transmitted = 0;

// nrf24 status 
typedef enum{
    NRF24_INIT_OK = 0,
    NRF24_INIT_FAILED = 1
}NRF24_INIT_STATUS;

// nrf24 operation modes
typedef enum {
    RX_MODE = 1,
    TX_MODE = 2
}NRF24_OPERATION_MODE;


// spi commands
#define R_REGISTER          0x00  
#define W_REGISTER          0x20  
#define R_RX_PAYLOAD        0x61  
#define W_TX_PAYLOAD        0xA0  
#define FLUSH_TX            0xE1  
#define FLUSH_RX            0xE2  
#define REUSE_TX_PL         0xE3
#define NRF24_NOP           0xFF

// register map
#define CONFIG              0x00  
#define EN_AA               0x01  
#define EN_RXADDR           0x02  
#define SETUP_AW            0x03  
#define SETUP_RETR          0x04  
#define RF_CH               0x05  
#define RF_SETUP            0x06  
#define STATUS              0x07  
#define OBSERVE_TX          0x08  
#define CD                  0x09  
#define RX_ADDR_P0          0x0A  
#define RX_ADDR_P1          0x0B  
#define RX_ADDR_P2          0x0C  
#define RX_ADDR_P3          0x0D  
#define RX_ADDR_P4          0x0E  
#define RX_ADDR_P5          0x0F  
#define TX_ADDR             0x10  
#define RX_PW_P0            0x11  
#define RX_PW_P1            0x12  
#define RX_PW_P2            0x13  
#define RX_PW_P3            0x14  
#define RX_PW_P4            0x15  
#define RX_PW_P5            0x16  
#define FIFO_STATUS         0x17

// #define DYNPD               0x1C
// #define FEATURE             0x1D


/******************************************************************************/
// NRF24L01 Functions.
/******************************************************************************/

void nrf24_WritePayload(unsigned char *, unsigned char);

// write value to memory address of the nrf
void nrf24_WriteRegister(unsigned char address, unsigned char value);

// read value from a memory address of the nrf
unsigned char nrf24_ReadRegister(unsigned char address);

// write a buffer to an address of the nrf
void nrf24_WriteBuffer(unsigned char address, unsigned char *buffer, unsigned char size);

// read and fill a buffer from data in an address of the nrf
void nrf24_ReadBuffer(unsigned char address, unsigned char *buffer, unsigned char size);

// initialize the nrf24: put it in Standby
NRF24_INIT_STATUS nrf24_Initialize();

// change modes
void nrf24_SetMode(NRF24_OPERATION_MODE mode);

// send payload to the nrf
void nrf24_SendData(unsigned char *buffer);


// check if data is present: 0 = no data, 1 = data available
unsigned char nrf24_DataAvailable(void);

// read payload from nrf
void nrf24_ReadData(unsigned char *buffer);

// print config
void nrf24_printf_rf_config(void);


#endif	/* NRF24_H */

