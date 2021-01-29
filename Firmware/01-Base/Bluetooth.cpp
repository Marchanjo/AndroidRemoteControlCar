
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

#include "Bluetooth.h"




Bluetooth::Bluetooth() {}

Bluetooth::~Bluetooth(void) {}

void Bluetooth::onSetup(void)
  {
  //Serial1.begin(115200);//tem que ser a velocidade certa, Serial1 = leonardo
  //while (!Serial1);//necessario para Leonardo / necessary for Leonardo
  Serial1.begin(115200);
  Serial1.flush();

  timer = millis();
  holdFunctionBT = false;
  last_sequence=255;//como o celular começa a sequencia com 0, last_sequence é inicializado com 255 para evitar um erro no primeiro pacote  
  }


void Bluetooth::onLoop(void)
  {
  dataValidation();
  }

//Byte 0 caracter de start
//Byte 1 Byte mais significativo do X PWM
//Byte 2 Byte menos significativo do X PWM
//Byte 3 Byte mais significativo do Y PWM
//Byte 4 Byte menos significativo do Y PWM
//Byte 5 Byte mais significativo do flag_register- sempre 
//Byte 6 Byte menos significativo do flag_register
//Byte 7 Sequencial do pacote
//Byte 8 Checksum
//inputSpeed e inputDir variam de -255 a 255
bool Bluetooth::dataValidation(void)
  {
  int inputSpeed = CENTER;//0(min neg) - 2047(center) - 4095(max pos)
  int inputDir = CENTER;  //0(min neg) - 2047(center) - 4095(max pos)
  byte mode = ANALOG_MODE;//Default
  int functionAction;

  // Proteção de desconexão
  // Caso não tenha sido recebido um pacote válido durante WAIT_TIME milisegundos,
  // tanto as saídas do modo digital e analógico do joystick são devolvidas à
  // posição inicial (ponto morto)
  if((millis() - timer) > WAIT_TIME){
    motor.setMotors(CENTER,CENTER,ANALOG_MODE);
  }
  
  
  Serial1.flush();
  if (Serial1.available() < 1)  return false;
    
  data[0]=Serial1.read();
  if(DebugMode==2) Serial.println(String("cmd=")+data[0]);
    
  if (data[0] != START_CMD_CHAR) return false;

  
  return_code = Serial1.readBytes(&data[1], PACKET_DATA_SIZE-1);//Sem contar o primeiro byte, já lido, carrega os 8 restantes
  if(DebugMode==2) Serial.println(String("return=")+return_code);
   
  if(return_code==PACKET_DATA_SIZE-1) //Sem contar o primeiro byte, são 8 restantes
    {
    if(DebugMode==2)  {for(int i=0;i<PACKET_DATA_SIZE;i++)  Serial.println(String("data")+i+String("=")+data[i]);}
    
    if(data[PACKET_DATA_SIZE-2]!=last_sequence) {if(DebugMode==1) Serial.println("Sequence OK!");}
    else{
      if(DebugMode==1) Serial.println("Sequence Error ! &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&");
      motor.setMotors(CENTER,CENTER,ANALOG_MODE);///mantém motores parados
      return false;
      }
    last_sequence=data[PACKET_DATA_SIZE-2];
    
    //checksum
    checksum = 0;
    for (int i=1; i<PACKET_DATA_SIZE-1; i++)  checksum+=data[i];//no Checksum o data[0]='*' não entra 
       
    if(DebugMode==2) Serial.println(String("checksum enviado=")+data[PACKET_DATA_SIZE-1]+ String("checksum calculado=")+checksum);
    if(data[PACKET_DATA_SIZE-1]==checksum) {if(DebugMode==1) Serial.println("Checksum OK!");}
    else{
      if(DebugMode==1) Serial.println("Checksum - Packet Fail! *************************************");
      motor.setMotors(CENTER,CENTER,ANALOG_MODE);//mantém motores parados
      return false;
    }

    //inputSpeed    0(min neg) - 2047(center) - 4095(max pos)
    //inputDir      0(min neg) - 2047(center) - 4095(max pos)
    
    x = CENTER;
    y = CENTER;
    flag_register = 0;
    
    timer = millis(); // Usado na Proteção de desconexão
    x = data[1] << 8;//inputDir mais significativo
    x += data[2];//inputDir menos significativo
    y = data[3] << 8;//inputSpeed mais significativo
    y += data[4];//inputSpeed menos significativo
    flag_register = data[5] << 8;//flag_register byte mais significativo 
    flag_register += data[6];//flag_register byte menos significativo  


    //inputSpeed    0(min neg) 2047(center) 4095(max pos)
    //inputDir      0(min neg) 2047(center) 4095(max pos)
    //mode          0 Analog, 1 Digital
    inputSpeed = y;
    inputDir = x;
    mode = flag_register & 0x01;

    //inicio: Funciona como a App do ControleM, comentar com App final
    if(DebugMode==1) Serial.println(String("X: ") + x  + String(" inputDir: ") + inputDir + String("\n") + String("Y: ") + y + String(" inputinputSpeed: ") + inputSpeed  + String("\n") +  String("flag_register: ")  + flag_register + String(" MODE: ") + mode);
    motor.setMotors(inputSpeed,inputDir, mode);//única condição que gera movimento
    return true;
    }
  motor.setMotors(CENTER,CENTER,ANALOG_MODE);//mantém motores parados
  return false;
  }
