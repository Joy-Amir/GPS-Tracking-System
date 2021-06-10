/*# ifndef FILES_H
# define FILES_H
# include "tm4c123gh6pm.h"
# include "stdint.h"
# include "string.h"
# endif
# include "PORTF.h"
# include "Systick timer.h"
# include "LCD.h"

void UART0_Init(void);
uint8_t UART0_InChar(void);
void UART0_OutChar(uint8_t data);*/


# ifndef FILES_H
# define FILES_H
# include "tm4c123gh6pm.h"
# include "stdint.h"
# include "string.h"
# endif

void UART0_Init(void);
uint8_t UART0_InChar(void);
void UART2_Init(void);
void output(char* latitude, char*longitude, char latitude_type, char longitude_type);
uint8_t UART2_InChar(void);
void UART2_OutChar(uint8_t data);
void UART0_OutChar(uint8_t data);
void get_coordinates(char* latitude,char* longitude, char* latitude_type, char* longitude_type);