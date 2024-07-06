/*
 * led.c
 *
 * Created: 2024-03-17 오후 1:00:13
 *  Author: sw
 */ 

#include "led.h"


void ledInit()
{
    DDRD |= 0x20;
    DDRC |= 0xC0;
}

void ledOn(uint8_t ch)
{
    if(ch == LED_CH1)
    {
        PORTD |= (1<<PORTD5);
    }
    else if (ch == LED_CH2)
    {
        PORTC |= (1<<PORTC6);
    }
    else if (ch == LED_CH3)
    {
        PORTC |= (1<<PORTC7);
    }
}

void ledOff(uint8_t ch)
{
    if(ch == LED_CH1)
    {
        PORTD &= ~(1<<PORTD5);
    }
    else if (ch == LED_CH2)
    {
        PORTC &= ~(1<<PORTC6);
    }
    else if (ch == LED_CH3)
    {
        PORTC &= ~(1<<PORTC7);
    }
}

void ledToggle(uint8_t ch)
{
    if(ch == LED_CH1)
    {
        if(PORTD & (1<<PORTD5))
            ledOff(ch);
        else
            ledOn(ch);
    }
    else if(ch == LED_CH2)
    {
        if(PORTC & (1<<PORTC6))
            ledOff(ch);
        else
            ledOn(ch);
    }
    else if(ch == LED_CH3)
    {
        if(PORTC & (1<<PORTC7))
            ledOff(ch);
        else
            ledOn(ch);
    }
}