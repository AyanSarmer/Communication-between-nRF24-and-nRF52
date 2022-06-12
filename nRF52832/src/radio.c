#include "radio.h"

uint8_t radioState = PRX;
uint8_t S1 = 0;
uint8_t packet[PACKET_LENGTH];

void RADIO_IRQHandler()
{
  if(NRF_RADIO->EVENTS_END)
  {
    NRF_RADIO->EVENTS_END = 0;
    NRF_RADIO->PACKETPTR = (uint32_t)packet;
    NRF_RADIO->TASKS_START = 1;        
    pwmSeq = packet[2] | POLARITY_MASK;
    NRF_PWM0->TASKS_SEQSTART[0] = 1;
  }
}

void radioInit(uint8_t channel)
{
  NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
  NRF_CLOCK->TASKS_HFCLKSTART = 1;
  while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0);

  NRF_RADIO->TXPOWER      = (RADIO_TXPOWER_TXPOWER_0dBm << RADIO_TXPOWER_TXPOWER_Pos);  
  NRF_RADIO->MODE 	      = (RADIO_MODE_MODE_Nrf_2Mbit << RADIO_MODE_MODE_Pos);   
  NRF_RADIO->PCNF0        = (0 << RADIO_PCNF0_S0LEN_Pos) |
                            (6 << RADIO_PCNF0_LFLEN_Pos) |
                            (3 << RADIO_PCNF0_S1LEN_Pos) ;
  NRF_RADIO->PCNF1        = (RADIO_PCNF1_WHITEEN_Disabled    << RADIO_PCNF1_WHITEEN_Pos) |
                            (RADIO_PCNF1_ENDIAN_Big          << RADIO_PCNF1_ENDIAN_Pos)  |
                            (4                               << RADIO_PCNF1_BALEN_Pos)   |
                            (0                               << RADIO_PCNF1_STATLEN_Pos) |
                            (PACKET_LENGTH                   << RADIO_PCNF1_MAXLEN_Pos);
  NRF_RADIO->BASE0        = 0xe7e7e7e7; 
  NRF_RADIO->PREFIX0      = 0xe7; 
  NRF_RADIO->TXADDRESS    = 0; 
  NRF_RADIO->RXADDRESSES  = RADIO_RXADDRESSES_ADDR0_Enabled << RADIO_RXADDRESSES_ADDR0_Pos; 
  NRF_RADIO->CRCCNF       = (RADIO_CRCCNF_LEN_Two << RADIO_CRCCNF_LEN_Pos);
  NRF_RADIO->CRCINIT      = 0xFFFF; 
  NRF_RADIO->CRCPOLY      = 0x11021;  
  NRF_RADIO->TIFS         = 150;
  NRF_RADIO->FREQUENCY    = channel;
  NRF_RADIO->PACKETPTR    = (uint32_t)packet;  
  NVIC_EnableIRQ(RADIO_IRQn);  
}

void radioSetPTX()
{
  NRF_RADIO->TASKS_DISABLE = 1;
  while(!NRF_RADIO->EVENTS_DISABLED);
  NRF_RADIO->EVENTS_DISABLED = 0;  

  NRF_RADIO->INTENCLR |= (1 << RADIO_INTENCLR_END_Pos);

  NRF_RADIO->TASKS_TXEN = 1;
  while(!NRF_RADIO->EVENTS_READY); 
  NRF_RADIO->EVENTS_READY = 0; 
}

void radioSetPRX()
{
  NRF_RADIO->TASKS_DISABLE = 1;
  while(!NRF_RADIO->EVENTS_DISABLED);
  NRF_RADIO->EVENTS_DISABLED = 0;  

  NRF_RADIO->INTENSET |= (1 << RADIO_INTENSET_END_Pos);
  
  NRF_RADIO->TASKS_RXEN = 1;
  while(!NRF_RADIO->EVENTS_READY); 
  NRF_RADIO->EVENTS_READY = 0;   
  NRF_RADIO->TASKS_START = 1;   
}

void radioTransmit()
{   
  packet[0] = PAYLOAD_LENGTH;
  S1++;
  if(S1 > 1) S1 = 0;
  packet[1] = S1;     
  NRF_RADIO->TASKS_START = 1;  
  while(!NRF_RADIO->EVENTS_END); 
  NRF_RADIO->EVENTS_END = 0;
}