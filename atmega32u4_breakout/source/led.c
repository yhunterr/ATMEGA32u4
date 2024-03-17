/*
 * led.c
 *
 * Created: 2024-03-17 오후 1:00:13
 *  Author: sw
 */ 

#include "led.h"


void ledInit()
{
    DDRD |= 0x10;
}

void ledOn(uint8_t ch)
{
    if(ch == LED_CH1)
    {
        PORTD |= (1<<PORTD4);
    }        
}

void ledOff(uint8_t ch)
{
    if(ch == LED_CH1)
    {
        PORTD &= ~(1<<PORTD4);
    }        
}

void ledToggle(uint8_t ch)
{
    if(ch == LED_CH1)
    {
        if(PORTD & (1<<PORTD4))
            ledOff(ch);
        else
            ledOn(ch);
    }        
}