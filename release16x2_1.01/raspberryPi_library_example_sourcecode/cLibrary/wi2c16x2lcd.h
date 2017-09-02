//File wi2c16x2lcd.h
#ifndef WI2C16X2LCD_H
#define WI2C16X2LCD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
#endif
