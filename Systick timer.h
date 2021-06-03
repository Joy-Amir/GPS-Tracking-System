# ifndef FILES_H
# define FILES_H
# include "tm4c123gh6pm.h"
# include "stdint.h"
# include "string.h"
# endif



void Systick_Init(void);
void Systick_Wait(uint32_t delay);
void Systick_Wait1us(uint32_t delay);
void Systick_Wait1ms(uint32_t delay);
