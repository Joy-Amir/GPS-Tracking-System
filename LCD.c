# include "LCD.h"
# include "Systick timer.h"

void LCD_Init(void)
{
	volatile unsigned long delay;
	SYSCTL_RCGCGPIO_R |= (Control_Port | ComDat_Port);
	delay = SYSCTL_RCGCGPIO_R;
	//while ((SYSCTL_PRGPIO_R & 0X20) == 0);
	GPIO_PORTA_LOCK_R = 0X4C4F434B;
	GPIO_PORTA_CR_R |= Control_Pins;
	GPIO_PORTA_DIR_R |= Control_Pins;
	GPIO_PORTA_PUR_R &= ~Control_Pins;
	GPIO_PORTA_DEN_R |= Control_Pins;
	GPIO_PORTA_AMSEL_R &= ~Control_Pins;
	GPIO_PORTA_AFSEL_R &= ~Control_Pins;
	GPIO_PORTA_PCTL_R &= ~Control_Pins_PCTL;
	
	GPIO_PORTB_LOCK_R = 0X4C4F434B;
	GPIO_PORTB_CR_R |= ComDat_Pins;
	GPIO_PORTB_DIR_R |= ComDat_Pins;
	GPIO_PORTB_PUR_R &= ~ComDat_Pins;
	GPIO_PORTB_DEN_R |= ComDat_Pins;
	GPIO_PORTB_AMSEL_R &= ~ComDat_Pins;
	GPIO_PORTB_AFSEL_R &= ~ComDat_Pins;
	GPIO_PORTB_PCTL_R &= ~ComDat_Pins_PCTL;
	//Systick_Wait1ms(200);//ref delay 20 m
	//LCD_Command(0X30);						//wakeup
	Systick_Wait1ms(50);
	//delay 40 micro "different in ref"
	//ref delay 5 m
	
	//LCD_Command(0X30);						//wakeup
	//Systick_Wait1us(1000);
	//delay 40 micro "different in ref"
	//ref delay 100 micro
	
	//LCD_Command(0X30);						//wakeup
	//Systick_Wait1us(400);
	//delay 40 micro "different in ref"
	
	LCD_Command(0X38);						//For 8 bit data
	Systick_Wait1ms(1);
	//delay 40 micro "different in ref"
	
	LCD_Command(0X0E);							//Turn on display: Cursor blinking
	Systick_Wait1us(400);
	//delay 40 micro "different in ref"
	
	LCD_Command(0X01);							//Clear screen and move cursor home
	Systick_Wait1ms(20);
	//delay 2 milli "different in ref"
	
	LCD_Command(0X06);							//Move cursor right
	Systick_Wait1us(400);
	//delay 40 micro "different in ref"
}


void LCD_Command(uint8_t command)
{
	GPIO_PORTA_DATA_R &=~(RS|RW);					//Clear Rs, Rw, En
	
	GPIO_PORTB_DATA_R = command;
	
	GPIO_PORTA_DATA_R|= EN;
	//delay  150 ns minimum or 240
	if(command < 4)
	{
		//delay 2 ms
		Systick_Wait1ms(2);
	}
	else
	{
		//delay 40 micro sec
		Systick_Wait1us(40);
	}
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


void LCD_Cursor(uint8_t pos)
{
   LCD_Command(0X80 + (pos % 16));
}
   
void LCD_Clear(void)
{

   LCD_Command(0x01);
}

//#########################
void LCD_Data(char* data)
{
	uint8_t length;
	uint8_t i;
	uint8_t afterpoint = 3;
	uint8_t flag = 0;
	length = strlen(data);
	LCD_Clear();
	for(i = 0; (i < length && i < 16 && afterpoint > 0); i++)
	{
		if(flag)
			afterpoint --;
		LCD_Cursor(i);
		LCD_Char(data[i]);
		LCD_Command(0xC0 + 16); //Hide cursor
		if(data[i] == '.')
			flag = 1;
	}
}
