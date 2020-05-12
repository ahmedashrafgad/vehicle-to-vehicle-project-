#include <avr/io.h>
#include <assert.h>
#include <string.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include "softuart.h"
#include "usart.h"
#include "direction.h"
#include "ADC.h"
#include "usart_driver.h"
#include "Ultrasonic.h"
#include <math.h>
#define d1 deviceInfo[0].distance
#define d2 deviceInfo[1].distance
#define d3 deviceInfo[2].distance
#define d4 deviceInfo[3].distance
#define PI 3.14159265


//char buffer[50] ;
unsigned char receiveBuffer[300] ;
unsigned char lastChar='E';

struct DeviceInfo
{
	double rssi;
	long address;
	double distance;
};
struct CarsData
{
	int x ;
	int y ;
	int angle;
	int speed;
	long address;
};
struct CarsData Car_Data;

struct DeviceInfo deviceInfo[4] ; // general variable to init with null
struct DeviceInfo deviceSData[9] ; // general variable to init with null

void str_split(char* a_str, int x);
const int sizeOfBuffer = 300;
char buffer[300] ;
unsigned int deviceCounter = -1 ;
struct receivedDevices{
	char receivedData[50] ;
};

struct receivedDevices devices[9];

char printBuffer[50];
char* ptr ;

int c ;
double x = 0 , y = 0,theta = 0 ;
double x_room = 10 , y_room = 10;	//x and Y OF THE ROOM
void location(struct DeviceInfo deviceInfo[4]);

int main(void)
{
	
	deviceInfo[0].address = 12017048; //melos lab
	deviceInfo[1].address = 1937820;  //melos mob
	deviceInfo[2].address = 1156291   ; //sara mob
	deviceInfo[3].address = 316796    ; //shakeer lab
	
	ptr	 = devices[deviceCounter].receivedData ;
	unsigned int xValue  = 0, yValue = 0 ;
	_delay_ms(10000) ;
	memset(receiveBuffer,'\0',sizeOfBuffer);
	uart_init(9600) ;
	usart0_init(9600);
	sei();
	softuart_init();
	CarControlInit();
	
	softuart_puts_P( "\r\nStarting of application\r\n" );
	
	//str_split(str);
	uart_SendString("AT\r\n");
	uart_SendString("at+init\r\n") ;
	//test
	//uart_SendString("AT+CMODE=1\r\n") ;
	//uart_SendString("AT+ROLE=1\r\n") ;
	//
	uart_SendString("at+iac=9e8b33");
	uart_SendString("at+class=0\r\n");
	uart_SendString("at+inqm=1,9,48\r\n");
	_delay_ms(2000);
	ptr	= buffer ;
	while (1)
	{
			
		//fflush(buffer);
		clearReceivingBuffer();
		uart_SendString("At+inq\r\n");
		_delay_ms(10000);

		softuart_puts("in loop\n");
		softuart_puts(buffer);
		//split_Devices(buffer) ;
		char sss[300] ;
		strcpy(sss,buffer) ;
		split(sss);
	
	int j;
	for(j=0 ; j<4 ;j++)
	{
		deviceInfo[j].distance = pow(10.0, (76.5-deviceSData[j].rssi)/20.0)*100;
		printf("the rssi =%d\n",deviceInfo[j].distance);
	}
	location(deviceInfo);
		
		setDirection();
		_delay_ms(100);
		
		ptr = buffer ;
		softuart_puts("after init ptr\n");
	}
}

char start = 0 ;
ISR(USART_RX_vect)
{
	char r = UDR0 ;
	//test
	
	//softuart_putchar(r);
	if (r != 'O' && r != 'K')
	{
		*ptr = r ;
		ptr++;
	}
	else if(r != 'O')
	{
		deviceCounter =-1 ;
	}
	
	if (r == '+')
	{
		deviceCounter ++ ;
	}
	
}

void clearReceivingBuffer()
{
	int counter = 0 ;
	for (counter = 0 ; counter < sizeOfBuffer ; counter++)
	{
		buffer[counter] = "\0";
	}
}

void split(char* str)
{
	softuart_puts("string in split\n");
	softuart_puts(str);
	
	char strBuffer [300] ;
	strcpy(strBuffer,str);
	
	if(*str == NULL || *str == '\r'||*str =='\n')
	{
		softuart_puts("in return split\n");
		return;
	}
	

	char first[20] ,_[15],rssi[5],addressArray[7];
	char *token;
	token = strtok(str,"\r\n");
	{

		sscanf(token,"%[^,],%[^,],%[^,],%s",first,_,rssi);
		sscanf(first,"%[^:]:%[^:]:%[^:]:%[^:]:%s",_,_,_,addressArray);
		softuart_puts("\ntoken = ");
		softuart_puts(token);
		softuart_puts("\nfirst = ");
		softuart_puts(first);
		updateDeviceInfo(rssi,addressArray) ;
		
		while((token = strtok(NULL,"\r\n"))!= NULL )
		{
			
			if (*token != '+' )
			{
				softuart_puts("\ntoken before break = \n");
				softuart_puts(token);
				break;
			}
			
			sscanf(token,"%[^,],%[^,],%[^,],%s",first,_,rssi);
			sscanf(first,"%[^:]:%[^:]:%[^:]:%[^:]:%s",_,_,_,addressArray);
			softuart_puts("\ntoken = ");
			softuart_puts(token);
			softuart_puts("\nfirst = ");
			softuart_puts(first);
			//puts(rssi);
			//puts(addressArray);
			updateDeviceInfo(rssi,addressArray) ;
		}
	}
}


void updateDeviceInfo(char* rssiStr,char* addrStr)
{
	unsigned int  rssi , address ;
	char bb[20]={'\0'};
	char counter = 0 ;
	rssi = strtol(rssiStr,NULL,16);
	address = strtol(addrStr,NULL,16);
	for(counter = 0 ; counter < 4 ; counter ++)
	{
		if(deviceInfo[counter].address == address)
		{
			deviceInfo[counter].rssi = rssi ;
			
			snprintf(bb,20,"%d",rssi);
			softuart_puts("\nrssi value = ");
			softuart_puts(bb);
			break;
		}
		else
		{
			snprintf(bb,20,"%d",rssi);
			softuart_puts("\nrssi value in else = ");
			softuart_puts(bb);
		}
		
	}
}

void location(struct DeviceInfo deviceInfo[4])
{
	double x = 0 , y = 0,theta = 0 ;
	double A1,A2;
	printf("Resultant array is\n");
	for (c = 0; c < 4; c++)
	printf("%0.3f\t", deviceInfo[c].distance);
	A1 = atan(round(y)/round(x));
	A2 = atan(round(x)/round(y));

	if ((180-(A1+A2))==90)
	{
		if(d2<10)
		{
			printf("x = %0.2f\ny = %0.2f\ntheta = %f",x_room,d2,90);
		}
		else if (d1<10)
		{
			theta=asin(d1/x_room);
			printf("x = %0.2f\ny = %0.2f\ntheta = %f",0,d1,theta);
		}
	}
	else
	{
		y = ((d1*d2)/(x_room));
		x = sqrt((d1*d1)-(y*y));
		theta= asin(round(y)/d1)*(180/PI);
		
		Car_Data.x = x;
		Car_Data.y = y;
		Car_Data.angle = theta; 
		
		softuart_puts(Car_Data.x = x);
		softuart_puts(Car_Data.x = y);
		softuart_puts(Car_Data.x = theta);
		
		/*printf("\nX=%.2f\n",round(x));
		printf("y=%.2f\n",round(y));
		printf("the angle is %.2f",theta);*/
	}

}



