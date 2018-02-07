#include <stdint.h>
#include "tm4c123gh6pm.h"

void main(void) {
	uint32_t n;
	uint8_t indice=0;
	uint8_t arreglo[] = {0x02,0x04,0x06,0x08,0x0A,0x0C,0x0E};
	
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
	while( (SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5)==0) { }
	GPIO_PORTF_DIR_R |= 0x0E;
	GPIO_PORTF_DR8R_R |=0x0E;
	GPIO_PORTF_DEN_R |=0x0E;
	
	while(1){
		
		GPIO_PORTF_DATA_R |=arreglo[indice];
		for(n = 0; n < 800000; n++);
		GPIO_PORTF_DATA_R &= ~arreglo[indice];
		indice = indice+1;
		if (indice==8){
			indice = 0;
		}
		for(n = 0; n < 800000; n++);
	
	}
}