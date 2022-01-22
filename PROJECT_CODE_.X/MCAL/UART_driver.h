#ifndef UART_H_
#define UART_H_

#include "../MEM_MAP_AT32/MACROS.h"
#include "../MEM_MAP_AT32/Mem_map32.h"
#include "../HELPERS/STD_TYPES.h"

u8 UART_Recieve_Byte_g();
void UART_init(u16 baud_rate , u32 FOSC);
void UART_Send_Byte(u8 value);
void UART_send_string(char* sentence);
void UART_Send_Byte_noblock(u8 value);
void UART_send_string_noblock(char *sentence);
char UART_Recieve_Byte(void);
void TX_Func(void);
void RX_Func(void);
void TX_SetCallBack(void(*LocalPtr)(void));
void RX_SetCallBack(void(*LocalPtr)(void));

void UART_recieve_string(char* recieved_sentence);

void UART_Enable_RXINT(void);
void UART_Disable_RXINT(void);
void UART_Enable_TXINT(void);
void UART_Disable_TXINT(void);

void UART_Enable_RECIEVE(void);
void UART_Disable_RECIEVE(void);

void UART_Disable_Transmision(void);
void UART_Enable_Transmision(void);
#endif