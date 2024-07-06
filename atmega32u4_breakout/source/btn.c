/*
 * btn.c
 *
 * Created: 2024-07-05 오후 9:14:26
 *  Author: sw
 */ 

#include "btn.h"
#include "led.h"

void btnInit()
{
    DDRD &= 0x3f;
    PORTD |= 0xc0; // pull-up
}

bool btnRead(uint8_t ch)
{
    if(ch == BTN_CH1)
    {
        return !(PIND & 0x40);
    }
    else if(ch == BTN_CH2)
    {
        return !(PIND & 0x80);
    }
    return false;
}

void btn_detect()
{
    if(btnRead(BTN_CH1))
    {
        ledOn(LED_CH2);
    }
    else
    {
        ledOff(LED_CH2);
    }
    
    if(btnRead(BTN_CH2))
    {
        ledOn(LED_CH3);
    }
    else
    {
        ledOff(LED_CH3);
    }
}