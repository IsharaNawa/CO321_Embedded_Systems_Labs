#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char count=0;				//global because used in ISR

//timer function 
void delay_timer(){

	//setting up timer0
	TCNT0 = 100;                    //inital value is set to 100
  	TCCR0A = 0x00;					//mode is set to normal
  	TCCR0B = 0b00000101;            //prescaler is maximized to 1024
	
	//delay is 10ms
	
	//setting up timer1
	TCNT1 = 34286;                  //inital value is set to 34286
  	TCCR1A = 0x00;					//mode is set to normal
  	TCCR1B = 0b00000100;           	//prescaler is maximized to 256

  	//delay is 500ms
	
}

ISR(TIMER0_OVF_vect){				//called when flag is overflowed
	
	count++;						//incrementing the counter
	if(count==5){					//check if the counter is 10
		PORTB ^= (1<<5);			//if it is 10, 100ms is completed
		count=0;
	}
	TCNT0 = 100; 
	                  //inital value is set to 100
}

ISR(TIMER1_OVF_vect){				//called when flag is overflowed
	
	PORTB ^= (1<<4);
	TCNT1 = 34286;		

}

int main(void){ 

	DDRB |= (1<<5) | (1<<4);        //PB5 and 4 are outputs

	sei();							//setting global interrupts
	
  	TIMSK0 |=(1<<TOIE0);			//enable timer interrupt for timer0
	TIMSK1 |=(1<<TOIE1);			//enable timer interrupt for timer1
	
	PORTB &= ~(1<<5);				//initially PB5 is reset
	PORTB &= ~(1<<4);				//initially PB4 is reset 
	
	delay_timer();					//start timer0 and timer1

	while(1);						//inifinite loop
	
	return 0;
}