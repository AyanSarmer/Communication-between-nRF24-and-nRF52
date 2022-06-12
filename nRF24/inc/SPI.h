#ifndef SPI_H_
#define SPI_H_

#define F_CPU                   16000000UL

#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>

#define SPI_DDR					DDRD
#define SPI_PORT				PORTD
#define SPI_PIN                 PIND
#define MOSI					PD7 // DI
#define SCK						PD6 // DO
#define MISO					PD5

#define MOSI_HIGH				SPI_PORT |= (1 << MOSI)
#define MOSI_LOW				SPI_PORT &= ~(1 << MOSI)
#define SCK_HIGH				SPI_PORT |= (1 << SCK)
#define SCK_LOW				    SPI_PORT &= ~(1 << SCK)

#define MSBit                   0x80
#define LSBit                   0x01

void spiInit();
uint8_t spiByte(uint8_t _byte);

#endif /* SPI_H_ */