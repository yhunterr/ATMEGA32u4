/*
 * i2c.h
 *
 * Created: 2024-04-05 오후 10:39:15
 *  Author: sw
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "def.h"

void i2cInit();
uint8_t i2c_write1(uint8_t addr, uint8_t data1);
uint8_t i2c_write2(uint8_t addr, uint8_t data1,uint8_t data2);
uint8_t i2c_write3(uint8_t addr, uint8_t data1,uint8_t data2, uint8_t data3);
uint8_t i2c_write_multi(uint8_t addr, uint8_t *data, uint8_t cnt);
uint8_t i2c_read1(uint8_t addr, uint8_t data1, uint8_t *save_data1);

#endif /* I2C_H_ */