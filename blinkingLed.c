//#include <wiringPi.h>
#include <stdio.h>
#include "Rpi_Digital_IO.h"
#include <unistd.h>
#define LedPin 19

char Pin13Flag=0;
int main(){

  Init_Digi_Pin(PIN_ENB,19,OUT);
  Init_Digi_Pin(PIN_ENB,13,IN);
  
  Rpi_Write_Digi_Pin(19,HIGH);
  
  while(1){
    Pin13Flag = Rpi_Read_Digi_Pin(13);
    if(Pin13Flag==0){
      printf("Fault Occurred\n");     
    }else{
      printf("No Fault\n");
    }
    sleep(1);
  }
  
  return(0);
}
