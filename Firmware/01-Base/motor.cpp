/*
 * =====================================================================================
 *
 *      Filename:  motor.cpp
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

 #include "motor.h"

Motor::Motor() {}
Motor::~Motor(void) {}

void Motor::onSetup(void){   
  //configura timers para frequência inaudível 31,3KHz - sets timers for inaudible frequency 31,3KHz
  TCCR1A = 0xA9;
  TCCR3A = 0xA9;
  TCCR4A = 0x53;

  TCCR1B = 1;
  TCCR3B = 1;
  TCCR4B = 1;

  TCCR4C = 0xAB;

  pinMode(pinMotorLfwd, OUTPUT);
  pinMode(pinMotorLbwd, OUTPUT);
  pinMode(pinMotorLEnableL298, OUTPUT);
  
  pinMode(pinMotorRfwd, OUTPUT);
  pinMode(pinMotorRbwd, OUTPUT);
  pinMode(pinMotorREnableL298, OUTPUT);
  
  

  motorLfwd = 0;
  motorLbwd = 0;
  digitalWrite(pinMotorLEnableL298, HIGH);

  motorRfwd = 0;
  motorRbwd = 0;
  digitalWrite(pinMotorREnableL298, HIGH);

  //Softresponse
  lastMotorL = 0;
  lastMotorR = 0;
  lastLoopTime = millis();  
  

  //O TX LED não pode ser acessado normalmente por um pino, por isso uma macro é necessária, usei macro para o RX LED (pin 17) só por padrão
  //TX LED is not tied to a normally controlled pin so a macro is needed, RX LED (pin 17) macro was used just for standard.
  
  }

void Motor::onLoop(){
  
}

void Motor::setMotors(int inputSpeed, int inputDir, byte mode){
   float motorL,motorR;

  //Valores recebidos do joystick virtual da App Android
  //inputSpeed    0(min neg) 2047(center) 4095(max pos)
  //inputDir      0(min neg) 2047(center) 4095(max pos)
  //mode          0 Analog, 1 Digital

  if(DebugMode==3) Serial.println(String("Motors\ninputDir: ") + inputDir + String("\ninputinputSpeed: ") + inputSpeed   +  String("\nMODE: ") + mode);

  //Centraliza os valores 
  inputSpeed-=2047;//-2047(min neg)  0(center)  2048(max pos) 
  inputDir-=2047;  //-2047(min neg)  0(center)  2048(max pos)

  //deixa os valores simétricos
  if(inputSpeed==2048) inputSpeed=2047; //-2047(min neg)  0(center)  2047(max pos)
  if(inputDir==2048) inputDir=2047;//-2047(min neg)  0(center)  2047(max pos)
  
  if(DebugMode==4) Serial.println(String("Motors\ninputDir: ") + inputDir + String("\ninputinputSpeed: ") + inputSpeed   +  String("\nMODE: ") + mode);

  //Equaciona velocidade e direção em sinal para cada motor
  motorL=(inputSpeed+inputDir);//pode ficar maior que 2047 e menor que -2047, mas não importa poderá ser cortado em 2047
  motorR=(inputSpeed-inputDir);//pode ficar maior que 2047 e menor que -2047, mas não importa poderá ser cortado em 2047

  if(DebugMode==5) Serial.println(String("Motors Base\nmotorL: ") + motorL + String("\nmotorR: ") + motorR   +  String("\nMODE: ") + mode);

  //recebe valores na escala //-2047(min neg) -JOYSTICK_DEAD_ZONE 0(center) JOYSTICK_DEAD_ZONE 2047(max pos)
  //devolve //-255 -MINIMAL_PWM 0(center)MINIMAL_PWM 255
  motorL=escaleAdjust(motorL);
  motorR=escaleAdjust(motorR);

  if(DebugMode==2) Serial.println(String("Motors Adjs\nmotorL: ") + motorL + String("\nmotorR: ") + motorR   +  String("\nMODE: ") + mode);

  
  motorL=softResponse(255,500,lastMotorL,lastLoopTime,motorL);
  motorR=softResponse(255,500,lastMotorR,lastLoopTime,motorR);
  if(DebugMode==6) Serial.println(String("Motors Soft\nmotorL: ") + String(" motor1=")+motorL+String(" motor2=")+motorR);

  //PWM nos motores
  if(motorL > 0){
      if(DebugMode==7) {Serial.print(" MLF=");Serial.print((unsigned char)motorL);}
      motorLfwd=(unsigned char)motorL;//tem que usar o type cast (unsigned char),pois (byte) não funciona
      motorLbwd=0;
      TXLED1;
      }
  if(motorL < 0){
      if(DebugMode==7) {Serial.print(" MLB=");Serial.print((unsigned char)-motorL);} 
      motorLfwd=0;
      motorLbwd=(unsigned char)-motorL;//tem que usar o type cast (unsigned char),pois (byte) não funciona
      TXLED1;
      }
  if(motorL == 0){//parado 
      motorLfwd=0;
      motorLbwd=0;
      if(DebugMode==7) Serial.print(" ML=0 ");
      TXLED0;
      }
      
  if(motorR > 0){
      if(DebugMode==7) {Serial.print(" MRF=");Serial.print((unsigned char)motorR);}
      motorRfwd=(unsigned char)motorR;//tem que usar o type cast (unsigned char),pois (byte) não funciona
      motorRbwd=0;
      RXLED1;
      }
  if(motorR < 0){
      if(DebugMode==7) {Serial.print(" MRB=");Serial.print((unsigned char)-motorR);} 
      motorRfwd=0;
      motorRbwd=(unsigned char)-motorR;//tem que usar o type cast (unsigned char),pois (byte) não funciona
      RXLED1;
      }
   if(motorR == 0){//parado
      motorRfwd=0;
      motorRbwd=0;
      if(DebugMode==7) Serial.print(" MR=0 ");
      RXLED0;
      }
    //continuação do softresponse
    lastMotorL=motorL;
    lastMotorR=motorR;
    lastLoopTime = millis();
    if(DebugMode==8) Serial.println(String(" motorL=")+motorL+String(" motorR=")+motorR);
    //fim do softresponse
  }
  
//recebe valores na escala //-2047(min neg) -JOYSTICK_DEAD_ZONE 0(center) JOYSTICK_DEAD_ZONE 2047(max pos)
//devolve //-255 -MINIMAL_PWM 0(center)MINIMAL_PWM 255
float Motor::escaleAdjust(float motorSignal) {
  float toReturn;
  if(motorSignal>0){
      if(motorSignal>2047) motorSignal=2047; //limita antes do map 
      if(motorSignal>JOYSTICK_DEAD_ZONE)  toReturn=map(motorSignal,JOYSTICK_DEAD_ZONE,2047,MINIMAL_PWM,255);
      else toReturn=0;     
      if(toReturn>255) toReturn=255;//limita depois do map
      }
  if(motorSignal<0){
      if(motorSignal<-2047)motorSignal=-2047;//limita antes do map
      if(motorSignal<-JOYSTICK_DEAD_ZONE)  toReturn=map(motorSignal,-JOYSTICK_DEAD_ZONE,-2047,-MINIMAL_PWM,-255);  
      else toReturn=0;
      if(toReturn<-255) toReturn=-255;//limita depois do map
        }
  if(motorSignal==0)toReturn=0;
  
 return toReturn;
 }

//valueRate e timeRate indicam a razão de evolucão do numero
//softResponse valueRate/timeRate equivale Ã  velocidade, timeRate indica também o tempo em que o valor atingiria o valueTarget partindo do zero
//lastValue e lastTime são o valor e o momento que o valor foi obtido no loop anterior
//valueTarget é a meta que o valor irá ter passado o tempo
//ESTE METODO TAMBEM EH USADO PARA SUAVIZAR O PENTA
float Motor::softResponse(float valueRate, int timeRate,float lastValue, unsigned long lastTime,float valueTarget)//modificada para que valueRate seja float
  {
  float currentValue;
  unsigned long currentTime=millis();
  float rate=(float)valueRate/(float)timeRate;
  
  if((currentTime-lastTime)>timeRate) return valueTarget;
  
  if(lastValue==valueTarget) return valueTarget;
  
  if(lastValue<valueTarget)//sentido positivo
    {
    currentValue=lastValue+((float)(currentTime-lastTime)*rate);
    if(currentValue>valueTarget) return valueTarget;
    }
  else//sentido negativo
    {
    currentValue=lastValue-((float)(currentTime-lastTime)*rate);
    if(currentValue<valueTarget) return valueTarget;
    }
  
  return currentValue; 
  }
  
