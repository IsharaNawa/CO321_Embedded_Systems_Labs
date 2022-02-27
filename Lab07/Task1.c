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