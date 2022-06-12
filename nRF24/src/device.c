#include "device.h"

void deviceInit()
{
    adcInit();
    displayInit();
    transceiverInit();
    transceiverSetPRX();
}  

void deviceControl()
{       
    if(payloadReceivedFlag == PAYLOAD_RECEIVED_FLAG_IS_SET)
    {
	    payloadReceivedFlag = PAYLOAD_RECEIVED_FLAG_IS_CLEAR;    
        transceiverReceive();
        temperatureSign = payload[0];
        temperatureTens = payload[1];
        temperatureUnits = payload[2];
        temperatureFraction = payload[3];
        drawTemperature();
    } 

    unsigned char adcValue = adcGetValue();
    if(adcCurrentValue != adcValue)
    {
        adcCurrentValue = adcValue;
        payload[0] = adcCurrentValue; 
        transceiverSetPTX();
        transceiverTrasmit();        
        transceiverSetPRX();
    }    
}