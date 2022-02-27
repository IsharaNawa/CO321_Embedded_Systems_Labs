#include <avr/io.h>

#define X 103  

//reading from the EEPROM
unsigned char EEPROMread(unsigned int uiAddress)
{
    /* Wait for completion of previous write */
    while(EECR & (1<<EEPE));
    
    /* Set up address register */
    EEAR = uiAddress;

    /* Start eeprom read by writing EERE */
    EECR |= (1<<EERE);

    /* Return data from Data Register */
    return EEDR;
}

void usart_init( unsigned int ubrr){

    UCSR0B = (1<<RXEN0)|(1<<TXEN0);             //enable the serial transmeter and receiver

    UCSR0C |= (3<<UCSZ00);                      //data bits are 8
    UCSR0C &= ~(1<<USBS0);                      //number of stop bits are 1
                         
    /*Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;

}

void usart_send( unsigned char data )
{
    //waiting for emptying the transfer buffer
    while ( !( UCSR0A & (1<<UDRE0)) );

    //putting the character to the buffer
    UDR0 = data;
}

int main(){

    usart_init(X);

    unsigned char read_sentence[1000];

    int i=0;
    
    for(i=0;read_sentence[i]!='\r';i++){
        read_sentence[i] = EEPROMread(i); 
    }
    
    for (int counter = 0; counter<i; counter++)
    {
        
        usart_send(read_sentence[counter]);

    }
        
    return 0;
}