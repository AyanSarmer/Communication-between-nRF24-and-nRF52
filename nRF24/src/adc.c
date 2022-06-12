#include "adc.h"

unsigned char adcCurrentValue;

void adcInit()
{
    ADMUX = (1 << ADLAR);
    ADCSRA = (1 << ADEN);	
}

unsigned char adcGetValue()
{
    ADCSRA |= (1 << ADSC);
    while(ADCSRA & (1 << ADSC));
    return ADCH;
}