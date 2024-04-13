/*
 * i2c.c
 *
 * Created: 2024-04-05 오후 10:39:23
 *  Author: sw
 */ 

#include "i2c.h"
#include "cli.h"

void i2cInit()
{
    PORTD |= 0x03; // SDA,SCL pull-up setting PD0: SCL, PD1: SDA
    TWBR = 0x48; /* SCL 100kHz */
    TWSR = 0x00;  	
    TWCR = (1<<TWINT)|(1<<TWEN);
}

void i2c_stop()
{
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

uint8_t i2c_start()
{
    _delay_ms(1);
    /* Start */
    TWCR = (1<<TWSTA)|(1<<TWINT)|(1<<TWEN); //start

    /* Start check */
    while(1)
    {
        if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x08))
            return 1;
    }
}

uint8_t i2c_restart()
{
    /* REPEAT START */
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    /* ReStart check */
    while(1)
    {
        if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x10))
          return 1;
        else if ((TWCR & 0x80) && ((TWSR & 0xf8) == 0x08))
        {
            return 0;
        }
    }
}


uint8_t i2c_write_addr(uint8_t addr)
{
    /* Address send */
    TWDR = addr<<1 | 0; // slave address, write
    TWCR = (1<<TWINT)|(1<<TWEN);

    /* ACK Check */
    while(1)
    {
        if((TWCR & 0x80) && ((TWSR & 0xf8) ==0x18))
        {
            return 1;
        }
        if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x20))
        {
            return 0;
        }
    }
}

uint8_t i2c_read_addr(uint8_t addr)
{
    /* Address send */
    TWDR = addr<<1 | 1; // slave address, write
    TWCR = (1<<TWINT)|(1<<TWEN);

    /* ACK Check */
    while(1)
    {
        if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x40))
        {
            return 1;
        }
        if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x48))
        {
            return 0;
        }
    }
}
uint8_t i2c_write_data(uint8_t data)
{
    /*  Data send */
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);

    /* Data send check */
    while(1)
    {
        if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x28))
        {
            return 1;
        }        
        if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x30))
        {
            return 0;
        }
    }
}

uint8_t i2c_write_read(uint8_t *data1)
{
    /* send NACK*/
    TWCR = (1<<TWINT)|(1<<TWEN); //NACK
    /* Data receive Check */
    while(1)
    {
        if((TWCR & 0x80) && (((TWSR & 0xf8) == 0x50) || ((TWSR & 0xf8) == 0x58)))
        {
            *data1 = TWDR;
            return 1;
        }     
    }
}

/* 
    combination write/read function 
*/

uint8_t i2c_write1(uint8_t addr, uint8_t data1)
{
    if(i2c_start() == 0)
    {
        i2c_stop();
        return 0;
    }
    if(i2c_write_addr(addr) == 0)
    {
        i2c_stop();
        return 0;
    }
    if(i2c_write_data(data1) == 0)
    {
        i2c_stop();
        return 0;
    }
    i2c_stop();
    return 1;
}

uint8_t i2c_write2(uint8_t addr, uint8_t data1,uint8_t data2)
{
    if(i2c_start() == 0)
    {
        i2c_stop();
        return 0;
    }
    if(i2c_write_addr(addr) == 0)
    {
        i2c_stop();
        return 0;
    }
    if(i2c_write_data(data1) == 0)
    {
        i2c_stop();
        return 0;
    }
    if(i2c_write_data(data2) == 0)
    {
        i2c_stop();
        return 0;
    }
    i2c_stop();
    return 1;
}
uint8_t i2c_write3(uint8_t addr, uint8_t data1,uint8_t data2, uint8_t data3)
{
    if(i2c_start() == 0)
    {
        i2c_stop();
        return 0;
    }
    if(i2c_write_addr(addr) == 0)
    {
        i2c_stop();
        return 0;
    }
    if(i2c_write_data(data1) == 0)
    {
        i2c_stop();
        return 0;
    }
    if(i2c_write_data(data2) == 0)
    {
        i2c_stop();
        return 0;
    }
   if(i2c_write_data(data3) == 0)
   {
       i2c_stop();
       return 0;
   }
    i2c_stop();
    return 1;
}
uint8_t i2c_read1(uint8_t addr, uint8_t data1, uint8_t *save_data1)
{
    if(i2c_start() == 0)
    {
        i2c_stop();
        return 0;
    }
    if(i2c_write_addr(addr) == 0)
    {
        i2c_stop();
        return 0;
    }
    if(i2c_write_data(data1) == 0)
    {
        i2c_stop();
        return 0;
    }
    if(i2c_restart() == 0)
    {
        i2c_stop();
        return 0;
    }
    if(i2c_read_addr(addr) == 0)
    {
        i2c_stop();
        return 0;
    }
    if(i2c_write_read(save_data1) == 0)
    {
        i2c_stop();
        return 0;
    }
    i2c_stop();
    return 1;
}
uint8_t i2c_write_multi(uint8_t addr, uint8_t *data, uint8_t cnt)
{
    uint8_t loop;
    if(i2c_start() == 0)
    {
        i2c_stop();
        return 0;
    }
    if(i2c_write_addr(addr) == 0)
    {
        i2c_stop();
        return 0;
    }
    for(loop = 0; loop < cnt ; loop++)
    {
        if(i2c_write_data(data[loop]) == 0)
        {
            i2c_stop();
            return 0;
        }
    }
    i2c_stop();
    return 1;
}

