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
void main(void) {
	uint32_t temp;
	config_sw1();
	config_leds();
	while(1){
		temp =GPIO_PORTF_DATA_R;
		if ((temp & 0x10) == 0) // si SW1(conectado a PF4) está presionado
		{
			GPIO_PORTF_DATA_R &= ~(0X08);
			GPIO_PORTF_DATA_R |= 0x02; // prendemos el led
			for(n = 0; n < 800000; n++);
			GPIO_PORTF_DATA_R &= ~(0X02);
			GPIO_PORTF_DATA_R |= 0x04; // prendemos el led
			for(n = 0; n < 800000; n++);
			GPIO_PORTF_DATA_R &= ~(0X04);
			GPIO_PORTF_DATA_R |= 0x08; // prendemos el led
			for(n = 0; n < 800000; n++);
		}	
		else // si SW1 no está presionado
		{	
			GPIO_PORTF_DATA_R &= ~0x02; // apagamos el led
		}
	}
} // fin main()