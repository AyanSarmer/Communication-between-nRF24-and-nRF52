#ifndef _DS18B20_H_
#define _DS18B20_H_

#include "OneWire.h"

#define SKIP_ROM            0xCC
#define READ_SCRATCH_PAD    0xBE
#define CONVERT_T           0x44

#define CONVERT_DELAY       750 

#define MINUS               1
#define PLUS                0

#define FREE                0
#define CONVERSION          1
#define DONE                2

void DS18B20Init(void);
void DS18B20StartConversion(void);

extern unsigned char temperatureSign, temperatureTens, temperatureUnits, temperatureFraction, DS18B20State;
extern float temperature;

#endif /* _DS18B20_H_ */
