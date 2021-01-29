/*
 * =====================================================================================
 *
 *      Filename:  motor.h
 *
 *      Description:  Classe Motor - Motor Class
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
#ifndef MOTOR_H_
#define MOTOR_H_

#include <Arduino.h>
#include "base.h"

 
class Motor{
   public:
      Motor(void);
      virtual ~Motor(void);
      void onSetup(void); 
      void onLoop(void);
      void setMotors(int inputSpeed, int inputDir, byte mode);
      
   private:      
      float escaleAdjust(float motorSignal);
      float softResponse(float valueRate, int timeRate,float lastValue, unsigned long lastTime,float valueTarget);
      float lastMotorL, lastMotorR;
      unsigned long lastLoopTime;
};
      
#endif 
