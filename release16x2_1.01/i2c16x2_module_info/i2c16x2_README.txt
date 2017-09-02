PCB size : 80mm X 36mm

Standard HD44780 command sets

PINOUT configuration

pin 1 : GND (ground)
pin 2 : VDD (+5V)
pin 3 : V0 (leave it open)
pin 4 : SDA (i2c data)
pin 5 : SCL (i2c clock)
pin 6 : A (leave it open)
pin 7 : K (leave it open)


Default I2C address : 0X3C (with sub address SA0 (R7) = L , SA1 (R8) = L)
Customized I2C sub address : desolder R7 or R8, change it to the corresponding values
(for example, if wish the address to be 
0X3D, R7 = H, R8 = L 
0X3E, R7 = L, R8 = H
0X3F, R7 = H, R8 = H )

Backlight(Yellow Green) : Default ON (if wish to be controlled by A, K pins, cut JA and JK on PCB)

Contrast control : remove R6, input voltage from V0


