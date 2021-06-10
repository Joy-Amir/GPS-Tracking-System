# ifndef FILES_H
# define FILES_H
# include "tm4c123gh6pm.h"
# include "stdint.h"
# include "string.h"
#include "math.h"
# endif
#include "distance.h"
# include "PORTF.h"
# include "Systick timer.h"
# include "LCD.h"
# include "UART.h"
#include "flash.h"
#define CPAC (*((volatile uint32_t *)0xE000ED88))
		
int start_flag = 0;
int end_flag = 0;


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
char res[11] ={0};
//char out[11] ={0};
//char w[11] ={0};
int i;
int j;
float x ;
float y;
float z;
float a[6] = {3005.88788 ,03118.61276, 3025.88710,03118.61276,3001.11110,03118.61276};
float b[6] = {0};

while (start_flag == 1 & end_flag == 1)
{
for(i = 0;i<6;i++){
	ftoa(a[i], res, 9);
	b[i] = convert_latitude(res);
}

//ftoa(x, res, 9);
//for(i=0;i<10;i++){
//UART0_OutChar(res[i]);
//}
//}	


}
}

void GPIOF_Handler(void)
{
	Systick_Wait1ms(70);
	
	//switch 1 for start
	
	
	if (GPIO_PORTF_MIS_R  & 0x01) // switch 2 for end
	{
		end_flag = 0;
		char lcd_total_distance[6];
		PortF_Output(0x08);
		//ftoa(TotalDistance, res, 3); //the input: output of funtion TotalDistance from the main, the output is in array of characters
		LCD_Data(lcd_total_distance);
		GPIO_PORTF_ICR_R |= 0x01;
	}
}