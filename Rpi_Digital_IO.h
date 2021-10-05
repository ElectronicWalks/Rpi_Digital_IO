/*--------------------------------------------------------------------------/
All right reserved with Gauranga Softtech pvt Ltd.
Copyrights 2018-2019

TimeStamp           : 180712_1500
Project             : Lab ZERO
Platform            : Raspberry Pi 3
Operating System    : Linux Raspbian
Compiler            : GCC
Editor              : Kate
File                : I2C_Driver.c
Despcription        : Its a generic SPI driver file 
Coded By            : Kamil H Shaikh
----------------------------------------------------------------------------*/
//----------------------------Inclusion of Files-----------------------------//

#ifndef RPI4_DIGITAL_IO_H
#define RPI4_DIGITAL_IO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/stat.h>
#include <sys/types.h>
//#include <fcntl.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "GenericTypeDefs.h"
#include <string.h>

//----------------------------Typedefs & Macros-----------------------------//
#define sGPIO "/sys/class/gpio/gpio"
#define sDIR "/direction"
#define sLOGIC "/value"

//Used for Export (Enable) or Import(Disable)
#define PIN_ENB 1
#define PIN_DIS 0

//Used for Pin Direction
#define IN  0
#define OUT 1
 
//Used for Pin Logic
#define LOW  0
#define HIGH 1

/*
//#define PLATFORM_BCM2711_CM4 1 ,Enable this is module in 
 

#ifdef PLATFORM_BCM2711_CM4   
    
//Pin Map By KHZ 210825_1256
  
    
#define PIN_24    "26"     //GPIO No.26
#define PIN_25    "21"     //GPIO No.21
#define PIN_26    "19"     //GPIO No.19

#define PIN_27    "20"     //GPIO No.20     
#define PIN_28    "13"     //GPIO No.13
#define PIN_29    "16"     //GPIO No.16

#define PIN_30    "6"     //GPIO No.06
#define PIN_31    "12"    //GPIO No.12
#define PIN_34    "5"     //GPIO No.05

#define PIN_37    "7"     //GPIO No.07
#define PIN_38    "11"     //GPIO No.11
#define PIN_39    "8"     //GPIO No.9

#define PIN_40    "9"     //GPIO No.9
#define PIN_41    "25"     //GPIO No.25
#define PIN_44    "10"     //GPIO No.10

#define PIN_45    "24"     //GPIO No.24
#define PIN_46    "22"     //GPIO No.22
#define PIN_47    "23"     //GPIO No.23

#define PIN_48    "27"     //GPIO No.27
#define PIN_49    "18"     //GPIO No.18
#define PIN_50    "17"     //GPIO No.17

#define PIN_51    "15"     //GPIO No.15
#define PIN_54    "4"     //GPIO No.4
#define PIN_55    "14"     //GPIO No.14

#define PIN_56    "3"     //GPIO No.3
#define PIN_58    "2"     //GPIO No.2

#define PinMODE_OP  "out"
#define PinMODE_IP  "in"
    
#end if  */
//----------------------------Declaration of Variables------------------------//
extern UINT8 PUMPStatus;
extern UINT32 AirPump_ON_tickCount;
extern UINT32 AirPump_OF_tickCount;
//----------------------------Declaration of Functions------------------------//
void  Init_Digi_Pin(UINT8 enflag,UINT8 PinNo,UINT8 PinMode);
void  Rpi_Write_Digi_Pin(UINT8 PinNo,UINT8 pinLogic);
UINT8 Rpi_Read_Digi_Pin(UINT8 PinNo);



#ifdef __cplusplus
}
#endif

#endif /* RPI4_DIGITAL_IO_H */

