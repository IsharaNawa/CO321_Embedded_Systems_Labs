//including the essential libraries
#include <avr/io.h>
#include <LiquidCrystal.h>
#include <util/delay.h>
#include <EEPROM.h>

#define LENGTH 10   //length of the plain text

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // initialize the lcd library 

char keypad[4][4] = { {'1', '2', '3', 'A'},{'4', '5', '6', 'B'},{'7', '8', '9', 'C'},{'*', '0', '#', 'D'}};

//getting the user input from the keypad
char readKeyPad() {
  
  while (1) {                           //looping until a key is found in the keypad
    
    for (int row = 0; row < 4; row++){
      PORTC &= 0b11110000;              // initially , all rows are resetting 
      PORTC |= (1 << row);              // setting the current iteration row to high
    
      //scanning the j th row
      for (int col = 0; col < 4; col++) {
        if ((PINB >> col) & 1){         //get the intersection of the row and col
        	_delay_ms(350);               //wait for a delay to insert the key by the user
            return(keypad[row][col]);   //return the entered key
        }
      }
    }
  }
}

// function to return the cipher encrypted key
void cipher(char *str, int key){
    
    int place = 0;                  // to place the cursor
    char *pointer = str, plaintext; // to get the plaintext

    while(*pointer != '#'){

        
        lcd.setCursor(place, 1);        //set the cursor

        //for A,B,C,D
        if(*pointer > 64 && *pointer < 69){
            plaintext = (*pointer - 65 + key) % 26 + 65;
            lcd.print(plaintext);
        }
        
        else{
            lcd.print(*pointer);
        }

        place++;          //increment the place of the lcd       
        pointer++;        //move to the next character
    }
}
//getting the option from the user
char getOption(){
    lcd.setCursor(0, 0);            //setting the cursor
    lcd.print("Change key?");       //prompt user to enter the key
    lcd.setCursor(0, 1);            //setting the cursor 
    lcd.print("Yes - 1, No - 2");   //giving the user the input options
    
    char buffer = readKeyPad();     // get the user input from the keypad
    lcd.clear();                    //clear
    return buffer;                  //return the keypad input as the option
}

int main(){

    lcd.begin(16, 2);             //apply the number of 16 as the columns and 2 rows
    
  	DDRC |= 0b00001111;		        // PC0 to PC3 are outputs and considered as rows of the keypad
  	DDRB &= ~(0b00001111);  	    // PB0 to PB3 are input columns of keypad
    
    int cursor_place = 0;             //cursor controlling variable
    
    char index, buffer,option;
    int key = EEPROM.read(0);           //reading the key from the read
    char plain_text[LENGTH];            //array to store the encrypted text

    while(1){                           //infinity loop(polling)

        option = getOption();           //get the user option

        if (option == '1'){             //in case of key change
            
            key = 0;                     //initially key is set to 0(acts as the total)
            lcd.setCursor(0, 0);         //cursor is set to 1st row 1st column
            lcd.print("Enter key:");    //propt the user to enter the key
            lcd.setCursor(0, 1);        //move to the nex row
            
            
            buffer = readKeyPad();      //listen for user to enter a key on the keypad
            lcd.setCursor(0, 1);        //move to the next row
            lcd.print(buffer);          //dispaly the entered number on the keypad
            
            
            key += (buffer - '0') * 10;       //get the key value by adding the first number
                
            _delay_ms(300);                   //wait a delay for the next number 
            
            //same procedure for the sencond digit
            buffer = readKeyPad();
            lcd.setCursor(1, 1);
            lcd.print(buffer);
            key += (buffer - '0');


            EEPROM.write(0,key);      //write the calculated key value to the EEPROM

          	_delay_ms(700);           //wait for a delay
            
            readKeyPad();             // read the next character
            lcd.clear();              //clear the display
        }
        


        //in case of the encryption process

        //propmting for the plain text
        lcd.setCursor(0, 0);
        lcd.print("Enter Plain Text:");
        
        //buffer is reset to null
        buffer = '0';
        cursor_place = 0; //cursor controlling
        
        index = 0;
        lcd.setCursor(0, 1);
        
        //read values from the user on keypad until # is entered or length is met
        while(buffer != '#' && index != LENGTH){
            buffer = readKeyPad();          //read the each value to the buffer
            plain_text[index] = buffer;     //append the input character to the plain text 
            index++;                        //increment the index
            
            lcd.print(buffer);              //print the character
            cursor_place++;                 //move the cursor to the next column
            lcd.setCursor(cursor_place, 1);   //display the cursor
        }

        plain_text[index] = '#';            //add the # at the end
        
        //lcd is set for displaying the cipher text
        lcd.clear();    
        lcd.setCursor(0, 0);
        lcd.print("Cipher Text : ");
        lcd.setCursor(0, 1);
        

        cipher(plain_text, key);    // encrypt and display the cipher text
        
        // press any key
        readKeyPad();  
        lcd.clear();
        
    }
    return 0;
}