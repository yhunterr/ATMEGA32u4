/*
 * atmega32u4_breakout.c
 *
 * Created: 2024-03-16 오후 1:54:39
 * Author : sw
 */ 
#include "main.h"

void mainInit()
{
    ledInit();
    uartInit();
    usb_cdc_init();
}

int main(void)
{
    mainInit();
    ledOn(LED_CH1);

    while (1) 
    {
        if(uartAvailable(UART_CH1))
        {
            ledToggle(LED_CH1);
            uartPrintf(UART_CH1, "CH1 received : %c \n", uartRead(UART_CH1));
        }
                
        if(uartAvailable(UART_CH2))
        {
            ledToggle(LED_CH1);
            uartPrintf(UART_CH2, "CH2 received : %c \n", uartRead(UART_CH2));
        }
    }
}


