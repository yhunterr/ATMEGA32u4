/*
 * uart.c
 *
 * Created: 2024-03-16 오후 5:13:31
 *  Author: sw
 */ 
#include "uart.h"
#include "led.h"
#include "usb_cdc.h"
static uint8_t receive_buf = 0;

void uartInit()
{
    UCSR1A = 0x00;
    UCSR1B = (1<<RXCIE1) | (1<<RXEN1) | (1<<TXEN1);
    UCSR1C = (1<<UCSZ11) | (1<<UCSZ10);
    UBRR1H = 0;
    UBRR1L = 8;
    sei();
}

uint8_t uartAvailable(uint8_t ch)
{
    uint8_t ret = 0;
    int k;
    switch(ch)
    {
        case UART_CH1:
            if(receive_buf)
            {
                ret = 1;
            }
            break;
        case UART_CH2:
            k = usb_serial_getchar();
            if(k >= 0)
            {
                ret = 1;
                receive_buf = k;
            }
            break;
    }
    return ret;
}

void uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length)
{
    uint32_t count = 0;
    switch(ch)
    {
        case UART_CH1:
            while(count <length)
            {
                while(!(UCSR1A&(1<<UDRE1)));
                    UDR1 = *p_data;
                p_data++;
                count++;
            }
            break;
        case UART_CH2:
        while(count <length)
        {
            usb_serial_putchar(*p_data);
            p_data++;
            count++;
        }
        break;
    }
}

void uartPrintf(uint8_t ch, const char *fmt, ...)
{
    va_list arg;
    char printf_buf[256];
    int len;
    switch(ch)
    {
        case UART_CH1:
            va_start(arg,fmt);
            len = vsnprintf(printf_buf,256,fmt,arg);
            va_end(arg);
            if(len>0)
            {
                uartWrite(ch, (uint8_t *)printf_buf,len);
            }
            break;
        case UART_CH2:
            va_start(arg,fmt);
            len = vsnprintf(printf_buf,256,fmt,arg);
            va_end(arg);
            if(len>0)
            {
                uartWrite(ch, (uint8_t *)printf_buf,len);
            }
            break;
    }    
}

uint8_t uartRead(uint8_t ch)
{
    uint8_t ret = 0;
    switch(ch)
    {
        case UART_CH1:
            ret = receive_buf;
            receive_buf = 0;
        break;
        case UART_CH2:
            ret = receive_buf;
            receive_buf = 0;
        break;
    }
    return ret;
}


ISR(USART1_RX_vect)
{
    receive_buf = UDR1;
}
