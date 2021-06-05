# ifndef FILES_H
# define FILES_H
# include "tm4c123gh6pm.h"
# include "stdint.h"
# include "string.h"
# endif
# include "PORTF.h"
# include "Systick timer.h"
# include "LCD.h"
# include "UART.h"

void SystemInit(void)
{
	PORTF_Init();
	Systick_Init();
	LCD_Init();
}

int main(void)
{

	LCD_Data("1207");
	

	
}	
