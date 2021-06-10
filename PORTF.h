# ifndef FILES_H
# define FILES_H
# include "tm4c123gh6pm.h"
# include "stdint.h"
# include "string.h"
# endif


void PORTF_Init(void);
void PORTF_Output(uint8_t data);
uint8_t PORTF_Input(void);
void turn_on_Led_100(uint32_t distance);
void PortF_Interrupt_Init(void);