#include <avr/io.h>
#define X 103  

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

unsigned char usart_receive( void )
{
    //wait until the data is received
    while ( !(UCSR0A & (1<<RXC0)) );

   //returning the data
    return UDR0;
}



int main(){

    char members[] = "E/17/027:Pubudu Bandara\nE/17/219:Ishara Nawarathna\n.";

    usart_init(X);
   

    for (int counter = 0; members[counter]!='.'; counter++)
    {
        usart_send(members[counter]);

    }
    

}