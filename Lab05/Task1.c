#include <avr/io.h>

/*
calculation:

setting the prescaler value

-let prescaler be 128

    frequency of ADC = 16 MHz / 128 = 125kHz < 200KHz ==> requirement satisfied.

*/

int main(){

    DDRC &= ~(1<<1);            //make the PC1 as an input analog signal
    DDRD |= 0b11111111;         //make the port D as output pins
    unsigned char z;

    ADCSRA |= (1<<ADEN);        //enable the built in ADC

    ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) ;    //setting the prescaler of ADC as 128

    ADMUX |= (1<<MUX0)  ;       //setting the analog input channel as ADC1

    ADMUX |= (1<<REFS0);        //take the reference voltage as AVcc

    ADMUX |= (1<<ADLAR) ;       //getting the most significat 8 bits

    ADCSRA |= (1<<ADSC);        //stating the conversion 

    while(1){

        if((ADCSRA & 1<< ADIF)==0x10){  //waiting for the coversion to be completed

            z = ADCH;                   //get the value in ADCH to the z
            
            //according to the voltage level, the LED series is bieng lit
            //the range is devided into 8 equel parts for each LED
            if (z>224)
              PORTD = 0xFF;
          	else if(z>192)
              PORTD = 0x7F;
            else if(z>160)
              PORTD = 0x3F;
            else if(z>128)
              PORTD = 0x1F;
            else if(z>96)
              PORTD = 0x0F;
            else if(z>64)
              PORTD = 0x07;
            else if(z>32)
              PORTD = 0x03;
            else
              PORTD = 0x00;

            ADCSRA &= ~(1<<ADIF);       //reseting the interupt bit
            ADCSRA |= (1<<ADSC);        //starting the conversion again
        }                    
    }            

    return 0;
}