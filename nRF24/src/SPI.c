#include "SPI.h"

void spiInit()
{
    SPI_DDR |= (1 << MOSI) | (1 << SCK);
}

uint8_t spiByte(uint8_t _byte)
{
    for(uint8_t counter = 8; counter; counter--)
    {
        if (_byte & MSBit)
            MOSI_HIGH;
        else
            MOSI_LOW;
        _byte <<= 1;
        SCK_HIGH; 
        if (SPI_PIN & (1 << MISO))
            _byte |= LSBit;   
        SCK_LOW; 
    }
    return _byte;    
}