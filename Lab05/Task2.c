#include <avr/io.h>

int main(){

    DDRC &= ~(1<<1);             //make the PC1 as an input analog signal
    DDRD |= 0b00000001;          //make the port D as output pins
    unsigned char z;

    ADCSRA |= (1<<ADEN);         //enable the built in ADC

    ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) ;  //setting the prescaler of ADC as 128

    ADMUX |= (1<<MUX0);          //setting the analog input channel as ADC1

    ADMUX &= ~(1<<REFS0);        //take the reference voltage as AVcc
    ADMUX &= ~(1<<REFS1);        //take the reference voltage as AVcc

    ADMUX |= (1<<ADLAR);         //getting the most significat 8 bits

    ADCSRA |= (1<<ADSC);        //stating the conversion 

    while(1){

       if((ADCSRA & 1 << ADIF) == 0x10){  //waiting for the coversion to be completed at 128

            z = ADCH;                     //get the value in ADCH to the z
            
            if (z > 192) {
               PORTD |= 1 << 0;           //setting the LED
            } else {
               PORTD &= ~(1 << 0);        //resetting the LED
            }

            ADCSRA &= ~(1 << ADIF);       //reseting the interupt bit
            ADCSRA |= (1 << ADSC);        //starting the conversion again

        }                    
    }            

    return 0;
}