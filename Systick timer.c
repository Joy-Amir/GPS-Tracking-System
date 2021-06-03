# include "Systick timer.h"
void Systick_Init(void)
{
	NVIC_ST_CTRL_R = 0X00;
	NVIC_ST_RELOAD_R = 0X00FFFFFF;
	NVIC_ST_CURRENT_R = 0X0;
	NVIC_ST_CTRL_R = 0X05;
}
void Systick_Wait(uint32_t delay)
{
	NVIC_ST_RELOAD_R = delay-1;
	NVIC_ST_CURRENT_R = 0;
	while((NVIC_ST_CTRL_R & 0X00010000) == 0);
}
void Systick_Wait1us(uint32_t delay)
{
	uint32_t i;
	for (i = 0; i < delay; i++)
	{
		Systick_Wait(16);
	}
}
void Systick_Wait1ms(uint32_t delay)
{
	uint32_t i ;
	for (i = 0; i < delay; i++)
	{
		Systick_Wait(16000);
	}
}
