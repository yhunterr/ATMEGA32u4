/*
 * ssd1306.c
 *
 * Created: 2024-04-10 오후 7:22:53
 *  Author: sw
 */ 


#include "ssd1306.h"
#include "ssd1306_data.h"
#include "i2c.h"
#include "cli.h"

uint8_t _i2c_address=0x3c;    //display write address
uint8_t ssd1306_ROW;
uint8_t ssd1306_COLUMN;

void  ssd1306_command(uint8_t c)
{
    uint8_t control = 0x00;
    i2c_write2(_i2c_address,control,c);
}

///////////////////////////////////////////////////
// Used when doing Horizontal or Vertical Addressing
void setColAddress()
{
    ssd1306_command(SSD1306_COLUMNADDR); // 0x21 COMMAND
    ssd1306_command(0); // Column start address
    ssd1306_command(SSD1306_LCDWIDTH-1); // Column end address
}

/////////////////////////////////////////////////////
// Used when doing Horizontal or Vertical Addressing
void setPageAddress()
{
    ssd1306_command(SSD1306_PAGEADDR); // 0x22 COMMAND
    ssd1306_command(0); // Start Page address
    ssd1306_command((SSD1306_LCDHEIGHT/8)-1);// End Page address
}

void setup()
{
    // Initialze SSD1306 OLED display
    ssd1306_COLUMN = ssd1306_ROW = 0;
    reset_display();              // Clear screen
    sendStrXY("Hello",0,0);
    sendStrXY("wowon",1,0);
}


///////////////////////////////////////////////////////////////////
// init according to SSD1306 data sheet and many places on the web
void  ssd1306_init()
{
    _delay_ms(100);
    ssd1306_ROW = ssd1306_COLUMN =0;
    // Init sequence for 128x64 OLED module
    ssd1306_command(SSD1306_DISPLAYOFF);                    // 0xAE

    ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
    ssd1306_command(0x80);                                  // the suggested ratio 0x80
    
    ssd1306_command(SSD1306_SETMULTIPLEX);                  // 0xA8
    ssd1306_command(0x3F);
    
    ssd1306_command(SSD1306_SETDISPLAYOFFSET);              // 0xD3
    ssd1306_command(0x0);                                   // no offset
    
    ssd1306_command(SSD1306_SETSTARTLINE);// | 0x0);        // line #0
    
    ssd1306_command(SSD1306_CHARGEPUMP);                    // 0x8D
    ssd1306_command(0x14);  // using internal VCC
    
    ssd1306_command(SSD1306_MEMORYMODE);                    // 0x20
    ssd1306_command(0x10);                                  // 0x10 Page addressing mode
    
    ssd1306_command(SSD1306_SEGREMAP | 0x1); // rotate screen 180 0xA0
    
    ssd1306_command(SSD1306_COMSCANDEC); // rotate screen 180 0xC8
    
    ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
    ssd1306_command(0x12);
    
    ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
    ssd1306_command(0xCF);
    
    ssd1306_command(SSD1306_SETPRECHARGE);                  // 0xd9
    ssd1306_command(0xF1);
    
    ssd1306_command(SSD1306_SETVCOMDETECT);                 // 0xDB
    ssd1306_command(0x40);
    
    ssd1306_command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
    
    ssd1306_command(SSD1306_NORMALDISPLAY);                 // 0xA6
    
    ssd1306_command(SSD1306_DISPLAYON);                     //switch on OLED
    setup();
}

void reset_display(void)
{
    displayOff();
    clear_display();
    displayOn();
}

//==========================================================//
// Turns display on.
void displayOn(void)
{
    ssd1306_command(0xaf);        //display on
}

//==========================================================//
// Turns display off.
void displayOff(void)
{
    ssd1306_command(0xae);		//display off
}

//==========================================================//
// Clears the display by sending 0 to all the screen map.
void clear_display(void)
{
    unsigned char i,k;
    for(k=0;k<8;k++)
    {
        setXY(k,0);
        {
            for(i=0;i<128;i++)     //clear all COL
            {
                SendChar(0);         //clear all COL
            }
        }
    }
}

