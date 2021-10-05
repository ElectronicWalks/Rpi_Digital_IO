/*--------------------------------------------------------------------------/
All right reserved with Gauranga Softtech pvt Ltd.
Copyrights 2018-2019

TimeStamp           : 210619_1340
Project             : LabHealth_2.90
Platform            : Raspberry Pi 4(CM4)
Operating System    : Linux Raspbian
Compiler            : GCC
Editor              : Netbeans 8.2
File                : Rpi4_Digital_IO.c
Despcription        : Its a Digital IO driver for Rpi4 CM4 
Driver Made By      : Kamil H Shaikh
----------------------------------------------------------------------------*/
//----------------------------Inclusion of Files-----------------------------//
#include "Rpi_Digital_IO.h"


//-------Start:Init_I2C----------------------------------------------//

/*Core Functions User must Avoid using these functions*/
int GPIOExport(int pin);
int GPIOUnexport(int pin);
int GPIODirection(char *pinStr, int dir);
int GPIOWrite(char *valStr, int value);
int GPIORead(char *valStr);
/*Core Functions User must Avoid using these functions*/


/*------------------------------------------------------------------------------
 Function Name  :Init_Digi_Pin
 Argument       :Enable/Disable,GPIO number,Out/In
 Return type    :void
 Description    :its called once to initialize the SPI channel
 eg for using   :Init_Digi_Pin(PIN_ENB,19,OUT); 19 is GPIO number
----------------------------------------------------------------------------- */
//
void Init_Digi_Pin(UINT8 enflag,UINT8 PinNo,UINT8 PinMode){
//Step 0:Defining  Macros 
#define PRINT_PIN 1

 //Step 1: Declaration of Variables
char PrintBuff[100];
memset(PrintBuff,0,sizeof(PrintBuff));   
char sPinNo[4];
memset(sPinNo,0,sizeof(sPinNo));  
//Step 2: Enable or Disable GPIO
    if(enflag==PIN_ENB){
        if (-1 == GPIOExport(PinNo)){
            printf("Pin %i EXPORT(Enable) error: %s\n",PinNo, strerror(errno) );
        }else{
            #ifdef PRINT_PIN
                printf("GPIO %i Enabled\n",PinNo);
            #endif
        }
    }else if(enflag==PIN_DIS){
        if(-1== GPIOUnexport(PinNo)){
            printf("Pin %i UN-EXPORT(Disable) error: %s\n",PinNo, strerror(errno) );
        }else{
            #ifdef PRINT_PIN
                printf("GPIO %i Disabled\n",PinNo);
            #endif
        }
    
    }
    
//Step 2: Make String for Pin Direction or Mode ie Output or Input
    sprintf(sPinNo,"%i",PinNo);
    strcpy(PrintBuff,(char*)sGPIO);
    strcat(PrintBuff,sPinNo);
    strcat(PrintBuff,sDIR);

    if( -1 == GPIODirection(PrintBuff,PinMode)){
        printf("GPIO %i Dir = %i error: %s\n",PinNo,PinMode,strerror(errno) );
    }

}
/*------------------------------------------------------------------------------
 Function Name  :Rpi_Write_Digi_Pin
 Argument       :GPIO number,Pin Logic
 Return type    :void
 Description    :API made for simple user interface
 eg for using   :Rpi_Write_Digi_Pin(19,LOW);
----------------------------------------------------------------------------- */
void Rpi_Write_Digi_Pin(UINT8 PinNo,UINT8 pinLogic){
//Step 0:Defining  Macros 

 //Step 1: Declaration of Variables
    char PrintBuff[100];
    memset(PrintBuff,0,sizeof(PrintBuff));   
    char sPinNo[4];
    memset(sPinNo,0,sizeof(sPinNo));  

//Step 2: Make String for Pin Direction or Mode ie Output or Input 
    sprintf(sPinNo,"%i",PinNo);
    strcpy(PrintBuff,(char*)sGPIO);
    strcat(PrintBuff,sPinNo);
    strcat(PrintBuff,sLOGIC);

//Step 3:Write Value on GPIO pin defined by file path
    if( -1 == GPIOWrite(PrintBuff,pinLogic)){
        printf("GPIO %i value  write error: %s\n",PinNo,strerror(errno));
    }
}
/*------------------------------------------------------------------------------
 Function Name  :Rpi_Read_Digi_Pin
 Argument       :GPIO number,Pin Logic
 Return type    :Logic State
 Description    :API made for simple user interface
 eg for using   : UINT8 pin = Rpi_Read_Digi_Pin(19);//where 19 is GPIO number
----------------------------------------------------------------------------- */
UINT8 Rpi_Read_Digi_Pin(UINT8 PinNo){
//Step 0:Defining  Macros 

 //Step 1: Declaration of Variables
    UINT8 PinVal = -1;
    char PrintBuff[100];
    memset(PrintBuff,0,sizeof(PrintBuff));   
    char sPinNo[4];
    memset(sPinNo,0,sizeof(sPinNo));  

//Step 2: Make String for Pin Direction or Mode ie Output or Input 
    sprintf(sPinNo,"%i",PinNo);
    strcpy(PrintBuff,(char*)sGPIO);
    strcat(PrintBuff,sPinNo);
    strcat(PrintBuff,sLOGIC);
    
//Step 3:Read pin Value on GPIO  defined by file path
    PinVal = GPIORead(PrintBuff);
    
    return(PinVal);
}




