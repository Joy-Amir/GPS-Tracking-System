#include "flash.h"
#define FLASH_BASE_ADDR			((volatile uint32_t*)0x00020000)
	
static uint16_t flashKey = 0;

void flashEnable(){

if (FLASH_BOOTCFG_R & 0x10) {
		flashKey = 	0xA442;
	}
	else {
    flashKey = 0x71D5;
	} 

	
}

int flashErase(int blockCount){
	
	int i;
	
//	if(flashKey ==0){
	//	return -1;
	//}
	
		for ( i = 0; i < blockCount; i++) {
	
		// Clear then set the OFFSET (17:0) with the write address.
			
		//FLASH_FMA_R &= 0xFFFC0000;  
		
		// Blocks are erased on 1KiB boundaries, so multiply the index by 1024
		//	and add this to the base address.
			FLASH_FMA_R =0;
		FLASH_FMA_R |= ((uint32_t)FLASH_BASE_ADDR) + (i*1024);
		
		// Set the ERASE command bit.
    FLASH_FMC_R = (flashKey << 16) | 0x2; 

		// Poll the ERASE bit until it is cleared.
		while (FLASH_FMC_R & 0x2) {}
}
return 0;
}



int flashWrite(const void* data, int wordCount){
	int i;
	int blockCount;
	
	//if(flashKey ==0){
	//	return -1;
//	}
	blockCount = ((wordCount * sizeof(uint32_t)) / 1024) + 1;
	flashErase(blockCount);
	
	for ( i= 0; i < wordCount; i++) {
	
		// Set the data register.  This the word that will be written.

		FLASH_FMD_R = ((volatile uint32_t*)data)[i];
		
		// Clear then set the OFFSET address field (17:0) with the write address.
	//	FLASH_FMA_R &= 0xFFFC0000;  
		FLASH_FMA_R = 0;
		FLASH_FMA_R |= (uint32_t)FLASH_BASE_ADDR + (i * sizeof(uint32_t));
		
		// Trigger a write operation. ..
	FLASH_FMC_R = (flashKey << 16) | 0x1;  //Write bit0 = 1

		// Poll the WRITE bit until it is cleared.
		while (FLASH_FMC_R & 0x1) {}
	
}
	return 0;
}

void flashRead(void* data, int wordCount){
	int i;
	
	for(i =0;i<wordCount;i++){
		((uint32_t*)data)[i] = FLASH_BASE_ADDR[i];
	}
}

