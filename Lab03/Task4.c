#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY 1000			

void blink_1S(){					

	TCNT1 = 3036;               	//inital value is set to 3036(1seconds)
  	TCCR1A = 0x00;					//mode is set to normal
  	TCCR1B = 0b00000100;           	//prescaler is maximized to 256
	
}

ISR(TIMER1_OVF_vect){				//called when flag is overflowed and TOV0 is set
	
	PORTB ^= (1<<5);				//toggle the PB5 bit
	TCNT1 = 3036; 					//set the initial value again
}



int main(void){
    
	unsigned char z;		//used for knight rider
	DDRB |= (1<<5);			//setting the PB5 as output(used for timer blinking)
	DDRB |= 0x0F;			//least significant 4 bits are outputs
	
	sei();					//enable global interrupt in the status reg
  
  	TIMSK1 |=(1<<TOIE1);	//enable interrupt for timer1

	PORTB &= ~(1<<5);		//initially PB5 is reset

	blink_1S();				//start the timer1
	
	while(1){
  	
		//run the knight rider configuration forward
		for(z=1;z<8;z*=2){
			PORTB = PORTB & ~ 0x0F ;	//assign least 4 pins to be zero
			PORTB = PORTB | z;			//only set the corresponding LED
			_delay_ms(BLINK_DELAY);		//system delay
		}
		
		
		//run the knight rider configuration backward
      	for(z=8;z>1;z/=2){
			PORTB = PORTB & ~ 0x0F ;	//assign least 4 pins to be zero
			PORTB = PORTB | z;			//only set the corresponding LED
			_delay_ms(BLINK_DELAY);		//system delay

		}

	}

	return 0;
	
}