/*
INT32 AIR_pump_Signal(UINT8 Logic){
    
   INT32 Status=0;
   if(PUMPStatus!=Logic){
       Status = GPIOWrite((char*)SUCTN_AIRPMP_FP, Logic);
        if( -1==Status){
             printf("AIR PUMP PIN write error %s\n",strerror(errno));
        }
       PUMPStatus = Logic;
   }
   
    return(Status);
}
*/
/*
void Periodic_AirPump_ON_OF(void){
    
#define PMP_ON_Time 5000  //05 secs
#define PMP_OF_Time 30000  //30 secs
    
    UINT32 u32CurrTick = 0;
    u32CurrTick = getTick();
    
    if(u32CurrTick - AirPump_ON_tickCount<PMP_ON_Time){
        AIR_pump_Signal(PMP_ON);
        printf("Time:%i,ON\n",u32CurrTick);
        AirPump_OF_tickCount = u32CurrTick;
        
    }else{        
        if(u32CurrTick-AirPump_OF_tickCount<PMP_OF_Time){
            AIR_pump_Signal(PMP_OF);
            printf("Time:%i,OFF\n",u32CurrTick);
        }else{
            AirPump_ON_tickCount = u32CurrTick;
        }
    }    
}*/
//-------------------------------------------------------------------------------------------------------

 //--------------------Declaration of Functions--------------------------------// 
/*-----------------------------------------------------------------------------
 * Function Name : GPIOExport
 * Argument      : UINT as pin no
 * Return Type   : -1 means failed
 * Periodicity   : Once         
 * Type          : Core Function API
 * Description   : Used to Enable pin 
 ----------------------------------------------------------------------------*/
//--***Start:GPIOExport***---//
int GPIOExport(int pin){
#define BUFFER_MAX 3
	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;
 
	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (-1 == fd) {
		printf("Failed to open export for writing!\n");
		return(-1);
	}
 
	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
}
 //--***Stop:GPIOExport***---//
/*-----------------------------------------------------------------------------
 * Function Name : GPIOUnexport
 * Argument      : UINT as pin no
 * Return Type   : -1 means failed
 * Periodicity   : Once          
 * Type          : Core Function API
 * Description   : Used to Disable pin 
 ----------------------------------------------------------------------------*/
//--***Start:GPIOUnexport***---//
int GPIOUnexport(int pin){
	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;
 
	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	if (-1 == fd) {
		printf("Failed to open unexport for writing!\n");
		return(-1);
	}
 
	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
}
 //--***Stop:GPIOUnexport***---//
/*-----------------------------------------------------------------------------
 * Function Name : GPIODirection
 * Argument      : UINT as pin no
 * Return Type   : -1 means failed
 * Periodicity   : Once          
 * Type          : Core Function API
 * Description   : Used to Set Direction mode of pin as Input(0) or Output(1)
 ----------------------------------------------------------------------------*/
