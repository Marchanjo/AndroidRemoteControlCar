
/*
 * =====================================================================================
 *
 *      Filename:  Bluetooth.h
 *
 *      Description:  Tratamento da comunicação Bluetooth 
 *      (Bluetooth communication)
 *
 *      Version:  0.1
 *      Created:  31/05/2020
 *      Revision:  none
 *      Compiler:  Arduino IDE 1.8.12
 *
 *      Author:  Marcelo Archanjo, marcelo_archanjo@yahoo.com.br
 *      Company: None
 *
 * =====================================================================================
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include <Arduino.h>
#include "base.h"
#include "motor.h"


extern Motor motor;

class Bluetooth {
   public:
      Bluetooth(void);
      virtual ~Bluetooth();
      void onSetup(void);
      void onLoop(void);

      int x, y, flag_register; 
      unsigned long timer;  
      
            
   private:
      bool dataValidation(void);

      boolean holdFunctionBT;//usado para que o incremento da função somente ocorra uma vez por movimento
      byte data[PACKET_DATA_SIZE];//Bit 0 caracter de start,Bit 1 sentido do PWM, Bit 2 PWM,Bit 3 Função (Actuator ou error)
      byte return_code;
      byte checksum = 0;
      byte last_sequence;// = 255;//como o celular começa a sequencia com 0, last_sequence é inicializado com 255 para evitar um erro no primeiro pacote
   };

#endif
