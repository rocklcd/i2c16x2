
#include <wi2c16x2lcd.h>

int main(int argc, char **argv)
{
	
	lcd_init();//initialize lcd
	clr_line(1);//clear line 1
	clr_line(2);//clear line 2
	wlcd(1 , 1 ,"I2C interface");//write to lcd from line1 postion1
	wlcd(2 , 2 , "Address = 0x");//write to lcd from line2 position2
	int w_Integer = I2C_ADDR ;//I2C address from wi2c16x2lcd.h
	char w_Character[] = "" ;
	sprintf(w_Character, "%x" ,w_Integer );//cast integer to char
	wlcd(2, 14,w_Character );//write to lcd from line2 position14
	return 0;
}

