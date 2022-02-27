#include <avr/io.h>
#include <util/delay.h>

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

  	TCCR0B |= (1<<CS01) | (1<<CS00);                       	//prescaler is macounterimized to 64
    
}

int main(void){ 

    DDRD |= (1<<6);
	
	start_timer();

    unsigned char counter;

	while(1){
        
        for(counter=0;counter<255;counter++){
            OCR0A = counter;
            _delay_ms(10);
        }

        for(counter=255;counter>0;counter--){
            OCR0A = counter;
            _delay_ms(10);
        }
    }							
	
	return 0;
}