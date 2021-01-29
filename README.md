# AndroidRemoteControlCar
Just a simple arduino toy car controlled by Bluetooth using Android App

The Android App here is just the .APK.
The complete Android App project is available in  [ControleM](https://github.com/CITI-USP/ControleM)

*Mounting:*
![Mounting](https://github.com/Marchanjo/AndroidRemoteControlCar/blob/main/Hardware/01-Promicro-L298-HC05_bb.jpg)


HC05 Configuration
------------------

*FTDI - HC05:*
![FTDI - HC05](https://github.com/Marchanjo/AndroidRemoteControlCar/blob/main/Hardware/FTDI-HC05.jpg)

Connections:

FTDI 5v  - 5v BT

FTDI GND - GND BT

FTDI TX  - RX BT(My FTDI cable provide 3,3v logic) 

FTDI RX  - TX BT(My FTDI cable provide 3,3v logic) 



You need to hold the push button in HC05 while power-on (just during the power-on)


For my HC05 the default connection:

Baud rate: 38400

Data bits: 8

Parity: None

Stop bits: 1 bit

Some serial terminals need ASCII Setup:

Send line ends with line feeds

Echo typed characters locally



First Step: Return to original Configurations
---------------------------------------------

AT  

OK

AT+ORGL       

OK 

AT+RESET


Second Step: Configuration (name and Baud rate 115200)
------------------------------------------------------

Power-off and hold the push button in HC05 while power-on again.
Connect with 96000 Baud rate (my HC05 change to this)

My HC05 configuration:

AT+VERSION

VERSION:3.0-20170601

OK

AT+ADDR

+ADDR:21:13:3CDE1

OK

AT+NAME

+NAME:H-C-2010-06-01

OK

AT+UART

+UART:9600,0,0

OK

AT+UART=115200,0,0

AT+NAME=MagicBot01


AT+VERSION

VERSION:3.0-20170601

OK

AT+ADDR

+ADDR:21:13:3CDE1

OK

AT+NAME

+NAME:MagicBot01

OK

AT+UART

+UART:115200,0,0

OK

Final Pictures
--------------
*Front:*
![Front](https://github.com/Marchanjo/AndroidRemoteControlCar/blob/main/Hardware/front.jpg)

*Back:*
![Back](https://github.com/Marchanjo/AndroidRemoteControlCar/blob/main/Hardware/back.jpg)