void cliI2c(cli_args_t *args)
{
    bool ret = false;
    uint8_t result = false;
    int    argc = args->argc;
    char **argv = args->argv;
    int cnt=0;
    char *pre_char = NULL;
    uint8_t read_data1;
    if(argc != 0)
    {
        pre_char = (char *)argv[0];
    }   
    
    if(argc == 1)
    {
        if(strcasecmp(pre_char,"SEARCH") == 0)
        {
            for(cnt=0; cnt <= 127 ; cnt++)
            {
                if(i2c_start() == 1)
                {
                    if(i2c_write_addr(cnt) == 1)
                    {
                        cliPrintf("search : 0x%02x\n",cnt);
                    }
                    i2c_stop();
                }            
            }
            cliPrintf("search end\n");
        }  
        ret = true;
    }
    else if(argc == 2)
    {
        if(strcasecmp(pre_char,"RALL") == 0)
        {
            for(cnt=0; cnt <= 255 ; cnt++)
            {
                result = i2c_read1((int)strtoul((const char * ) argv[1], (char **)NULL, (int) 0),(int)strtoul((const char * ) argv[2], (char **)NULL, (int) 0),&read_data1);
                if(result == 1)
                {
                    cliPrintf("Read data(0x%02x) : 0x%02x \n",cnt, read_data1);
                }
                else if(result ==0)
                {
                    cliPrintf("Read data(0x%02x) :i2c read fail \n",cnt);
                }
                result = 0;
            }
            ret = true;
        }
    }
    else if(argc == 3)
    {

        if(strcasecmp(pre_char,"R") == 0)
        {
            result = i2c_read1((int)strtoul((const char * ) argv[1], (char **)NULL, (int) 0),(int)strtoul((const char * ) argv[2], (char **)NULL, (int) 0),&read_data1);
            if(result == 1)
            {
                cliPrintf("Read data : 0x%02x \n",read_data1);
            }
            else if(result ==0)
            {
                cliPrintf("i2c read fail \n");
            }
        }
        else if(strcasecmp(pre_char,"W") == 0)
        {
            result = i2c_write1((int)strtoul((const char * ) argv[1], (char **)NULL, (int) 0),(int)strtoul((const char * ) argv[2], (char **)NULL, (int) 0));
            if(result == 1)
            {
                cliPrintf("i2c write success \n");
            }
            else if(result == 0)
            {
                cliPrintf("i2c write fail \n");
            }
        }
        ret = true;       
    }    
    else if(argc == 4)
    {
        if(strcasecmp(pre_char,"W") == 0)
        {
            result = i2c_write2((int)strtoul((const char * ) argv[1], (char **)NULL, (int) 0),(int)strtoul((const char * ) argv[2], (char **)NULL, (int) 0),(int)strtoul((const char * ) argv[3], (char **)NULL, (int) 0));
            if(result == 1)
            {
                cliPrintf("i2c write success \n");
            }
            else if(result == 0)
            {
                cliPrintf("i2c write fail \n");
            }
        }
        ret = true;
    }
    
    if(ret == false)
    {
        cliPrintf("------------------- \n");
        cliPrintf("i2c search \n");
        cliPrintf("i2c rall [addr]=> i2c rall 0x01\n");
        cliPrintf("i2c r [addr] [data2] => i2c r 0x01 0x02 \n");
        cliPrintf("i2c w [addr] [data2] [data3] (max data3) => i2c w 0x01 0x02 0x03\n");
        cliPrintf("------------------- \n");
    }
} 