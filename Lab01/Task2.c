#include <avr/io.h>				//including standard AVR header
#include <util/delay.h>			//including libraries to hadle delay
#define BLINK_DELAY 500			//defining the dalay constant

int main(void){			

	unsigned char z;					//store active pin
	DDRB = DDRB | 0x0F;					//least 4 pins of port B are outputs

	while(1){
      
		for(z=1;z<8;z*=2){
			PORTB = PORTB & ~ 0x0F ;	//assign least 4 pins to be zero
			PORTB = PORTB | z;			//only set the corresponding LED
			_delay_ms(BLINK_DELAY);		//delay
		}
      
      	for(z=8;z>1;z/=2){
			PORTB = PORTB & ~ 0x0F ;	//assign least 4 pins to be zero
			PORTB = PORTB | z;			//only set the corresponding LED
			_delay_ms(BLINK_DELAY);		//delay
		}

		
	}
	return 0;
}