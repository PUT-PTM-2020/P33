#ifndef SRC_LED_H_
#define SRC_LED_H_

#include "main.h"
#include <stdlib.h>
#include <stdio.h>
//Constants
#define REG_NOOP 0x0
#define REG_DIGIT0 0x1
#define REG_DIGIT1 0x2
#define REG_DIGIT2 0x3
#define REG_DIGIT3 0x4
#define REG_DIGIT4 0x5
#define REG_DIGIT5 0x6
#define REG_DIGIT6 0x7
#define REG_DIGIT7 0x8
#define REG_DECODEMODE 0x9
#define REG_INTENSITY 0xA
#define REG_SCANLIMIT 0xB
#define REG_SHUTDOWN 0xC
#define REG_DISPLAYTEST 0xF

//functions defines
short* value(char asciiCode);
void max_init(SPI_HandleTypeDef* spi);
void command(uint8_t reg, uint8_t data);
void clear();
void rotate_left(uint8_t redraw);
void rotate_right(uint8_t redraw);
void scroll_left(uint8_t redraw);
void scroll_right(uint8_t redraw);
void orientate(int angle,uint8_t redraw);
void letter(short deviceId, short asciiCode, uint8_t redraw);
void showMessage(char* text,int size);
void flush();
void brightness(uint8_t intense);
void open();
void close();
void write(uint8_t buf[],int size);
uint8_t* values(short position, uint8_t buf[]);
void setByte(int deviceId, short position, uint8_t value);
uint8_t* rotate88(uint8_t buf[]);
uint8_t* rotate(uint8_t buf[]);

#endif /* SRC_LED_H_ */
