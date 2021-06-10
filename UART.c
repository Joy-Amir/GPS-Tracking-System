# include "UART.h"
# include "distance.h"  //##############

extern int end_flag;   //#############
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
	GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0X00FFFFFF)|0x11000000;
	GPIO_PORTD_AMSEL_R &=~0XC0;
}

uint8_t UART0_InChar(void)
{
	while((UART0_FR_R & 0X10)!=0);
	return (uint8_t) UART0_DR_R&0XFF;
}

uint8_t UART2_InChar(void)
{
	while((UART2_FR_R & 0X10)!=0);
	return (uint8_t) UART2_DR_R&0XFF;
}

void UART2_OutChar(uint8_t data)
{
	while((UART2_FR_R & 0X20)!=0);
	UART2_DR_R = data;
}

void UART0_OutChar(uint8_t data)
{
	while((UART0_FR_R & 0X20)!=0);
	UART0_DR_R = data;
}



uint8_t get_coordinates(char* latitude,char* longitude, char* latitude_type, char* longitude_type)
{
	char tag_check[] = "$GPGLL";
	char tag[7];
	char input, valid;
	uint8_t i;
		
			for(i = 0; i < 6 && end_flag != 0; i++)
				tag[i] = UART2_InChar();
			if (strcmp(tag_check, tag) == 0)
			{
				GPIO_PORTF_DATA_R= 0X02;
				input = UART2_InChar();///bypass the comma
				for(i = 0; i < 10 && end_flag != 0; i++)
				{
					latitude[i] = UART2_InChar();
				}
				input = UART2_InChar();///bypass the comma
				*latitude_type = UART2_InChar();
			
				input = UART2_InChar();///bypass the comma
				for(i = 0; i < 11 && end_flag != 0; i++)
				{
					longitude[i] = UART2_InChar();
				}
				input = UART2_InChar();///bypass the comma
				*longitude_type = UART2_InChar();
				for(i = 0; i < 11 && end_flag != 0; i++)
				{
					input = UART2_InChar();
				}
				valid = UART2_InChar();
				if(valid == 'A')
				{
					return 1;
				}
			
			}
			return 0;
}
void output(char* latitude, char*longitude, char latitude_type, char longitude_type)
{
	uint8_t i;
	for(i = 0; i < 10; i++)
	{
		UART0_OutChar(latitude[i]);
	}
	UART0_OutChar(',');
	UART0_OutChar(latitude_type);
	UART0_OutChar('\n');
	for(i = 0; i < 11; i++)
	{
		UART0_OutChar(longitude[i]);
	}
		UART0_OutChar(',');
		UART0_OutChar(longitude_type);
		UART0_OutChar('\n');
}






