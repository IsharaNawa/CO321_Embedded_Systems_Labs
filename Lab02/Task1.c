#include <avr/io.h>

int main(void)
{
    unsigned char z = 0;			//BUTTON PRESSING COUNT
    unsigned char pre_state = 0;    // INITIALLY BUTTON IS RELEASED
  
    DDRD &= ~(1 << 7);				//7TH BIT OF PORTD IS INPUT
  
    DDRB |= 0b00111111;				////FIRST 6 BITS OF PORTB ARE OUTPUTS
  
    PORTB &= ~(0b00111111);         // INITIALLY ALL BULBS ARE UNLIT
  
    while (1)						//INFINITY LOOP
    {
        
      	if ((PIND >> 7) & 1){			//IF THE BUTTON IS PRESSED
         
          	if(pre_state==0){			//AT THE RISISNG EDGE
           		PORTB &= ~(0b00111111);	// UNLITs ALL BULBS TO SET ONLY THE RELEVENT BULB(S)
          		z++;					//INCREMENT NUMBER OF BUTTON PRESSES
            	z &= ~(0b11000000);		//CANCEL OUT EFFECTS FROM z TO THE 2 MSBS OF PORTB
            	PORTB |= z;				//ASSIGN Z TO PORTB
            	pre_state=1;			//SET THE CURRENT STATE
    		} 
    	}else{
        	pre_state=0;			//IF THE BUTTON IS NOT PRESSED, RESET THE PRESET
          	}  
	}
  	return 0;
}