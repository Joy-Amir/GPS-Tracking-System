# include "PORTF.h"
void PORTF_Init(void)
{
	volatile unsigned long delay;
	SYSCTL_RCGCGPIO_R |= 0X20;
	delay = SYSCTL_RCGCGPIO_R;
	//while ((SYSCTL_PRGPIO_R & 0X20) == 0);
	GPIO_PORTF_LOCK_R = 0X4C4F434B;
	GPIO_PORTF_CR_R |= 0X1F;
	GPIO_PORTF_DIR_R |= 0X0E;
	GPIO_PORTF_DIR_R &= ~0x11;
	GPIO_PORTF_PUR_R |= 0X11;
	GPIO_PORTF_DEN_R |= 0X1F;
	GPIO_PORTF_AMSEL_R = 0X00;
	GPIO_PORTF_AFSEL_R = 0X00;
	GPIO_PORTF_PCTL_R = 0X00;
}

void PORTF_Output(uint8_t data)
{
	GPIO_PORTF_DATA_R &= ~0X0E;
	GPIO_PORTF_DATA_R |= data;
}

uint8_t PORTF_Input(void)
{
	return (GPIO_PORTF_DATA_R & 0X11);
}

void turn_on_Led_100(uint32_t distance) {

	if (distance > 100) {
		PORTF_Output(0x02);

	}
}

