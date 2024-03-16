/*
 * atmega32u4_breakout.c
 *
 * Created: 2024-03-16 오후 1:54:39
 * Author : sw
 */ 
#include <avr/io.h>

int main(void)
{
    /* Replace with your application code */
    DDRD= 0xff;
    while (1) 
    {
        PORTD=0xff;
    }
}

