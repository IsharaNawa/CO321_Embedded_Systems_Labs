#include <avr/io.h>
#include <avr/interrupt.h>


unsigned char z;			//global because used in ISR
int main(void){

	//setting data directions
  	DDRD &=  ~(1<<2);		//2 bit of port D is input
  	DDRB |= 0b00111111;		//first 6 bits of port B are outputs
  
  	EICRA |= (1<<ISC01);	//setting the behaviour of the inturrupt 
	EICRA &= ~(1<<ISC00);  	//of port d to negative edge of the clock
  	
  	sei();					//enable global interrupt in the status reg
  
  	EIMSK |= (1<<INT0);		//enable interrupt for PD2(int0)
  
  	PORTB &= ~(0b00111111); //initally first 6 bits of port B are reset
  
  	while(1){}				//inifinity loop
	return 0;

}

ISR(INT0_vect){					//call this routine when intrrupted by INT0 vector
	
  	PORTB &= ~(0b00111111);		//initally first 6 bits of port B are reset
  	z++;						//increment z by 1
  	z &= ~(0b11000000);			//cancel out the effect of z to 2 msbs of port b
  	PORTB |= z;					//port b is assigned to z
  
}