
 #
 # I2C_example_smbus.py
 # 
 #
 # ***************************************************************************
 # This program is a free software. You can use/modify/distribute freely upon
 # agreeing the followings.
 #
 # DISCLAIMER:
 # NO WARRANTY or implied warranty of any kind. Any user who makes use 
 # of this software shall be solely responsible for any liability/direct
 # lose/indirect lose which may occur.
 #
 # ***************************************************************************
 #
 #
 # How to install smbus library on raspberrypi :
 # (Reference to )
 # http://www.linuxcircle.com/2015/05/03/how-to-install-smbus-i2c-module-for-python-3/
 # 1. sudo apt-get update
 # 2. sudo apt-get install python-smbus
 # 3. (for python3 raspbian version later than 4.1.6)
 #    (check version) uname -a
 #    sudo apt-get install python3-smbus
 # 4. sudo raspi-config
 # 5. "go to advance options and enable I2C"
 # 6. "reboot the system"
 # 

from smbus import SMBus
from time import sleep


#I2C control parameters
I2C_ADDR = 0x3C
INSTRUCTION = 0x00
CHAR = 0x40

#basic instructions
#(Can create your own according to HD44780 instruction sets)
TWO_LINE_MODE = 0x38
CLR_SCREEN = 0x01
RET_HOME = 0x02
DISPLAY_ON_CURSOR_OFF = 0x0C
DISPLAY_ON_CURSOR_ON = 0x0E
DISPLAY_OFF_CURSOR_OFF = 0x08
BLANK_CHAR = 0x20


#RaspberryPi 3 I2C port set to 1
#(May need to set to 0 on eariler models)
b = SMBus(1)



#send instruction to lcd
def lcd_write_instruction(inst):
    
    b.write_byte_data(I2C_ADDR, INSTRUCTION, inst)
    sleep(0.01)
    return



#dsiplay 1 character
#character is an integer from 0x00 to 0xFF
def lcd_write_character(character):
    
    b.write_byte_data(I2C_ADDR, CHAR, character)
    sleep(0.01)
    return



#display a string 
def lcd_write_string(str_list):
    
    length = len(str_list)
    
    for i in range(0, length ):
        lcd_write_character(ord(str_list[i]))#cast char to int(ASCII code)
        i = i+1
    return



#jump to a position within 2 lines x 16 characters range
def jump(line, position):
    
    if ((1 > position) or (position >16)) :
        #print("invalid position")
        lcd_write_instruction(CLR_SCREEN)
        lcd_write_string(list("invalid position"))
        return 0xFF
  
    if line == 1 :
        pos = 0x80 + position - 1
        return pos
    elif line == 2 :
        pos = 0xC0 + position - 1
        return pos
    else :
        #print("invalid line")
        lcd_write_instruction(CLR_SCREEN)
        lcd_write_string(list("invalid line"))
        return 0xFF
    return 0
   

#define lcd_init()
def lcd_init():
    lcd_write_instruction(TWO_LINE_MODE)
    lcd_write_instruction(CLR_SCREEN)
    lcd_write_instruction(DISPLAY_ON_CURSOR_OFF)
    return

#define clr_line
def clr_line(line_no) :
    lcd_write_instruction(jump(line_no ,1))
    for i in range(0,16) :
        lcd_write_character(BLANK_CHAR)
        i=i+1
    return

#define wlcd
def wlcd(ln,posi,str_list) :
	status = jump(ln ,posi)
	if(status !=0xFF) :
		lcd_write_instruction(status)
		lcd_write_string(str_list)
	return






    
