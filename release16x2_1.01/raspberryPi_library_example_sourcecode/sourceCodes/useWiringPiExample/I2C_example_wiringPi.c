/*
 * I2C_example_wiringPi.c
 * 
 * 
 * 
 * ***************************************************************************
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
 * How to install wiringPi library on raspberrypi:
 * (Reference to http://wiringpi.com/download-and-install/)
 * 
 * 1. sudo apt-get install git-core
 * 2. sudo apt-get update
 * 3. sudo apt-get upgrade
 * 4. git clone git://git.drogon.net/wiringPi
 * 5. cd wiringPi
 * 6. git pull origin
 * 7. cd wiringPi
 * 8. /build
 * 9. gpio -v (to check installation is ok.)
 * 10. gpio readall
 * 11. sudo raspi-config
 * 12. "go to advance options and enable I2C"
 * 13. "reboot the system"
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
#include <wiringPi.h>
#include <wiringPiI2C.h>


unsigned int delay10 = 5;
unsigned int delay1000 = 1000;

//I2C control parameters
int I2C_ADDR = 0x3C;
int INSTRUCTION = 0x00;
int CHAR = 0x40;
int fd ;


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
void lcd_write_string(char str_list[17]);
int jump(int line,int position);



int main(int argc, char **argv)
{
	//a simple example
    printf("Program starts \n") ;
    memset(message,BLANK_CHAR,sizeof(message));
    wiringPiSetup();
    fd = wiringPiI2CSetup(I2C_ADDR);
    lcd_write_instruction(TWO_LINE_MODE) ;
    lcd_write_instruction(CLR_SCREEN) ;
    lcd_write_instruction(DISPLAY_ON_CURSOR_ON) ;
    printf("Please enter :   ") ;
    fgets(message, 17 , stdin);
	printf("Message = %s \n" ,message);
    lcd_write_string(message);

   int new_position = jump(2,2);
    
    if (new_position == 0xFF )
    {
        return 1;
     }
    else 
    {
        lcd_write_instruction(new_position);
        strncpy(message, "in WiringPi ", 17);
        lcd_write_string(message);
    }
      
    return 0;
	
}

void lcd_write_instruction(int inst)
{
	wiringPiI2CWriteReg8( fd, INSTRUCTION, inst) ;
	delay(delay10);
}
	
	
void lcd_write_character(int character)
{
	wiringPiI2CWriteReg8( fd, CHAR, character) ;
	delay(delay10);
}


void lcd_write_string(char str_list[17])
{
	int ii =  0;
	int iline1 [17] ;
	int numaa ;
	
	delay(delay10);
	for ( ii=0;  ii<17 ; ii++)
		{
			iline1[ii] = str_list[ii];//cast char to int (ASCII code)
			numaa= iline1[ii];
			
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
        //print("invalid line");
        lcd_write_instruction(CLR_SCREEN);
        strncpy(message, "invalid line", 17);
        lcd_write_string(message);
        return 0xFF ;
    }
}
	
	

