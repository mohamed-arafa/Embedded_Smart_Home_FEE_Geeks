#ifndef REPO_HAL_LCD_LCD_H_
#define REPO_HAL_LCD_LCD_H_

#include "../MCAL/GPIO_INTERFACE.h"
#include "../HELPERS/STD_TYPES.h"
#include "../MEM_MAP_AT32/MACROS.h"
#include "../MEM_MAP_AT32/Mem_map32.h"
#define F_CPU 8000000UL

#include <util/delay.h>


#define CLR_SCREEN           0X01
#define DISPLAY_ON_CURSOR_ON 0X0E

#define FOUR_BIT_MODE		 0X28
#define LCD_PORT			 GPIOB
#define LCD_CONTROL_PORT	 GPIOB 
#define LCD_EN_PIN			 pin3
//#define LCD_RW_PIN			 pin0
#define LCD_RS_PIN			 pin2



void LCD_Initial(void);
void LCD_Cmd(u8 cmd);
void LCD_char(u8 data);
void LCD_string(u8 *str);
void LCD_clearscreen(void);
void LCD_cursor(u8 row, u8 coloumn);

#endif // REPO_HAL_LCD_LCD_H_