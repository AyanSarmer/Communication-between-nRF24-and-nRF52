#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

void adcInit();
unsigned char adcGetValue();

extern unsigned char adcCurrentValue;

#endif /* ADC_H_ */