//==========================================================//
// Clears the display by sending 0 to 1 row
void clear_display_line(uint8_t row)
{
    int i;
    setXY(row,0);
    {
        for(i=0;i<128;i++)
        {
            SendChar(0);
        }
    }
}

//==========================================================//
// Actually this sends a byte, not a char to draw in the display.
// Display's chars uses 8 byte font the small ones and 96 bytes
// for the big number font.
void SendChar(unsigned char data)
{
    i2c_write2(_i2c_address, 0x40, data);
}

//==========================================================//
// Set the cursor position in a 16 COL * 8 ROW map.
void setXY(unsigned char row,unsigned char col)
{
    ssd1306_command(0xb0+row);                //set page address
    ssd1306_command(0x00+(8*col&0x0f));       //set low col address
    ssd1306_command(0x10+((8*col>>4)&0x0f));  //set high col address
    ssd1306_ROW = row;
}

//==========================================================//
// Prints a string regardless the cursor position.
void sendStr(char *string)
{
    unsigned char i=0;
    while(*string)
    {
        for(i=0;i<8;i++)
        {
            SendChar(pgm_read_byte(myFont[*string-0x20]+i));
        }
        string++;
    }
}

//==========================================================//
// Prints a string in coordinates X Y, being multiples of 8.
// This means we have 16 COLS (0-15) and 8 ROWS (0-7).
void sendStrXY(char *string, int X, int Y)
{
    setXY(X,Y);
    unsigned char i=0;
    while(*string)
    {
        for(i=0;i<8;i++)
        {
            SendChar(pgm_read_byte(myFont[*string-0x20]+i));
        }
        string++;
    }
}

void sendTestDisplay()
{
    uint8_t cnt;
    uint8_t cnt2;
    uint8_t cnt3 = 0;
    uint8_t cnt4 = 0;
    for(cnt = 0; cnt<8; cnt++)
    {
        setXY(cnt, 0);
        for(cnt2=0 ; cnt2<128 ; cnt2++)
        {
            SendChar(0xff);
            _delay_ms(2);
        }
    }
    for(cnt = 0; cnt<8; cnt++)
    {
        setXY(cnt, 0);
        for(cnt2=0 ; cnt2<128 ; cnt2++)
        {
            SendChar(0x00);
            _delay_ms(2);
        }
    }
    
    for(cnt = 0; cnt<7; cnt++)
    {
        setXY(cnt, 0);
        for(; cnt3 < cnt4 ; cnt3 ++)
        {
            for(cnt2=0;cnt2<8;cnt2++)
            {
                SendChar(pgm_read_byte(myFont[cnt3]+cnt2));
            }
        }
        cnt4 += 16;
    }
}

void clissd1306(cli_args_t *args)
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
        if(strcasecmp(pre_char, "CLEAR") == 0)
        {
            reset_display();
            cliPrintf("display clear\n");
        }
        else if(strcasecmp(pre_char,"TEST") == 0)
        {
            sendTestDisplay();
            cliPrintf("display test\n");
        }
        
        ret = true;
    }
    else if(argc == 2)
    {
        if(strcasecmp(pre_char,"PRINT") == 0)
        {
            ssd1306_ROW++;
            ssd1306_ROW = ssd1306_ROW % 8;
            clear_display_line(ssd1306_ROW);
            sendStrXY((char *)argv[1], ssd1306_ROW, 0);
            cliPrintf("print string : %s\n",(char *)argv[1]);
            cliPrintf("print row : %d\n",ssd1306_ROW);
        }
        ret = true;
    }


    if(ret == false)
    {
        cliPrintf("------------------- \n");
        cliPrintf("ssd1306 clear \n" );
        cliPrintf("ssd1306 test \n" );
        cliPrintf("ssd1306 print [string] => ssd1306 print hi \n" );
        cliPrintf("------------------- \n");
    }
}