#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char z;	//global because have to use outside main()

int main(void){

  	DDRD = DDRD & ~(0b00001100);	//PD2,PD3 are inputs
  	DDRB = DDRB | 0b00111111;		//PB0-PB5 are outputs
  	
  	EICRA |= (1<<ISC01);	//setting the rising edge for INT0
	EICRA |= (1<<ISC00);  
  
  	EICRA |= (1<<ISC11);	//setting the rising edge for INT1
	EICRA |= (1<<ISC10); 
  
  	sei();		//setting the global interrupt in SReg
  
  	EIMSK |= (1<<INT0);		//enabling INT0 
  	EIMSK |= (1<<INT1);		//enabling INT1
  
  	PORTB &= ~(0b00111111); //initially all LEDs are turned off
  	
  	while(1){}		//runs until the program terminates
	return 0;

}

ISR(INT0_vect){
	PORTB &= ~(0b00111111);	//using pins in port b are reset
  	z *= 2;					//left shiting by 0
  	z &= ~(0b11000000);		//z doesnt affect the 2 msb
  	PORTB |= z;				//assinging the value of z to port b
}

ISR(INT1_vect){
	PORTB &= ~(0b00111111);	//using pins in port b are reset
  	z = 2*z+1;				//left shiting by 1
  	z &= ~(0b11000000);		//z doesnt affect the 2 msb
  	PORTB |= z;				//assinging the value of z to port b
}