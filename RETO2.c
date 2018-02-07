#include <stdint.h>
#include "tm4c123gh6pm.h"

void config_sw1(void){
	// activamos la señal de reloj del puerto F
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
	// esperamos a que realmente se active
	while( (SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5)==0) { }
	// SW1 está conectado al pin PF4
	GPIO_PORTF_DIR_R &= ~(0x10); // PF4 pin de entrada
	GPIO_PORTF_AFSEL_R &= ~(0x10); // no usamos función alternativa
	GPIO_PORTF_PUR_R |= 0x10; // activamos resistencia de pull-up en pin PF4
	GPIO_PORTF_DEN_R |= 0x10; // PF4 pin digital
}
void config_leds(void){
	// activamos la señal de reloj del puerto F
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
	// esperamos a que realmente se active
	while( (SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5)==0) { }
	GPIO_PORTF_DIR_R |= 0x0E; // Configura el bit 1 del puerto F como salida
	GPIO_PORTF_DR8R_R |=0x0E; // se activa el driver de 8 mA en el pin 1.
	GPIO_PORTF_DEN_R |=0x0E; // se activa el pin 1, como salida digital.
	GPIO_PORTF_DATA_R &= ~(0X0E); // apagamos el led
}

void shine(uint8_t var){
	uint32_t n;
	GPIO_PORTF_DATA_R |= var;
	for(n = 0; n < 800000; n++);
	GPIO_PORTF_DATA_R &= ~var;
}

void main(void) {
	uint8_t selector=0; 
	config_leds();
	config_sw1();
	uint8_t variable1 = 0x02;
	uint8_t variable2 = 0x04;
	uint8_t variable3 = 0x06;
	uint8_t variable4 = 0x08;
	
	while(1){
		while((GPIO_PORTF_DATA_R & 0x10) == 0)
		while((GPIO_PORTF_DATA_R & 0x10) == 0x10)
		switch (selector)
		{
			case 0:
				shine(variable1);
				selector =1;
				break;
			case 1:
				shine(variable2);
				selector =2;
				break;
			case 2:
				shine(variable3);
				selector =3;
				break;
			case 3:
				shine(variable4);
				selector =0;
				break;
		}
	
	}
}