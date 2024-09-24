#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>
#include <stdarg.h>

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t length);
void Serial_SendString(char *String);
void Serial_SendNum(uint32_t Num, uint8_t length);
void Serial_Printf(char *format, ...);

#endif
