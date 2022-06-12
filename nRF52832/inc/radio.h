#ifndef RADIO_H_
#define RADIO_H_

#include "nrf.h"
#include "nrf_delay.h"
#include "PWM.h"
#include <stdbool.h>

#define PACKET_LENGTH               7
#define PAYLOAD_LENGTH              5

#define PRX                         0
#define PTX                         1

void radioInit(uint8_t channel);
void radioSetPTX();
void radioSetPRX();
void radioTransmit();
bool radioReceive();

extern uint8_t packet[PACKET_LENGTH], S1;

#endif /* RADIO_H_ */