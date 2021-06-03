# ifndef FILES_H
# define FILES_H
# include "tm4c123gh6pm.h"
# include "stdint.h"
# include "string.h"
# endif

# define Control_Port					0X01
# define ComDat_Port					0X02	
# define Control_Pins					0XE0
# define Control_Pins_PCTL		0XFFF00000
# define ComDat_Pins 					0XFF
# define ComDat_Pins_PCTL			0XFFFFFFFF
# define RS										0X20
# define RW										0X40
# define EN										0X80




void LCD_Char(uint8_t data);
void LCD_Command(uint8_t command);

