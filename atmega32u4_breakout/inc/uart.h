/*
 * uart.h
 *
 * Created: 2024-03-16 오후 5:13:23
 *  Author: sw
 */ 
#include "def.h"

#define UART_CH1        1       // UART
#define UART_CH2        2       // USB CDC

void uartInit();
uint8_t uartAvailable(uint8_t ch);
void uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length);
uint8_t uartRead(uint8_t ch);
void uartPrintf(uint8_t, const char *fmt, ...);