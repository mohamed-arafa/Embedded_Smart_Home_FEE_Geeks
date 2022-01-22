
#include "EEPROM.h"
#include"util/delay.h"


void eeprom_write_char(u8 Data,u16 Address )
{
//    while(GET_BIT(EECR,EEWE));  // Wait until the previous EEPROM write operation 
//       
//    EEARL = Address;
//    EEARH = Address>>8;
//                            
//    EEDR = Data;
//                                /* Setting EEMWE to enable writing to EEPROM */
//    SET_BIT(EECR,EEMWE);
//                                /* Start eeprom write by setting EEWE */
//    SET_BIT(EECR,EEWE);



    
/* Wait for completion of previous write */
while(GET_BIT(EECR,EEWE));

/* Set up address and data registers */
EEAR = Address;
EEDR = Data;
/* Write logical one to EEMWE and a zero to EEWE */
EECR=0X04;
/* Start eeprom write by setting EEWE */
EECR=0X02;
}


u8 eeprom_read_char(u16 Address){
                              /* Wait for completion of previous write */
    while(GET_BIT(EECR,EEWE));
                              /* Set up address register */
    EEAR = Address;
                              /* Start eeprom read by writing EERE */
    EECR=0x1;
                              /* Return data from data register */
return EEDR;
}