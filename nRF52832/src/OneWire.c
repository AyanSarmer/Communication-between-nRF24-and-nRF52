#include "OneWire.h"

void owiInit(void) 
{
  OWI_RELEASE_BUS;
  nrf_delay_us(DELAY_H);
}

void owiReset(void) 
{ 
  OWI_PULL_BUS_LOW;
  nrf_delay_us(DELAY_H);  

  OWI_RELEASE_BUS;
  nrf_delay_us(DELAY_I);  
  
  nrf_delay_us(DELAY_J);  
}

void owiWriteBit0(void) 
{
  OWI_PULL_BUS_LOW;
  nrf_delay_us(DELAY_C);
    
  OWI_RELEASE_BUS;
  nrf_delay_us(DELAY_D);  
}

void owiWriteBit1(void) 
{
  OWI_PULL_BUS_LOW;
  nrf_delay_us(DELAY_A);
    
  OWI_RELEASE_BUS;
  nrf_delay_us(DELAY_B);
}

unsigned char owiReadBit(void) 
{  
  uint32_t bitsRead = 0;

  OWI_PULL_BUS_LOW;
  nrf_delay_us(DELAY_A);  

  OWI_RELEASE_BUS;
  nrf_delay_us(DELAY_E);  

  if(NRF_GPIO->IN & (1 << OWI_BUS)) 
    bitsRead = 1;  
  nrf_delay_us(DELAY_F); 
  
  return bitsRead;
}

void owiSendByte(unsigned char data) 
{
  unsigned char temp, currentBit;
    
  for (currentBit = 0; currentBit < 8; currentBit++) 
  {
    temp = data & 0x01;
    if (temp) 
    {
      owiWriteBit1();
    } 
    else 
    {
      owiWriteBit0();
    }
    data >>= 1;
  }  
}

unsigned char owiReceiveByte(void) 
{
  unsigned char data = 0, currentBit = 0;  

  for (currentBit = 0; currentBit < 8; currentBit++) 
  {  
    data >>= 1;
    if (owiReadBit()) 
    {
      data |= MSBit;
    }
  }
  return data;
}
