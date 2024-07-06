/*
 * led.h
 *
 * Created: 2024-03-17 오후 12:59:54
 *  Author: sw
 */ 

#include "def.h"

#define LED_CH1    1 // PD5
#define LED_CH2    2 // PC6 
#define LED_CH3    3 // PC7

void ledInit();
void ledOn(uint8_t ch);
void ledOff(uint8_t ch);
void ledToggle(uint8_t ch);