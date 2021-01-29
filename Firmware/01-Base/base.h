
/*
 * =====================================================================================
 *
 *      Filename:  base.h
 *
 *      Description:  lista de pinos , definições e variáveis estáticas 
 *      (physical pins enumeration, static variables and defines)
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

#ifndef BASE_H_
#define BASE_H_


#define DebugMode 0

//Controle Analogico ou Digital - Analog or Digital control
#define ANALOG_MODE 0
#define DIGITAL_MODE 1

#define JOYSTICK_DEAD_ZONE 5 //Pequena região central do joystick que é ignorada para evitar movimento involuntário 
#define MINIMAL_PWM 170 //PWM mínimo para que o motor gire

#define CENTER 2047 //posição de repouso no eixo X e Y recebido da App
#define WAIT_TIME 200


//ordem escolhida para facilitar a ligação da Pro Micro com a Breakout Board L298 - This sequence was chosen to make ease the Pro Micro and Breakout Board L298 connection
//                //Arduino pin (microcontroller pin)  
#define motorLfwd  OCR1B  //pin 10 (30) 
#define motorLbwd  OCR1A  //pin 9  (29)

#define motorRfwd  OCR4D  //pin 6  (27)                   
#define motorRbwd  OCR3A  //pin 5  (31)


//não tem na ProMicro / Not available in ProMicro:
//#define motor0fwd  OCR1C  //pin 11 (12)
//#define motor0bwd  OCR4A  //pin 13 (32)



//ordem escolhida para facilitar a ligação da Pro Micro com a Breakout Board L298 - This sequence was chosen to make ease the Pro Micro and Breakout Board L298 connection
#define pinMotorLEnableL298   8   //pin 8  (28) - PB4
#define pinMotorLfwd          10  //pin 10 (30) - PB6
#define pinMotorLbwd           9  //pin 9  (29) - PB5

#define pinMotorREnableL298    7  //pin 7   (1) - PE6 
#define pinMotorRfwd           6  //pin 6  (27) - PD7
#define pinMotorRbwd           5  //pin 5  (31) - PC6



//não tem na ProMicro / Not available in ProMicro:
//#define pinMotor0fwd  11 //pin 11 (12)
//#define pinMotor0bwd  13 //pin 13 (32)

//O TX LED não pode ser acessado normalmente por um pino, por isso uma macro é necessária, usei macro para o RX LED (pin 17) só por padrão
//TX LED is not tied to a normally controlled pin so a macro is needed, RX LED (pin 17) macro was used just for standard.

//Bluetooth
#define BLUETOOTH_WAIT_TIME 200

//comunicação Bluetooth
//
//Byte 0 caracter de start
//Byte 1 Não usado
//Byte 2 Não usado
//Byte 3 Byte mais significativo do PWM - inputSpeed
//Byte 4 Byte menos significativo do PWM - inputSpeed
//Byte 5 Byte mais significativo do flag_register- sempre 
//Byte 6 Byte menos significativo do flag_register
//Byte 7 Sequencial do pacote
//Byte 8 Checksum
//inputSpeed e inputDir variam de -255 a 255

#define START_CMD_CHAR '*'
#define PACKET_DATA_SIZE 9




#endif
