#include "External_intrrupt_Atmega32H.h"

static void (*EX_INT0_ptr)(void)=NULL_PTR;
static void (*EX_INT1_ptr)(void)=NULL_PTR;
static void (*EX_INT2_ptr)(void)=NULL_PTR;


void 
init_ex_interrupt(EX_INT_t  ex_int, EX_INT_MODE_t  mode){
	switch(ex_int){
		case EX_INT0:
			MCUCR =(MCUCR & 0XFC )| mode;		break;
		case EX_INT1:
			MCUCR =(MCUCR & 0XF3 )| (mode<<2);	break;
		 case EX_INT2:
			if(mode==falling_edge)
				CLR_BIT(MCUCSR,ISC2);
			else if (mode==rising_edge)
				SET_BIT(MCUCSR,ISC2);
			else{
				
				}
	}
}

void 
enable_ex_interrupt(EX_INT_t  ex_int){
	switch(ex_int){
		case EX_INT0:
			SET_BIT(GICR , INT0);	break;
		case EX_INT1:
			SET_BIT(GICR , INT1);	break;
		case EX_INT2:
			SET_BIT(GICR , INT2);	break;
		}
}

void 
disable_ex_interrupt(EX_INT_t  ex_int){
	switch(ex_int){
		case EX_INT0:
			CLR_BIT(GICR , INT0);	break;
		case EX_INT1:
			CLR_BIT(GICR , INT1);	break;
		case EX_INT2:
			CLR_BIT(GICR , INT2);	break;
		}	
}

u8 
read_ex_interrupt_flag(EX_INT_t  ex_int){
	u8 flag_status=0;
	switch(ex_int){
		case EX_INT0:
			flag_status= GET_BIT(GIFR , INTF0);	break;
		case EX_INT1:
			flag_status= GET_BIT(GIFR , INTF1);	break;
		case EX_INT2:
			flag_status= GET_BIT(GIFR , INTF2);	break;
		}
return flag_status;
}

void
EX_setCallBack(EX_INT_t ex_int ,void (*local_ptr)(void))
{
	switch(ex_int){
		case EX_INT0:
			EX_INT0_ptr=local_ptr; break;
		case EX_INT1 :
			EX_INT1_ptr=local_ptr; break;
		case EX_INT2:
			EX_INT2_ptr=local_ptr; break;	
	}
}


ISR(INT0_vect){
	if (EX_INT0_ptr!=NULL_PTR)
	{
		EX_INT0_ptr();
	}
}

ISR(INT1_vect){
	if (EX_INT1_ptr!=NULL_PTR)
	{
		EX_INT1_ptr();
	}
}	

ISR(INT2_vect){
	if (EX_INT2_ptr!=NULL_PTR)
	{
		EX_INT2_ptr();
	}	
}

