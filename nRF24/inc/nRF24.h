#ifndef nRF24_H_
#define nRF24_H_

#include <stdbool.h>
#include <avr/interrupt.h>
#include "SPI.h"

#define nRF_CSN_DDR                         DDRD
#define nRF_CSN_PORT                        PORTD
#define nRF_CSN                             PD4
#define nRF_CSN_HIGH		                nRF_CSN_PORT |= (1 << nRF_CSN)
#define nRF_CSN_LOW		                    nRF_CSN_PORT &= ~(1 << nRF_CSN)

#define nRF_CE_DDR                          DDRD
#define nRF_CE_PORT                         PORTD
#define nRF_CE                              PD3
#define nRF_CE_HIGH		                    nRF_CE_PORT |= (1 << nRF_CE)
#define nRF_CE_LOW		                    nRF_CE_PORT &= ~(1 << nRF_CE)

/* commands */
#define R_REGISTER                          0x00
#define W_REGISTER                          0x20
#define R_RX_PAYLOAD                        0x61
#define W_TX_PAYLOAD                        0xA0
#define W_ACK_PAYLOAD                       0xA8
#define FLUSH_TX                            0xE1
#define FLUSH_RX                            0xE2
#define NOP                                 0xFF
/* registers */
#define CONFIG                              0x00
    #define MASK_RX_DR			            6
    #define MASK_TX_DS			            5
    #define MASK_MAX_RT			            4
    #define EN_CRC				            3
    #define CRCO				            2
    #define PWR_UP				            1
    #define PRIM_RX				            0
#define EN_AA                               0x01
    #define ENAA_P0                         0
#define SETUP_AW                            0x03
#define SETUP_RETR							0x04
    #define ARD								4
    #define ARC								0
#define RF_CH				                0x05
#define RF_SETUP                            0x06
#define STATUS                              0x07
    #define RX_DR				            6
    #define TX_DS				            5
    #define MAX_RT				            4
    #define RX_P_NO				            1
    #define TX_FULL				            0
#define OBSERVE_TX							0x08
#define RX_ADDR_P0                          0x0A
#define RX_ADDR_P1                          0x0B
#define RX_ADDR_P2                          0x0C
#define RX_ADDR_P3                          0x0D
#define RX_ADDR_P4                          0x0E
#define RX_ADDR_P5                          0x0F
#define TX_ADDR                             0x10
#define RX_PW_P0                            0x11
#define DYNPD                               0x1C
    #define DPL_P5                          5
    #define DPL_P4                          4
    #define DPL_P3                          3
    #define DPL_P2                          2
    #define DPL_P1                          1
    #define DPL_P0                          0
#define FEATURE                             0X1D
    #define EN_DPL                          2
    #define EN_ACK_PAY                      1
    #define EN_DYN_ACK                      0

#define PAYLOAD_SIZE                        5
#define PTX                                 1
#define PRX                                 2

#define PTX_MASK                            (1 << MASK_RX_DR) | (1 << MASK_TX_DS) | (1 << MASK_MAX_RT) | (1 << EN_CRC)
#define PRX_MASK                            (0 << MASK_RX_DR) | (1 << MASK_TX_DS) | (1 << MASK_MAX_RT) | (1 << EN_CRC) | (1 << CRCO) | (1 << PRIM_RX)
#define STATUS_CLEAR_MASK                   (1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT) | (1 << TX_FULL)
#define SETUP_RETR_MASK						(1 << ARD) | (3 << ARC)
#define DYNPD_MASK                          (1 << DPL_P0) 
#define FEATURE_MASK                        (1 << EN_DPL)

#define PAYLOAD_RECEIVED_FLAG_IS_SET        1
#define PAYLOAD_RECEIVED_FLAG_IS_CLEAR      0

void transceiverCommand(uint8_t command);
void transceiverWriteRegister(uint8_t reg, uint8_t* buf, uint8_t length);
uint8_t transceiverReadRegister(uint8_t reg, uint8_t* buf, uint8_t length);

void transceiverInit();
void transceiverSetPTX();
void transceiverSetPRX();
void transceiverPowerUp();
void transceiverPowerDown();
void transceiverTrasmit();
void transceiverReceive();
void transceiverWriteAck(unsigned char *buf, unsigned char len);
void transceiverFlushStatus();
void transceiverFlushFIFO();

extern uint8_t payload[PAYLOAD_SIZE];
extern volatile bool payloadReceivedFlag;
extern unsigned char ack;

#endif /* nRF24_H_ */
