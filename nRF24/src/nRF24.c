#include "nRF24.h"

unsigned char payload[PAYLOAD_SIZE];
volatile bool payloadReceivedFlag;
unsigned char ack = 5;

ISR(INT0_vect)
{
	payloadReceivedFlag = PAYLOAD_RECEIVED_FLAG_IS_SET;
}

void transceiverCommand(unsigned char command)
{
	nRF_CSN_LOW;
	spiByte(command);
	nRF_CSN_HIGH;
}

void transceiverWriteRegister(unsigned char reg, unsigned char* buf, unsigned char length)
{
	reg |= W_REGISTER;
	nRF_CSN_LOW;
	spiByte(reg);
	while (length--)
	{
		spiByte(*buf++);
	}
	nRF_CSN_HIGH;
}

unsigned char transceiverReadRegister(unsigned char reg, unsigned char* buf, unsigned char length)
{
	nRF_CSN_LOW;
	unsigned char status = spiByte(reg);
	while(length--)
	{
		*buf++ = spiByte(NOP);
	}
	nRF_CSN_HIGH;

	return status;
}

void transceiverInit()
{
	spiInit();
	nRF_CSN_DDR |= (1 << nRF_CSN);
	nRF_CE_DDR |= (1 << nRF_CE);
	nRF_CSN_HIGH;

	_delay_ms(100);
	transceiverSetPRX();
	transceiverFlushStatus();
	transceiverFlushFIFO();

    EICRA |= (1 << ISC01);
	EIMSK |= (1 << INT0);
	sei();
}

void transceiverSetPTX()
{
	unsigned char mask = PTX_MASK;
	transceiverWriteRegister(CONFIG, &mask, sizeof(mask));
	mask = DYNPD_MASK;
	transceiverWriteRegister(DYNPD, &mask, sizeof(mask));
	mask = FEATURE_MASK;
	transceiverWriteRegister(FEATURE, &mask, sizeof(mask));	
	transceiverPowerUp();
	nRF_CE_LOW;
}

void transceiverSetPRX()
{
	unsigned char mask = PRX_MASK;
	transceiverWriteRegister(CONFIG, &mask, sizeof(mask));
	mask = DYNPD_MASK;
	transceiverWriteRegister(DYNPD, &mask, sizeof(mask));
	mask = FEATURE_MASK;
	transceiverWriteRegister(FEATURE, &mask, sizeof(mask));		
	transceiverPowerUp();
	nRF_CE_HIGH;
	_delay_us(150);
}

void transceiverPowerUp()
{
	unsigned char config;

	transceiverReadRegister(CONFIG, &config, 1);
	config |= (1 << PWR_UP);
	transceiverWriteRegister(CONFIG, &config, 1);
	_delay_ms(2);
}

void transceiverPowerDown()
{
	unsigned char config;
	
	transceiverReadRegister(CONFIG, &config, 1);
	config &= ~(1 << PWR_UP);
	transceiverWriteRegister(CONFIG, &config, 1);
}

void transceiverTrasmit()
{
	transceiverWriteRegister(W_TX_PAYLOAD, payload, PAYLOAD_SIZE);
	nRF_CE_HIGH;
	_delay_us(15);
	nRF_CE_LOW;
	_delay_us(150);
	transceiverFlushStatus();
	transceiverFlushFIFO();
}

void transceiverReceive()
{
	transceiverReadRegister(R_RX_PAYLOAD, payload, PAYLOAD_SIZE);
	transceiverFlushStatus();
	transceiverFlushFIFO();
}

void transceiverWriteAck(unsigned char *buf, unsigned char len)
{
{
  unsigned char command = *buf;
  command |= W_ACK_PAYLOAD;
  transceiverCommand(command);  
}	
}

void transceiverFlushStatus()
{
	unsigned char mask = STATUS_CLEAR_MASK;
	transceiverWriteRegister(STATUS, &mask, sizeof(mask));
}

void transceiverFlushFIFO()
{
	transceiverCommand(FLUSH_TX);
	transceiverCommand(FLUSH_TX);
}
