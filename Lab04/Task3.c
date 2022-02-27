#include <avr/io.h>
#include <util/delay.h>

#define DELAY_TIMER 1000

/*
Caluculation:

let choose duty circle as 50%.
duty_cycle = (OCR0 + 1) / 256 * 100%
50% = (OCR0 + 1) / 256 * 100%
OCR0 = 127

let prescaler = 1024, frequency = 61.03Hz
let prescaler = 256, frequency = 244.10Hz
let prescaler = 64, frequency = 976.56Hz
let prescaler = 8, frequency = 7812.50Hz
*/

void start_timer(){

	TCNT0 = 0;                                              //inital value is set to 0

    TCCR0A |= (1 << WGM01) | (1 << WGM00) ;					//wave form generation mode is set to fast PWM mode
	TCCR0B &= ~(1 << WGM02);

	TCCR0A |= (1<<COM0A1) & ~(1<<COM0A0);    				//set compare output mode to non inverting mode

    while(1)
    {
		TCCR0B = 0x05;						//prescaler is 1024
      	_delay_ms(DELAY_TIMER);
		TCCR0B = 0x04;						//prescaler is 256
      	_delay_ms(DELAY_TIMER);
		TCCR0B = 0x03;						//prescaler is 64
      	_delay_ms(DELAY_TIMER);				
      	TCCR0B = 0x02;						//prescaler is 8
     	_delay_ms(DELAY_TIMER);  	
    }

}

int main(void){ 

    DDRD |= (1<<6);					//PD6 is an output				
	
	OCR0A = 127;					//duty circle is set to 0.5

	start_timer();					//starting the timer		
	
	return 0;
}