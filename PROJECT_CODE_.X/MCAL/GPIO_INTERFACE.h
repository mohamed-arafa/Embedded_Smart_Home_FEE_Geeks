#ifndef _GPIO_INTERFACE_H_
#define _GPIO_INTERFACE_H_

#include "../MEM_MAP_AT32/MACROS.h"
#include "../MEM_MAP_AT32/Mem_map32.h"
#include "../HELPERS/STD_TYPES.h"
typedef enum
{
    INPUT=0,
    OUTPUT
}state_t;

typedef enum
{
GPIOA =0 ,
GPIOB,
GPIOC,
GPIOD
}
portname_t ;
typedef enum{
pin0=0,
pin1,
pin2,
pin3,
pin4,
pin5,
pin6,
pin7
}
pinnumber_t ;

void reset_pin (portname_t portname,pinnumber_t pinnumber);
void set_pin (portname_t portname,pinnumber_t pinnumber);
void set_pin_directin (portname_t portname,pinnumber_t pinnumber,state_t state);
void write_pin (portname_t portname,pinnumber_t pinnumber,u8 outputvalue);
u8   read_u8pin (portname_t portname,pinnumber_t pinnumber);
void write_port (portname_t portname,u8 portvalue);
void write_highnibble(portname_t portname,u8 value);
void clear_high_nibble(portname_t portname);
void toggle_pin(portname_t portname,pinnumber_t pinnumber);
#endif
