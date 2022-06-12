#ifndef _OWI_H_
#define _OWI_H_

#include "nrf.h"
#include "nrf_delay.h"

#define DELAY_A                   6
#define DELAY_B                   64
#define DELAY_C                   60
#define DELAY_D                   10
#define DELAY_E                   9
#define DELAY_F                   55
#define DELAY_G                   0
#define DELAY_H                   480
#define DELAY_I                   70
#define DELAY_J                   410

#define MSBit                     0x80
#define LSBit                     0x01

#define OWI_BUS                   24
#define DIR                       0 
#define PULL                      2 

#define OWI_RELEASE_BUS           NRF_GPIO->PIN_CNF[OWI_BUS] = 0 
#define OWI_PULL_BUS_LOW          NRF_GPIO->PIN_CNF[OWI_BUS] = 1 << DIR

void owiInit(void);
void owiReset(void);
void owiWriteBit0(void);
void owiWriteBit1(void);
unsigned char owiReadBit(void);
void owiSendByte(unsigned char data);
unsigned char owiReceiveByte(void);

#endif /* _OWI_H_ */
