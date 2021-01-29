 /*
 * =====================================================================================
 *
 *      Filename:  base.ino
 *
 *      Description:  main file
 *
 *      Version:  0.1
 *      Created:  25/05/2020
 *      Revision:  none
 *      Compiler:  Arduino IDE 1.8.12
 *
 *      Author:  Marcelo Archanjo, marcelo_archanjo@yahoo.com.br
 *      Company: None
 *
 * =====================================================================================
 */

/* Bibliotecas do projeto - Project Libraries */
#include "base.h"
#include "Bluetooth.h"
#include "motor.h"

//Objetos - Objects
Motor motor;
Bluetooth bluetooth;

//Variáveis Globais - Globals variables
//boolean motor1 = false, motor2 = false;
//int inputSpeed = 2047;//0(min neg) - 2047(center) - 4095(max pos)
//int inputDir = 2047;  //0(min neg) - 2047(center) - 4095(max pos)
//byte mode = ANALOG_MODE;//Default


void setup() { 
  if(DebugMode!=0) Serial.begin(115200);
  bluetooth.onSetup();
  motor.onSetup();  
}

void loop() {
  bluetooth.onLoop();
  motor.onLoop();  
}
