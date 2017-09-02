FIRST NEED TO INSTALL smbus LIBRARY 

 sudo apt-get update
 sudo apt-get install python-smbus
 (for python3 raspbian version later than 4.1.6)
 (check version) uname -a
 sudo apt-get install python3-smbus



SECOND TO INSTALL wi2c16x2lcd LIBRARY FOR PHYTHON

cd dist/
cd wi2c16x2lcd-0.1./
sudo pip install .
(for python 3)
sudo pip3 install .


FOR EARILER MODELS RATHER THAN PI3, THE I2C PORT MAY NEED TO SET TO 0

cd ./wi2c16x2lcd
(MODIFY THE FILE  __init__.py  )
(FIND THE LINE   s = SMBus(1) and then change 1 to 0 )
cd ../
sudo pip install .
(for python 3)
sudo pip3 install .


IN ORDER TO WORK PROPERLY
ENABLE THE I2C INTERFACE ON RASPBERRYPI

sudo raspi-config

(GO TO ADVANCE OPTIONS AND ENABLE  I2C)
(REBOOT THE SYSTEM)
