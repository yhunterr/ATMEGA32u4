/*
 * btn.h
 *
 * Created: 2024-07-05 오후 9:14:08
 *  Author: sw
 */ 


#ifndef BTN_H_
#define BTN_H_

#include "def.h"

#define BTN_CH1    1 // PD6
#define BTN_CH2    2 // PD7

void btnInit();
bool btnRead(uint8_t ch);
void btn_detect();


#endif /* BTN_H_ */