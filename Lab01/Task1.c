#include <avr/io.h>			//including standard AVR header
#include <util/delay.h>		//time delay handling library
#define BLINK_DELAY 500 	//dening the time dealy

int main(void){

	DDRB = DDRB | 0X0F;			//setting the least 4 bits
		
  	
  
	while(1){
		PORTB = PORTB | 0x0F;		//setting the least 4 bits	
      
		_delay_ms(BLINK_DELAY);		//delay 

      	PORTB = PORTB & ~ 0x0F;		//clearing least 4 bits
      	
      	_delay_ms(BLINK_DELAY);		//delay
      
	}

	return 0;
}