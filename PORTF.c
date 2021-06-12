# include "PORTF.h"
void PORTF_Init(void)
{
	volatile unsigned long delay;
	SYSCTL_RCGCGPIO_R |=0X20;
	delay = SYSCTL_RCGCGPIO_R;
	//while ((SYSCTL_PRGPIO_R & 0X20) == 0);
	GPIO_PORTF_LOCK_R = 0X4C4F434B;
	GPIO_PORTF_CR_R |= 0X1F;
	GPIO_PORTF_DIR_R |= 0X0E;
	GPIO_PORTF_PUR_R |= 0X11;
	GPIO_PORTF_DEN_R |= 0X0E;
	GPIO_PORTF_AMSEL_R = 0X00;
	GPIO_PORTF_AFSEL_R = 0X00;
	GPIO_PORTF_PCTL_R = 0X00;
}

void PORTF_Output(uint8_t data)
{








	GPIO_PORTF_DATA_R &=~0X0E;
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


//PortF Interrupt Intialization

void PortF_Interrupt_Init(void)
{
	SYSCTL_RCGCGPIO_R |= 0x00000020;
	//flag=0;
	GPIO_PORTF_DIR_R &= ~0x11;
	GPIO_PORTF_DEN_R |= 0x11;
	//GPIO_PORTF_DIR_R &= ~0x11;    //correction
	GPIO_PORTF_PUR_R |= 0x11;
	GPIO_PORTF_IS_R &= ~0x11;    // PF1 & PF4 Edge Sensitive
	GPIO_PORTF_IBE_R &= ~0x11;   // PF1 & PF4 not Both Edges Sensitive
	GPIO_PORTF_IEV_R &= ~0x11;  // PF1 & PF4 Falling Edge Event
	GPIO_PORTF_ICR_R = 0x11;    //Flag1 & Flag4 Clear
	GPIO_PORTF_IM_R |= 0x11;    //ARM Interrupt on PF1 & PF4
	NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF00FFFF) | 0x00200000;  //Priority Register for Port F (Priority 1)//correct
	NVIC_EN0_R = 0x40000000;  // Enable Interrupt Register 30 in NVIC
	//EnableInterrupts();
}
