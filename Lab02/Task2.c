#include <avr/io.h>
#include <avr/interrupt.h>

int main(void){

	//setting data directions
  	DDRD &=  ~(1<<2);	//2 bit of port D is input	
  	DDRB |=  (1<<0);	//0th bit of port B are outputs
  
  	EICRA |= (1<<ISC01);	//setting the behaviour of the inturrupt
	EICRA &= ~(1<<ISC00);  	//of port d to negative edge of the clock
  
  	sei();					//enable global interrupt in the status reg
  
  	EIMSK |=(1<<INT0);		//enable interrupt for PD2(int0)
  
  	PORTB &= ~(1<<0);		//initally 0 bit of port B are reset
  
    while(1){}				//infinity loop
	return 0;

}

ISR(INT0_vect){				//call this routine when intrrupted by INT0 vector
	
  PORTB ^= (1<<0);			//toggle the current 0th bit of port b
  
}