#ifndef  _External_intrrupt_H_
#define _External_intrrupt_H_

#include "../HELPERS/STD_TYPES.h"
#include "../MEM_MAP_AT32/Mem_map32.h"
#include "../MEM_MAP_AT32/MACROS.h"





typedef enum{
	low_level,
	logical_change,
	falling_edge,
	rising_edge
}EX_INT_MODE_t;

typedef enum{
	EX_INT0,
	EX_INT1,
	EX_INT2
}EX_INT_t;

/*********MCUCR PINS ************/

/*********MCUCSR PIN ************/
#define ISC2	6
/************GICR PINS***********/
#define INT1	7
#define  INT0	6
#define  INT2	5
/************GIFR PINS************/
#define INTF1	7
#define  INTF0	6
#define  INTF2	5

void 
init_ex_interrupt(EX_INT_t  ex_int, EX_INT_MODE_t  mode);

void 
enable_ex_interrupt(EX_INT_t  ex_int);

void 
disable_ex_interrupt(EX_INT_t  ex_int);

u8 
read_ex_interrupt_flag(EX_INT_t  ex_int);

void
EX_setCallBack(EX_INT_t ex_int ,void (*local_ptr)(void));


#endif