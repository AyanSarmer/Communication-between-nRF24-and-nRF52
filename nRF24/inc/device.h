#ifndef DEVICE_H_
#define DEVICE_H_

#include <avr/io.h>
#include "nRF24.h"
#include "adc.h"
#include "display.h"

void deviceInit();
void deviceControl();

#endif /* DEVICE_H_ */