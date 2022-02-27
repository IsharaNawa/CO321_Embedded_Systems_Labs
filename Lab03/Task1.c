#include <avr/io.h>

void delay_timer0(){

	TCNT0 = 131;			//load timer counter register with timer 131 in hexadecimal	
  	
  TCCR0A = 0x00;			//set the timer0 under normal 
  TCCR0B = 0b00000100;	//set the prescaler as clk/256
  
  while((TIFR0 & 0x01)==0);	//wait timer overflow bit is set

	TCCR0A = 0x00;	//clear timer settings - this stops the timer
	TCCR0B = 0x00;	
  
  TIFR0 = 0x01;	//clear the timer overflow bit for next round

}

int main(void){
    
	DDRB |= (1<<5);				//PB5 is output

	PORTB &= ~(1<<5);			//set initial value of the PB5 to low

  while(1){
  	
    PORTB ^= (1<<5);			//toggle with a delay
    delay_timer0();

  }

	return 0;
	
}