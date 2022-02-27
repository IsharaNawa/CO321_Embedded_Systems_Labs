#include <avr/io.h>

/*
Caluculation:

F(generated_wave) = 16,000,000 / 256 = 62500

F(timer_clock) = F(generated_wave) / N
        976.56 = 62500 / N

N(pre_scalar) ~ 64

duty_cycle = (OCR0 + 1) / 256 * 100%
50% = (OCR0 + 1) / 256 * 100%
OCR0 = 127

*/

void start_timer(){

	TCNT0 = 0;                                              //inital value is set to 0

    TCCR0A |= (1 << WGM01) | (1 << WGM00) ;					//wave form generation mode is set to fast PWM mode
	TCCR0B &= ~(1 << WGM02);

	TCCR0A |= (1<<COM0A1) & ~(1<<COM0A0);    				//set compare output mode to non inverting mode

  	TCCR0B |= (1<<CS01) | (1<<CS00);                       	//prescaler is maximized to 64
    
}


int main(void){ 

    DDRD |= (1<<6);					//PD6 is an output				

	PORTD |= (1<<6);				//initially PB5 is set
	
	OCR0A = 127;					//counts required for the duty cycle

	start_timer();					//starting the timer		

	while(1);						//going to inifinity	
	
	return 0;
}