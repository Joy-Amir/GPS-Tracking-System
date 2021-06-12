# ifndef FILES_H
# define FILES_H
# include "tm4c123gh6pm.h"
# include "stdint.h"
# include "string.h"
#include <math.h>
# endif
#include "distance.h"
# include "TotalDistance.h"
# include "PORTF.h"
# include "Systick timer.h"
# include "LCD.h"
# include "UART.h"
#include "flash.h"
#define CPAC (*((volatile uint32_t *)0xE000ED88))
	
int start_flag = 0;
int end_flag = 0;
int done = 1;
//char result[8] = {'1','2','3','.','5','6','7','8'};
char result[8];
float total_distance = 0;
float data[1000];
float data2[1000];
//float longitude[500];
int Npoints = 0;

void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
  
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
  
    reverse(str, i);
    str[i] = '\0';
    return i;
}
	void ftoa(float n, char* res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;
  
    // Extract floating part
    float fpart = n - (float)ipart;
  
    // convert integer part to string
    int i = intToStr(ipart, res, 0);
  
    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot
  
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter 
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
  
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}
void send_data()
{
	int N;
	uint32_t i;
	uint32_t j;
	//uint32_t lat_len;
	//uint32_t long_len;
	char lat[11];
	char longit[11];
	flashEnable();
	flashRead(data2,(2000+1));
	N = (int) data2[0];
	for (i = 1; i <= N; i++)
	{
		ftoa(data2[2 * i - 1], lat, 6);
		ftoa(data2[2 * i], longit, 6);
		//lat_len = strlen(lat);
		//long_len = strlen(longit);
		for (j = 0; j < 11; j++)
		{
			UART0_OutChar(lat[j]);
			//lat[j] = '\0';
		}
		UART0_OutChar(' ');
		for (j = 0; j < 11; j++)
		{
			UART0_OutChar(longit[j]);
			//longit[j] = '\0';
		}
		UART0_OutChar('\r');
		UART0_OutChar('\n');
		
	}
	done = 1;
	
}

void GPIOF_Handler(void)
{
	Systick_Wait1ms(50);
	if (GPIO_PORTF_MIS_R  & 0x10) //switch 1 for start
	{
		
		PORTF_Output(0x08);
		GPIO_PORTF_ICR_R |= 0x10;
		start_flag = 1;
		Npoints = 0;
		total_distance = 0;
	}
	if (GPIO_PORTF_MIS_R  & 0x01) // switch 2 for end
	{
		GPIO_PORTF_ICR_R |= 0x01;
		end_flag = 1;
		start_flag = 0;
		done = 0;
		PORTF_Output(0);
		Systick_Wait1ms(2000);
		
PORTF_Output(0x04);
		ftoa(total_distance, result, 3); //the input: output of funtion TotalDistance from the main, the output is in array of characters
		LCD_Data(result);
		flashEnable();
		flashWrite(data,((2000+1)+1));
		
	}
}

void SystemInit(void)
{
	UART0_Init();
  CPAC |= 0X00F00000;
	PORTF_Init();
	PortF_Interrupt_Init();
	Systick_Init();
	LCD_Init();
	flashEnable();
	UART2_Init();
}


int main(void)
{
	char c;
	char lat[10];
	char lat_type;
	char longit[11];
	char longit_type;
	uint8_t state;
		
while(1)
{
	if(start_flag == 0)
	{
			//	PORTF_Output(0x02);
		c = UART0_InChar();
		if(c == 0X55)
		{send_data();
		}
	}
		
	if(start_flag == 1 && end_flag == 0)
	{
		//Systick_Wait1ms(100);
		c = UART2_InChar();
		if(c == 0X0A)
		{
			
			
			state = get_coordinates(lat, longit, &lat_type, &longit_type);
			if (state == 1)
			{	Npoints++;
				data[0] = (float)Npoints;
				data[(2 * Npoints) - 1] = convert_latitude(lat);
				data[(2 * Npoints)] = convert_longitude(longit);
				
				if((int)Npoints > 1)
				{
					total_distance += TotalDistance(data[(2 * Npoints) - 3], data[(2 * Npoints) - 2], data[(2 * Npoints) - 1], data[(2 * Npoints)]);
				}
				Systick_Wait1ms(1800);
			}
			
		}
	
	}
}

}
