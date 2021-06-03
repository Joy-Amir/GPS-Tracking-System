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


void UART2_Init(void)
{
	volatile unsigned long delay;
	//using UART2, PORTD
	SYSCTL_RCGCUART_R |= 4;
	delay = SYSCTL_RCGCGPIO_R;
	SYSCTL_RCGCGPIO_R |= 8;
	delay = SYSCTL_RCGCGPIO_R;

	//PORTD unlock
	GPIO_PORTD_LOCK_R = 0x4C4F434B;
	GPIO_PORTD_CR_R |= 0xC0;

	// UART2 initialization 
	//Disable UART
	UART2_CTL_R = 0x0;
	// Using 16MHz, 9600 baud rate
	UART2_IBRD_R = 104;
	UART2_FBRD_R = 11;

	//Set word length to 8 bits, Enable FiFo
	UART2_LCRH_R = 0x70;
	//Enable UART, Rx, Tx	
	UART2_CTL_R = 0x301;


	GPIO_PORTD_DEN_R |= 0xC0;
	GPIO_PORTD_AFSEL_R |= 0xC0;
	GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0X00FFFFFF) | 0x11000000;
	GPIO_PORTD_AMSEL_R &= ~0XC0;
}


uint8_t UART0_InChar(void)
{
	while((UART0_FR_R & 0X10)!=0);
	return (uint8_t) UART0_DR_R&0XFF;
}

