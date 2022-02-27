#include <avr/io.h>
#include <ctype.h>

#define X 103  

/* 
Calculations:
             Fosc = 16MHz
Desired-baud-rate = 9600
                X = [Fosc / (16 * Desired-baud-rate)] -1
                X = [16,000,000 / (16 * 9600)] - 1
                X = 103.1.7 ~ 103
 */


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

void encrypt(int key,char message[]){

    int i;
    char ch;

    for(i = 0; message[i] != '\0'; ++i){
        ch = message[i];
        if(ch >= 'a' && ch <= 'z'){
                ch = ch + key;
            if(ch > 'z'){
                ch = ch - 'z' + 'a' - 1;
            }
                message[i] = ch;
        }

        else if(ch >= 'A' && ch <= 'Z'){
            ch = ch + key;
            if(ch > 'Z'){
                ch = ch - 'Z' + 'A' - 1;
            }
            message[i] = ch;
        }
    }

}


int main(){

    usart_init(X);
   
    unsigned char rec_sentence[1000];           //for receiving the sentence

    while(1){                                   //repeatedly taking inputs

    int counter = 0;
   
        while(1){

            rec_sentence[counter] = usart_receive();
            if(rec_sentence[counter]=='\n'){
                break;
            }
            counter++;
        }

        rec_sentence[counter]='\0';

        encrypt(3,rec_sentence);

        for (int counter = 0; rec_sentence[counter]!='\0'; counter++)
        {
            
            usart_send(rec_sentence[counter]);

        }
            usart_send('\n');
    }

}
