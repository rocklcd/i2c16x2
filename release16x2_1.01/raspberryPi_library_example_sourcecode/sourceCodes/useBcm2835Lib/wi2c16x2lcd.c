/*
 * wi2c16x2lcd.c
 * 
 * 
 * 
 * * ***************************************************************************
 # This program is a free software. You can use/modify/distribute freely upon
 # agreeing the followings.
 #
 # DISCLAIMER:
 # NO WARRANTY or implied warranty of any kind. Any user who makes use 
 # of this software shall be solely responsible for any liability/direct
 # lose/indirect lose which may occur.
 #
 # ***************************************************************************
 *
 * 
 * 
 * How to install bcm2835 library on raspberrypi:
 * (Reference to http://www.airspayce.com/mikem/bcm2835/)
 * (Use the latest version, the version used here is version 1.50)
 * 
 *
 * 1.open a command window on raspberrypi
 * 2.wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.50.tar.gz 
 * 3.tar zxvf bcm2835-1.50.tar.gz
 * 4.cd bcm2835-1.50
 * 5../configure
 * 6.make
 * 7.sudo make check
 * 8.sudo make install
 * 9.sudo raspi-config
 * 10. "go to advance options and enable I2C"
 * 11. "reboot the system"
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bcm2835.h>


#define DELAY5  5

//I2C control parameters
#define I2C_ADDR  0x3C
#define INSTRUCTION  0x00
#define CHAR  0x40


//basic instructions
//(Can create your own according to HD44780 instruction sets)
#define TWO_LINE_MODE  0x38
#define CLR_SCREEN  0x01
#define RET_HOME  0x02
#define DISPLAY_ON_CURSOR_OFF  0x0C
#define DISPLAY_ON_CURSOR_ON  0x0E
#define DISPLAY_OFF_CURSOR_OFF  0x08
#define BLANK_CHAR  0x20

//global varible
//allowing input 16 characters per line 
char message[17];


void lcd_write_instruction(int inst);
void lcd_write_character(int character);
void lcd_write_string(char *msg);
int jump(int line,int position);
void wlcd(int ln , int posi , char *list);
void clr_line(int line_no);
int lcd_init();



//int main()
//{
	//printf("doing nothing");
	//return 0;
//}

void wlcd(int ln , int posi, char *list)
{
	int status = jump(ln, posi);
	if(status != 0xFF)
	{
    lcd_write_instruction(status);
    lcd_write_string(list);
	}
    return ;
	
}

void lcd_write_instruction(int inst)
{
	const char write_buf [2] = { INSTRUCTION , inst } ;
	bcm2835_i2c_write(write_buf , 2);
	bcm2835_delay(DELAY5);
}
	
	
void lcd_write_character(int character)
{
	const char write_buf [2] = { CHAR , character } ;
	bcm2835_i2c_write(write_buf , 2);
	bcm2835_delay(DELAY5);
}

void lcd_write_string(char *msg)
{
	int ii =  0;
	int iline1 [17] ;
	int numaa ;
	
	delay(DELAY5);
	
	for ( ii=0;  ii< 16; ii++)
		{
			iline1[ii] = msg[ii];//cast char to int (ASCII code)
			numaa= iline1[ii];
			if (numaa==10 || numaa==0)
			{
				return;
			}
			lcd_write_character(numaa);
			delay(DELAY5);
		}
}


int jump(int line, int position)
{
    int pos ;
    if ((1 > position) || (position >16)) 
    {
        lcd_write_instruction(CLR_SCREEN);
        strncpy(message, "invalid position", 17);
        lcd_write_string(message);
        return 0xFF;
	}
    
    if (line == 1 )
    {
        pos = 0x80 + position - 1 ;
        return pos ;
     }
    else if (line == 2 )
    {
        pos = 0xC0 + position - 1 ;
        return pos ;
	}
    else 
    {
        lcd_write_instruction(CLR_SCREEN);
        strncpy(message, "invalid line", 17);
        lcd_write_string(message);
        return 0xFF ;
    }
}

void clr_line(int line_no)
{
	
    lcd_write_instruction(jump(line_no, 1));
    int ia=0 ;
    for (ia=0 ; ia< 16 ; ia++)
    {
		lcd_write_character(BLANK_CHAR);
	}
    
    return ;
	
}
	
	
int lcd_init()
{
	if(!bcm2835_init())return 1;
	bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(I2C_ADDR);
	bcm2835_i2c_setClockDivider(2500);
	bcm2835_i2c_set_baudrate(400000);
	
	lcd_write_instruction(TWO_LINE_MODE) ;
    lcd_write_instruction(DISPLAY_ON_CURSOR_OFF) ;
	
	return 0;
}
	




	

