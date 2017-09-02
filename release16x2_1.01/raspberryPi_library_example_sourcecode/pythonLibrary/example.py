import wi2c16x2lcd
#define main program
def main():

    wi2c16x2lcd.lcd_init() #initializ lcd
    wi2c16x2lcd.clr_line(1)#clear line 1
    wi2c16x2lcd.clr_line(2) #clear line 2
    wi2c16x2lcd.wlcd(1,1,list("i2c interface"))#write to lcd from line 1, position 1
    wi2c16x2lcd.wlcd(2,2,list("address = "))#write to lcd from line 2, position 2
    w_integer = hex(wi2c16x2lcd.I2C_ADDR)# get i2c address of lcd, cast to hex
    w_char = list(str(w_integer))#cast integer to string and then list
    wi2c16x2lcd.wlcd(2,12,w_char)#write to lcd from line 2, position 12
    
    return 0       


#execute main program 
main()
