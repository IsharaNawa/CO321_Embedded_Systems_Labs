#include <avr/io.h>

#define X 103  

//writing to the EEPROM
void EEPROMwrite(unsigned int uiAddress, unsigned char ucData)
{

    /* Wait for completion of previous write */
    while(EECR & (1<<EEPE));

    /* Set up address and Data Registers */
    EEAR = uiAddress;
    EEDR = ucData;

    /* Write logical one to EEMPE */
    EECR |= (1<<EEMPE);

    /* Start eeprom write by setting EEPE */
    EECR |= (1<<EEPE);
}

void usart_init( unsigned int ubrr){

    UCSR0B = (1<<RXEN0)|(1<<TXEN0);             //enable the serial transmeter and receiver

    UCSR0C |= (3<<UCSZ00);                      //data bits are 8
    UCSR0C &= ~(1<<USBS0);                      //number of stop bits are 1
                         
    /*Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;

}

unsigned char usart_receive( void )
{
    //wait until the data is received
    while ( !(UCSR0A & (1<<RXC0)) );

   //returning the data
    return UDR0;
}

int main(){

    usart_init(X);

    unsigned char rec_sentence[1000];           //for receiving the sentence

    int counter = 0;                            //counter
   
    while(1){

        rec_sentence[counter] = usart_receive();
        if(rec_sentence[counter]=='\r'){
            break;
        }
        counter++;
    }

    
    int i;
    for(i=0;i<counter;i++){
         EEPROMwrite(i,rec_sentence[i]);
    }

    return 0;
}