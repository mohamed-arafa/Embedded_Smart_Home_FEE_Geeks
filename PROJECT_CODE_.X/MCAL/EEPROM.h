/* 
 * File:   EEPROM.h
 * Author: Mohamed_Arafa
 *
 * Created on April 12, 2021, 1:28 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H

#include "../HELPERS/STD_TYPES.h"
#include "../MEM_MAP_AT32/MACROS.h"
#include "../MEM_MAP_AT32/Mem_map32.h"


void eeprom_write_char(u8 data,u16 Address);

u8 eeprom_read_char(u16 Address); 

#endif	/* EEPROM_H */

