/*
 * int.c
 *
 * Created: 2024-04-27 오후 8:21:46
 *  Author: sw
 */ 

#include "int.h"
#include "cli.h"

void intInit()
{
    DDRE &= ~0x40; // PE6
    PORTE |= 0x40;
    EIMSK &= ~(1<<INT6);
    EICRB = (1<<ISC61) | (0<<ISC60); // Falling edge
    /*
        ISC61 ISC60 Description
        0     0     low level
        0     1     both edge
        1     0     falling edge
        1     1     rising edge
    */
    EIMSK |= (1<<INT6);
}

ISR(INT6_vect)
{
    cliPrintf("\nINT6 Interrupt \n");
}

void cliint(cli_args_t *args)
{
    bool ret = false;
    int    argc = args->argc;
    char **argv = args->argv;
    char *pre_char = NULL;
    if(argc != 0)
    {
        pre_char = (char *)argv[0];
    }
    
    if(argc == 1 )
    {
        if(strcasecmp(pre_char, "rising") == 0)
        {
            PORTE &= ~0x40;
            EIMSK &= ~(1<<INT6);
            EICRB = (1<<ISC61) | (1<<ISC60);
            EIMSK |= (1<<INT6);
        }
        else if(strcasecmp(pre_char,"falling") == 0)
        {
            PORTE |= 0x40;
            EIMSK &= ~(1<<INT6);
            EICRB = (1<<ISC61) | (0<<ISC60);
            EIMSK |= (1<<INT6);
        }
        else if(strcasecmp(pre_char,"both") == 0)
        {
            PORTE |= 0x40;
            EIMSK &= ~(1<<INT6);
            EICRB = (0<<ISC61) | (1<<ISC60);
            EIMSK |= (1<<INT6);
        }
        else if(strcasecmp(pre_char,"low") == 0)
        {
            PORTE |= 0x40;
            EIMSK &= ~(1<<INT6);
            EICRB = (0<<ISC61) | (0<<ISC60);
            EIMSK |= (1<<INT6);
        }
        ret = true;
    }



    if(ret == false)
    {
        cliPrintf("------------------- \n");
        cliPrintf("only change INT6(PE6).. default is falling edge \n" );
        cliPrintf("int low \n" );
        cliPrintf("int both \n" );
        cliPrintf("int rising \n" );
        cliPrintf("int falling \n" );
        cliPrintf("------------------- \n");
    }
}