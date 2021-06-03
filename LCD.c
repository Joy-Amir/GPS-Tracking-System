# include "LCD.h"
# include "Systick timer.h"


void LCD_Command(uint8_t command)
{
	GPIO_PORTA_DATA_R &=~(RS|RW);					//Clear Rs, Rw, En
	
	GPIO_PORTB_DATA_R = command;
	
	GPIO_PORTA_DATA_R|= EN;
	//delay  150 ns minimum or 240
	
	GPIO_PORTA_DATA_R &=~EN;
}


void LCD_Char(uint8_t data)
{
	GPIO_PORTA_DATA_R &=~RW;					//Clear Rs, Rw, En
	GPIO_PORTA_DATA_R |= RS;
	
	GPIO_PORTB_DATA_R = data;
	
	GPIO_PORTA_DATA_R|= EN;
	Systick_Wait1ms(2);
	GPIO_PORTA_DATA_R &=~EN;

}

