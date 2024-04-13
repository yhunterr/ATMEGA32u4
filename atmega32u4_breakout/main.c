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
    i2cInit();
    usb_cdc_init();
    cliInit();
    ssd1306_init();
}

int main(void)
{
    mainInit();
    ledOn(LED_CH1);

    while (1) 
    {
        cliMain();
    }
}


