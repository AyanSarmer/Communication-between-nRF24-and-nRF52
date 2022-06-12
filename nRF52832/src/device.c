#include "device.h"

Device device;

void deviceInit() 
{
    DS18B20Init();  
    radioInit(2);  
    radioSetPRX();
    pwmInit();    
}

void deviceControl()
{    
    if(DS18B20State == FREE) 
    {
        DS18B20StartConversion();
    }
    else if(DS18B20State == DONE)
    {
        DS18B20State = FREE;
        packet[2] = temperatureSign;
        packet[3] = temperatureTens;
        packet[4] = temperatureUnits;
        packet[5] = temperatureFraction;
        radioSetPTX();
        radioTransmit();
        radioSetPRX();
    }
}