# include "UART.h"

void UART0_Init(void)
{
	volatile unsigned long delay;
	//using UART0, PORTA
	SYSCTL_RCGCUART_R |= 0X01;
	delay = SYSCTL_RCGCGPIO_R;
	SYSCTL_RCGCGPIO_R |= 0X01; 
	delay = SYSCTL_RCGCGPIO_R;
 
	// UART0 initialization 
	//Disable UART
	UART0_CTL_R = 0X0; 
	// Using 16MHz, 9600 baud rate
	UART0_IBRD_R = 104; 
	UART0_FBRD_R = 11; 
	
	//Set word length to 8 bits, Enable FiFo
	UART0_LCRH_R = 0x70;
	//Enable UART, Rx, Tx	
	UART0_CTL_R = 0x301; 
 
	
	GPIO_PORTA_DEN_R |= 0x03; 
	GPIO_PORTA_AFSEL_R |= 0x03; 
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0XFFFFFF00)|0x11; 
	GPIO_PORTA_AMSEL_R &=~0X03;
}

