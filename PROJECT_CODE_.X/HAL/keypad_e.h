#ifndef KEYPAD_H_
#define KEYPAD_H_
#define KEYPAD_PORT         PORTC 
#define KEYPAD_DIR          DDRC
#define KEYPAD_PIN          PINC


#include "../MEM_MAP_AT32/Mem_map32.h"
#include "../HELPERS/STD_TYPES.h"
#include "../MEM_MAP_AT32/MACROS.h"
#define ALL_LINES	    (((PINC&(1U<<LINE0))>>LINE0)\
					   &((PINC&(1U<<LINE1))>>LINE1)\
					   &((PINC&(1U<<LINE2))>>LINE2)\
					   &((PINC&(1U<<LINE3))>>LINE3))
//#include "lcd.h"
/*************Definitions of Rows & Coulmns ******************/
#define		ROW0			0
#define		ROW1			1
#define		ROW2			2
#define		ROW3			3
#define		LINE0			4
#define		LINE1			5
#define		LINE2			6
#define		LINE3			7

void keypad_init(void);
char  keypad_scan(void);
char   keypad_result(void);



#endif