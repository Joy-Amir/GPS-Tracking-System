# ifndef FILES_H
# define FILES_H
# include "tm4c123gh6pm.h"
# include "stdint.h"
# include "string.h"
#include <TM4C123.h>
# endif

void flashEnable(void);
int flashErase(int blockCount);
int flashWrite(const void* data, int wordCount);
void flashRead(void* data, int wordCount);