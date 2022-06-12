#include "DS18B20.h"

unsigned char temperatureSign, temperatureTens, temperatureUnits, temperatureFraction, DS18B20State = FREE;
float temperature;

void DS18B20Init(void) 
{
  owiInit();
}

void DS18B20StartConversion(void) 
{
  unsigned char ds18b20_data[2]; 
  DS18B20State = CONVERSION;

  owiReset();
  owiSendByte(SKIP_ROM);
  owiSendByte(CONVERT_T);
  nrf_delay_ms(CONVERT_DELAY);

  owiReset();
  owiSendByte(SKIP_ROM);
  owiSendByte(READ_SCRATCH_PAD);
  for(int i = 0; i < 2; i++)
    {
      ds18b20_data[i] = owiReceiveByte();
    }
  owiReset();
  
  temperature = (ds18b20_data[1] << 8 | ds18b20_data[0])/16.0;

  if(temperature >= 0)
  {
    temperatureSign = PLUS;
  }
  else if(temperature < 0)
  {
    temperatureSign = MINUS;
  }
            
  temperatureTens = (uint8_t)(temperature / 10);
  temperatureUnits = (uint8_t)(temperature - temperatureTens * 10);
  temperatureFraction = (uint8_t)(temperature * 10 - temperatureTens * 100 - temperatureUnits * 10);  
  DS18B20State = DONE;
}
