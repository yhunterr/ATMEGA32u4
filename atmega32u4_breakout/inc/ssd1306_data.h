﻿/*
 * ssd1306_data.h
 *
 * Created: 2024-04-10 오후 7:25:13
 *  Author: sw
 */ 


#ifndef SSD1306_DATA_H_
#define SSD1306_DATA_H_

#include "def.h"

// Small 8x8 font
const unsigned char PROGMEM myFont[][8] PROGMEM = {
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x5F,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x07,0x00,0x07,0x00,0x00,0x00},
    {0x00,0x14,0x7F,0x14,0x7F,0x14,0x00,0x00},
    {0x00,0x24,0x2A,0x7F,0x2A,0x12,0x00,0x00},
    {0x00,0x23,0x13,0x08,0x64,0x62,0x00,0x00},
    {0x00,0x36,0x49,0x55,0x22,0x50,0x00,0x00},
    {0x00,0x00,0x05,0x03,0x00,0x00,0x00,0x00},
    {0x00,0x1C,0x22,0x41,0x00,0x00,0x00,0x00},
    {0x00,0x41,0x22,0x1C,0x00,0x00,0x00,0x00},
    {0x00,0x08,0x2A,0x1C,0x2A,0x08,0x00,0x00},
    {0x00,0x08,0x08,0x3E,0x08,0x08,0x00,0x00},
    {0x00,0xA0,0x60,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x08,0x08,0x08,0x08,0x08,0x00,0x00},
    {0x00,0x60,0x60,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x20,0x10,0x08,0x04,0x02,0x00,0x00},
    {0x00,0x3E,0x51,0x49,0x45,0x3E,0x00,0x00},
    {0x00,0x00,0x42,0x7F,0x40,0x00,0x00,0x00},
    {0x00,0x62,0x51,0x49,0x49,0x46,0x00,0x00},
    {0x00,0x22,0x41,0x49,0x49,0x36,0x00,0x00},
    {0x00,0x18,0x14,0x12,0x7F,0x10,0x00,0x00},
    {0x00,0x27,0x45,0x45,0x45,0x39,0x00,0x00},
    {0x00,0x3C,0x4A,0x49,0x49,0x30,0x00,0x00},
    {0x00,0x01,0x71,0x09,0x05,0x03,0x00,0x00},
    {0x00,0x36,0x49,0x49,0x49,0x36,0x00,0x00},
    {0x00,0x06,0x49,0x49,0x29,0x1E,0x00,0x00},
    {0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00},
    {0x00,0x00,0xAC,0x6C,0x00,0x00,0x00,0x00},
    {0x00,0x08,0x14,0x22,0x41,0x00,0x00,0x00},
    {0x00,0x14,0x14,0x14,0x14,0x14,0x00,0x00},
    {0x00,0x41,0x22,0x14,0x08,0x00,0x00,0x00},
    {0x00,0x02,0x01,0x51,0x09,0x06,0x00,0x00},
    {0x00,0x32,0x49,0x79,0x41,0x3E,0x00,0x00},
    {0x00,0x7E,0x09,0x09,0x09,0x7E,0x00,0x00},
    {0x00,0x7F,0x49,0x49,0x49,0x36,0x00,0x00},
    {0x00,0x3E,0x41,0x41,0x41,0x22,0x00,0x00},
    {0x00,0x7F,0x41,0x41,0x22,0x1C,0x00,0x00},
    {0x00,0x7F,0x49,0x49,0x49,0x41,0x00,0x00},
    {0x00,0x7F,0x09,0x09,0x09,0x01,0x00,0x00},
    {0x00,0x3E,0x41,0x41,0x51,0x72,0x00,0x00},
    {0x00,0x7F,0x08,0x08,0x08,0x7F,0x00,0x00},
    {0x00,0x41,0x7F,0x41,0x00,0x00,0x00,0x00},
    {0x00,0x20,0x40,0x41,0x3F,0x01,0x00,0x00},
    {0x00,0x7F,0x08,0x14,0x22,0x41,0x00,0x00},
    {0x00,0x7F,0x40,0x40,0x40,0x40,0x00,0x00},
    {0x00,0x7F,0x02,0x0C,0x02,0x7F,0x00,0x00},
    {0x00,0x7F,0x04,0x08,0x10,0x7F,0x00,0x00},
    {0x00,0x3E,0x41,0x41,0x41,0x3E,0x00,0x00},
    {0x00,0x7F,0x09,0x09,0x09,0x06,0x00,0x00},
    {0x00,0x3E,0x41,0x51,0x21,0x5E,0x00,0x00},
    {0x00,0x7F,0x09,0x19,0x29,0x46,0x00,0x00},
    {0x00,0x26,0x49,0x49,0x49,0x32,0x00,0x00},
    {0x00,0x01,0x01,0x7F,0x01,0x01,0x00,0x00},
    {0x00,0x3F,0x40,0x40,0x40,0x3F,0x00,0x00},
    {0x00,0x1F,0x20,0x40,0x20,0x1F,0x00,0x00},
    {0x00,0x3F,0x40,0x38,0x40,0x3F,0x00,0x00},
    {0x00,0x63,0x14,0x08,0x14,0x63,0x00,0x00},
    {0x00,0x03,0x04,0x78,0x04,0x03,0x00,0x00},
    {0x00,0x61,0x51,0x49,0x45,0x43,0x00,0x00},
    {0x00,0x7F,0x41,0x41,0x00,0x00,0x00,0x00},
    {0x00,0x02,0x04,0x08,0x10,0x20,0x00,0x00},
    {0x00,0x41,0x41,0x7F,0x00,0x00,0x00,0x00},
    {0x00,0x04,0x02,0x01,0x02,0x04,0x00,0x00},
    {0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00},
    {0x00,0x01,0x02,0x04,0x00,0x00,0x00,0x00},
    {0x00,0x20,0x54,0x54,0x54,0x78,0x00,0x00},
    {0x00,0x7F,0x48,0x44,0x44,0x38,0x00,0x00},
    {0x00,0x38,0x44,0x44,0x28,0x00,0x00,0x00},
    {0x00,0x38,0x44,0x44,0x48,0x7F,0x00,0x00},
    {0x00,0x38,0x54,0x54,0x54,0x18,0x00,0x00},
    {0x00,0x08,0x7E,0x09,0x02,0x00,0x00,0x00},
    {0x00,0x18,0xA4,0xA4,0xA4,0x7C,0x00,0x00},
    {0x00,0x7F,0x08,0x04,0x04,0x78,0x00,0x00},
    {0x00,0x00,0x7D,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x80,0x84,0x7D,0x00,0x00,0x00,0x00},
    {0x00,0x7F,0x10,0x28,0x44,0x00,0x00,0x00},
    {0x00,0x41,0x7F,0x40,0x00,0x00,0x00,0x00},
    {0x00,0x7C,0x04,0x18,0x04,0x78,0x00,0x00},
    {0x00,0x7C,0x08,0x04,0x7C,0x00,0x00,0x00},
    {0x00,0x38,0x44,0x44,0x38,0x00,0x00,0x00},
    {0x00,0xFC,0x24,0x24,0x18,0x00,0x00,0x00},
    {0x00,0x18,0x24,0x24,0xFC,0x00,0x00,0x00},
    {0x00,0x00,0x7C,0x08,0x04,0x00,0x00,0x00},
    {0x00,0x48,0x54,0x54,0x24,0x00,0x00,0x00},
    {0x00,0x04,0x7F,0x44,0x00,0x00,0x00,0x00},
    {0x00,0x3C,0x40,0x40,0x7C,0x00,0x00,0x00},
    {0x00,0x1C,0x20,0x40,0x20,0x1C,0x00,0x00},
    {0x00,0x3C,0x40,0x30,0x40,0x3C,0x00,0x00},
    {0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x00},
    {0x00,0x1C,0xA0,0xA0,0x7C,0x00,0x00,0x00},
    {0x00,0x44,0x64,0x54,0x4C,0x44,0x00,0x00},
    {0x00,0x08,0x36,0x41,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x41,0x36,0x08,0x00,0x00,0x00,0x00},
    {0x00,0x02,0x01,0x01,0x02,0x01,0x00,0x00},
    {0x00,0x02,0x05,0x05,0x02,0x00,0x00,0x00}
};


#endif /* SSD1306_DATA_H_ */