/*
 * w16x2lcd.c
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


unsigned int delay10 = 5;
unsigned int delay1000 = 1000;

//I2C control parameters
int I2C_ADDR = 0x3C;
int INSTRUCTION = 0x00;
int CHAR = 0x40;


//basic instructions
//(Can create your own according to HD44780 instruction sets)
int TWO_LINE_MODE = 0x38;
int CLR_SCREEN = 0x01;
int RET_HOME = 0x02;
int DISPLAY_ON_CURSOR_OFF = 0x0C;
int DISPLAY_ON_CURSOR_ON = 0x0E;
int DISPLAY_OFF_CURSOR_OFF = 0x08;

//global varible
//allowing input 16 characters per line 
//you can change the number up tp 41
char message[17];
int BLANK_CHAR = 0x20;

void lcd_write_instruction(int inst);
void lcd_write_character(int character);
void lcd_write_string(char *str_list , int leng);
int jump(int line,int position);



int main(int argc, char **argv)
{
	//a simple example
    //printf("Program starts \n") ;
    if(!bcm2835_init())return 1;
    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(I2C_ADDR);
	bcm2835_i2c_setClockDivider(2500);
	bcm2835_i2c_set_baudrate(400000);
	
    lcd_write_instruction(TWO_LINE_MODE) ;
    lcd_write_instruction(DISPLAY_ON_CURSOR_OFF) ;
    
    if (argc == 1)
    {
	 printf( "w16x2lcd c will clear the lcd screen \n");
	 printf( "w16x2lcd c 1 will clear the first line \n");
	 printf( "w16x2lcd c 2 will clear the second line \n");
     printf("w16x2lcd l p display message \n ") ;
     printf("l is the line number, p is the position \n");
     printf("display message should not be more than 16 characters \n");
     
	}
	
	if (argc == 2 )
	{
		int clear = *argv[1];
		//printf("clear= %d \n", clear);
		if (clear == 0x63 )
		{
			lcd_write_instruction(CLR_SCREEN) ;
		}
	}
	
	if (argc == 3)
	{
		int clear = *argv[1];
		if (clear == 0x63)
		{
			int ia;
			int nline = atoi(argv[2]);
			//printf("newline = %d \n", nline);
			int clr_line = jump(nline,1);
			//printf("clr_line = %x \n", clr_line);
			lcd_write_instruction(clr_line);
			for (ia =0 ; ia<16 ; ia ++)
			{ 
				lcd_write_character(BLANK_CHAR);
			}
		}
	}
	 
	if (argc > 3)
	{ 
		int ix;
		int l = atoi(argv[1]);
		int p = atoi(argv[2]);    
		int new_position = jump(l,p);
    
		if (new_position == 0xFF )
		{
			return 1;
		}
		else 
		{
			lcd_write_instruction(new_position);
			for (ix = 3 ; ix < argc ;ix ++ )
			{
				//printf( "argc = %d \n" , ix);
				//printf( "argv = %s \n", argv[ix]);
				int length = strlen(argv[ix]);
				//printf( "length = %d \n" , length);
				strncpy(message, argv[ix] , length);
				//printf("message = %s \n" , message);
				lcd_write_string(message , length);
				lcd_write_character(BLANK_CHAR);
			}
		}
	}
      
    return 0;
	
}

void lcd_write_instruction(int inst)
{
	const char write_buf [2] = { INSTRUCTION , inst } ;
	bcm2835_i2c_write(write_buf , 2);
	bcm2835_delay(delay10);
}
	
	
void lcd_write_character(int character)
{
	const char write_buf [2] = { CHAR , character } ;
	bcm2835_i2c_write(write_buf , 2);
	bcm2835_delay(delay10);
}


void lcd_write_string(char *str_list , int leng)
{
	int ii =  0;
	int iline1 [leng] ;
	
	int numaa ;
	
	delay(delay10);
	for ( ii=0;  ii< leng; ii++)
		{
			iline1[ii] = str_list[ii];
			numaa= iline1[ii];
			//printf("numaa= %d \n", numaa);
			if (numaa==10 || numaa==0)
			{
				return;
			}
			lcd_write_character(numaa);
			delay(delay10);
		}
}


int jump(int line, int position)
{
    int pos ;
    if ((1 > position) || (position >16)) 
    {
        //printf("invalid position"); 
        lcd_write_instruction(CLR_SCREEN);
        strncpy(message, "invalid position", 17);
        lcd_write_string(message , 17);
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
        //print("invalid line");
        lcd_write_instruction(CLR_SCREEN);
        strncpy(message, "invalid line", 17);
        lcd_write_string(message , 17);
        return 0xFF ;
    }
}
	
	

