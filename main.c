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
char result[8];
float total_distance = 0;
float latitude[500];
float longitude[500];
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
void SystemInit(void)
{
	UART0_Init();
	CPAC |= 0X00F00000;
	PORTF_Init();
	Systick_Init();
	LCD_Init();
	flashEnable();
}


int main(void)
{
	char c;
	char lat[10];
	char lat_type;
	char longit[11];
	char longit_type;
	
while(1)
{
	if(start_flag == 1 && end_flag == 0)
	{
		c = UART2_InChar();
		if(c == 0X0A)
		{
			get_coordinates(lat, longit, &lat_type, &longit_type);
			latitude[Npoints] = convert_latitude(lat);
			longitude[Npoints] = convert_longitude(longit);
			Npoints++;
			if(Npoints > 1)
			{
				total_distance += TotalDistance(latitude[Npoints - 2], longitude[Npoints - 2], latitude[Npoints - 1], longitude[Npoints - 1]);
			}
			
		}
	
	}
}
}
