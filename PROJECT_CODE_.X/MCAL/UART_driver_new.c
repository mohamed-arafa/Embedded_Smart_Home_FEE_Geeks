#include "UART_driver.h"


volatile u8 text_global;
volatile u8* g_finish_recieve_f;
static void(*TX_Ptr)(void) = NULL_PTR ; 
static void(*RX_Ptr)(void) = NULL_PTR ; 
static char* str_send_temp ;   
static char* str_recieve_temp ;

 volatile u8 test=0;

u8 UART_Recieve_Byte_g(){
    return test;
}
void UART_init(u16 baud_rate , u32 FOSC)
{
    u8 UCSRC_var=0;
	//CLR_BIT(UCSRC,URSEL);
	u16 baud_value = (u16) ( (FOSC / (16*baud_rate) ) - 1) ;
	//UBRRH = (u8)(baud_value>>8);
	UBRRH =0;
    UBRRL =0x33; 
    // configuration of control registers   
	SET_BIT(UCSRC_var,URSEL);
	SET_BIT(UCSRB,RXCIE);     // enable RX interrupt
	CLR_BIT(UCSRC_var,USBS);      // one stop bit
	CLR_BIT(UCSRC_var,UMSEL);     // asynchronous mode 
	//character size 8 bit
	CLR_BIT(UCSRB,UCSZ2);
	SET_BIT(UCSRC_var,UCSZ1);
	SET_BIT(UCSRC_var,UCSZ0);
	
    UCSRC=UCSRC_var;
    // no parity mode
	CLR_BIT(UCSRB,UPM0);
	CLR_BIT(UCSRB,UPM1);
	//Enable Protocol
	
	SET_BIT(UCSRB,RXEN);      // enable RX pin
	SET_BIT(UCSRB,TXEN);      // enable TX pin
}

void UART_Send_Byte(u8 value)
{
    while(!GET_BIT(UCSRA,UDRE));
	UDR = value ;
}


void UART_send_string(char *sentence)
{
    volatile u8 i=0;
    UART_Send_Byte(sentence[i]);
        
    for (i=1;sentence[i]!='\0';++i){
        UART_Send_Byte(sentence[i]);   
    }
    
}


/**********send with no block****************/
void UART_Send_Byte_noblock(u8 value)
{
	UDR = value ;
}

void UART_send_string_noblock(char *sentence)
{   
    UART_Enable_Transmision();
    UART_Enable_TXINT();
	UART_Send_Byte_noblock(sentence[0]);
	str_send_temp = sentence ;
	TX_SetCallBack(TX_Func);
}

void TX_Func(void)
{
    test++;
    static u16 c = 1 ;
	if(str_send_temp[c] != '\0')
	{
		UART_Send_Byte_noblock(str_send_temp[c]);
		c++;
        
	}	
	else
	{
		 UART_Send_Byte_noblock('\0');        
		 c = 1 ;
		 str_send_temp = NULL_PTR ; 
	     UART_Disable_Transmision();
    }
}

char UART_Recieve_Byte(void)
{
	while(!(GET_BIT(UCSRA,RXC)));  
    CLR_BIT(UCSRA,RXC);
    return UDR;
}
void UART_recieve_string(char* recieved_sentence)
{
	u8 i=0;
    recieved_sentence[i]=UART_Recieve_Byte();
    while(recieved_sentence[i]!='\0'){
        ++i;
        recieved_sentence[i]=UART_Recieve_Byte();
    }
    recieved_sentence[i]='\0';
}

char UART_Recieve_Byte_noblock(void)
{
    CLR_BIT(UCSRA,RXC);
	return UDR ;
}
void UART_recieve_string_noblock(char* recieved_sentence,u8 *l_receive_finish_f)
{
	str_recieve_temp = recieved_sentence ;
	UART_Enable_RECIEVE();
    UART_Enable_RXINT();
    g_finish_recieve_f=l_receive_finish_f;
	RX_SetCallBack(RX_Func);
}
void RX_Func(void)
{
    *g_finish_recieve_f=0;                      // mcu is in receiving state 
	static u16 i = 0 ;
	str_recieve_temp[i] = UART_Recieve_Byte();
	if(i==1)             
	{   
        *g_finish_recieve_f=1;                  // mcu finished receiving
		//str_recieve_temp[i] = '#';
        i = 0 ;
        
	}
	else
	{
		i++ ;
	}	
    
}
/**********************         interrupt     ******************/
void UART_Enable_RECIEVE(void)
{
   SET_BIT(UCSRB,RXEN);     // enable RX interrupt	
}
void UART_Disable_RECIEVE(void)
{
	CLR_BIT(UCSRB,RXEN);     // disable RX interrupt
}

void UART_Enable_RXINT(void)
{
   SET_BIT(UCSRB,RXCIE);     // enable RX interrupt	
}
void UART_Disable_RXINT(void)
{
	CLR_BIT(UCSRB,RXCIE);     // disable RX interrupt
}
void UART_Enable_TXINT(void)
{
	SET_BIT(UCSRB,TXCIE);     // enable TX interrupt
}
void UART_Disable_TXINT(void)
{
	CLR_BIT(UCSRB,TXCIE);     // disable TX interrupt
}

void UART_Enable_Transmision(void)
{
	SET_BIT(UCSRB,TXEN);     // enable TX interrupt
}
void UART_Disable_Transmision(void)
{
	CLR_BIT(UCSRB,TXEN);     // disable TX interrupt
}

void TX_SetCallBack(void(*LocalPtr)(void))
{
	TX_Ptr = LocalPtr ;	
}
ISR(TXC_vect)
{
	if(TX_Ptr!= NULL_PTR)
	{
		TX_Ptr();
	}
}
void RX_SetCallBack(void(*LocalPtr)(void))
{
	RX_Ptr = LocalPtr ;
}
ISR(RXC_vect)
{
	if(RX_Ptr!= NULL_PTR)
	{
		RX_Ptr();
	}
}