//--***Start:GPIODirection***---//
int GPIODirection(char *pinStr, int dir){
    
	static const char s_directions_str[]  = "in\0out";
 
#define DIRECTION_MAX 40
	char path[DIRECTION_MAX];
	int fd;
 
//	snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
	snprintf(path, DIRECTION_MAX, pinStr);
	printf("%s\n",path);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		printf("Failed to open gpio direction for writing!\n");
		return(-1);
	}
 
	if (-1 == write(fd, &s_directions_str[IN == dir ? 0 : 3], IN == dir ? 2 : 3)) {
		printf("Failed to set direction!\n");
		close(fd);
		return(-1);
	}
 
	close(fd);
	return(0);
}
//--***Stop:GPIODirection***---// 
/*-----------------------------------------------------------------------------
 * Function Name : GPIORead
 * Argument      : File path of pin
 * Return Type   : -1 means failed
 * Periodicity   : can be called Multiple times        
 * Type          : Core Function API
 * Description   : Used to Read pin logic 
 ----------------------------------------------------------------------------*/
int GPIORead(char *valStr){
    
#define VALUE_MAX 40
	char path[VALUE_MAX];
	char value_str[3];
	int fd;

        
	snprintf(path, VALUE_MAX, valStr);
	fd = open(path, O_RDONLY);
	if (-1 == fd) {
		printf("Failed to open gpio value for reading!\n");
		return(-1);
	}
 
	if (-1 == read(fd, value_str, 3)) {
		printf("Failed to read value!\n");
		close(fd);
		return(-1);
	}
 
	close(fd);
 
	return(atoi(value_str));
}
/*-----------------------------------------------------------------------------
 * Function Name : GPIOWrite
 * Argument      : File path of pin
 * Return Type   : -1 means failed
 * Periodicity   : can be called Multiple times        
 * Type          : Core Function API
 * Description   : Used to Write pin logic 
 ----------------------------------------------------------------------------*/ 
int GPIOWrite(char *valStr, int value){
    
	static const char s_values_str[] = "01";
 
	char path[VALUE_MAX];
	int fd;
 
	snprintf(path, VALUE_MAX, valStr);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		printf("Failed to open gpio value for writing!\n");
		return(-1);
	}
 
	if (1 != write(fd, &s_values_str[LOW == value ? 0 : 1], 1)) {
		printf("Failed to write value!\n");
		close(fd);		//SDK 6th Dec : Safety precaution for ""Too many files open" error.
		return(-1);
	}
 
	close(fd);
	return(0);
}




#if 0
int
main_test(int argc, char *argv[])
{
	int repeat = 1;
 
	/*
	 * Enable GPIO pins
	 */
	if (-1 == GPIOExport(POUT1) || -1 == GPIOExport(POUT2) || -1 == GPIOExport(POUT3) || -1 == GPIOExport(POUT4))
		return(1);
 
	if (-1 == GPIODirection("/sys/class/gpio/gpio74_pe4/direction", OUT)) 
		return(2);

	sleep(2);
	/*
	 * Set GPIO directions
	 */
	if (-1 == GPIODirection("/sys/class/gpio/gpio74_pe4/direction", OUT)) 
		return(2);
 
		/*
		 * Write GPIO value
		 */
		if (-1 == GPIOWrite("/sys/class/gpio/gpio74_pe4/value", 1))
			return(3);
 
		//if (-1 == GPIOWrite(POUT2, repeat % 2))
		//	return(3);


	//	if (-1 == GPIOWrite(POUT3, repeat % 2))
	//		return(3);
 
	//	if (-1 == GPIOWrite(POUT4, repeat % 2))
	//		return(3);

			/*
		 * Read GPIO value - DISABLED
		 */
 
		sleep(5);

		GPIOWrite("/sys/class/gpio/gpio74_pe4/value", 0);
		
		sleep(5);
 
	/*
	 * Disable GPIO pins
	 */
	if (-1 == GPIOUnexport(POUT1) || -1 == GPIOUnexport(POUT2))
		return(4);
 
	return(0);
}

#endif
