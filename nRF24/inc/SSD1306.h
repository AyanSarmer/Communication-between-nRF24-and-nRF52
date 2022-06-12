#ifndef SSD1306_H_
#define SSD1306_H_

#include <string.h>
#include "SPI.h"

#define CONTROL_DDR                 DDRB
#define CONTROL_PORT                PORTB
#define DC                          PB1
#define DC_COMMAND                  CONTROL_PORT &= ~(1 << DC)
#define DC_DATA                     CONTROL_PORT |=  (1 << DC)
#define CS_SSD1306                  PB2
#define CS_SSD1306_HIGH             CONTROL_PORT |=  (1 << CS_SSD1306)            
#define CS_SSD1306_LOW              CONTROL_PORT &=  ~(1 << CS_SSD1306)  
#define RESET                       PB0
#define RESET_HIGH                  CONTROL_PORT |=  (1 << RESET)            
#define RESET_LOW                   CONTROL_PORT &=  ~(1 << RESET)           


#define SSD1306_LCDWIDTH            128
#define SSD1306_LCDHEIGHT           64

#define BLACK                       0
#define WHITE                       1
#define BACKGROUND_COLOR            BLACK
#define TEXT_COLOR                  WHITE

#define SSD1306_CHARGEPUMP          0x8D
  #define CHARGEPUMP_DISABLE        0x10
  #define CHARGEPUMP_ENABLE         0x14
#define SSD1306_DISPLAYON           0xAF

#define SSD1306_MEMORYMODE          0x20
  #define HORIZONTAL_ADDRESSING     0x00
#define SSD1306_SEGREMAP            0xA0
  #define SEGREMAP_OFF              0x00
  #define SEGREMAP_ON               0x01
#define SSD1306_COMSCANINC          0xC0
#define SSD1306_COMSCANDEC          0xC8
  
#define SSD1306_COLUMNADDR          0x21  
#define SSD1306_PAGEADDR            0x22

void ssd1306Command(unsigned char command);
void ssd1306Data(unsigned char data);    
void ssd1306Init();
void ssd1306SetRotation(unsigned char rotation);
void ssd1306ClearDisplay();
void ssd1306DrawDisplay();

void drawPixel(unsigned int x, unsigned int y, unsigned int color);
 
#endif /* SSD1306_H_ */