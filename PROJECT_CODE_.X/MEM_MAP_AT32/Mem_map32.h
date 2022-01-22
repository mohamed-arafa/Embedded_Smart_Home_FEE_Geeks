/*
 * Mem_map32.h
 *
 *  Created on: 5 Sep 2020
 *      Author: M
 */

#ifndef MCAL_REGISTERS_MEM_MAP32_H_
#define MCAL_REGISTERS_MEM_MAP32_H_

/* DIO_Registers */
#define DDRA (*(volatile unsigned char*)0x3A)
#define DDRB (*(volatile unsigned char*)0x37)
#define DDRC (*(volatile unsigned char*)0x34)
#define DDRD (*(volatile unsigned char*)0x31)

#define PINA (*(volatile unsigned char*)0x39)
#define PINB (*(volatile unsigned char*)0x36)
#define PINC (*(volatile unsigned char*)0x33)
#define PIND (*(volatile unsigned char*)0x30)

#define PORTA (*(volatile unsigned char*)0x3B)
#define PORTB (*(volatile unsigned char*)0x38)
#define PORTC (*(volatile unsigned char*)0x35)
#define PORTD (*(volatile unsigned char*)0x32)
/********************************************************************************************************/
/*************EXTERNAL INTERRUPT*******************/
#define MCUCR	(*(volatile unsigned char*)0x55)
#define MCUCSR	(*(volatile unsigned char*)0x54)
#define GICR	(*(volatile unsigned char*)0x5B)
#define GIFR	(*(volatile unsigned char*)0x5A)
/*********************************************************************************************************/

/************* ADC RIGISTERS *******************/

# define ADMUX   (*(volatile unsigned char*)0x27)
# define ADCSRA  (*(volatile unsigned char*)0x26)
# define ADCL  (*(volatile unsigned short*)0x24)
# define ADCH  (*(volatile unsigned short*)0x25)



/**************EEPROM*******************/
#define  EEAR (*(volatile unsigned short*)0x3E)
#define  EEDR  (*(volatile unsigned char*)0x3D)
#define  EECR  (*(volatile unsigned char*)0x3C)

/********EECR BITs *******/
#define EERIE 3
#define EEMWE 2
#define EEWE  1
#define EERE  0  

/****************Timer0*********************/
#define  TCCR0 (*(volatile unsigned char*)0x53)
#define  TCNT0 (*(volatile unsigned char*)0x52)
#define   OCR0 (*(volatile unsigned char*)0x5C)
#define  TIMSK (*(volatile unsigned char*)0x59)

/****************Timer1*********************/
#define  TCCR1A (*(volatile unsigned char*)0x4F)
#define  TCCR1B (*(volatile unsigned char*)0x4E)

#define  TCNT1 (*(volatile unsigned short*)0x4C)
#define  OCR1A (*(volatile unsigned short*)0x4A)
#define  OCR1B (*(volatile unsigned short*)0x48)
#define  ICR1  (*(volatile unsigned short*)0x46)
 
/****************** UART ************************/
/* USART Baud Rate Register Low */
#define UBRRL    (*(volatile unsigned char*)0x29)

/* USART Control and Status Register B */
#define UCSRB   (*(volatile unsigned char*)0x2A)

/* USART Control and Status Register A */
#define UCSRA    (*(volatile unsigned char*)0x2B)

/* USART I/O Data Register */
#define UDR       (*(volatile unsigned char*)0x2C)

/* USART Baud Rate Register High */
#define UBRRH    (*(volatile unsigned char*)0x40)

/* USART Control and Status Register C */
#define UCSRC     (*(volatile unsigned char*)0x40)

/* USART Register C */
#define	   URSEL		7
#define    UMSEL        6
#define    UPM1         5
#define    UPM0         4
#define    USBS         3
#define    UCSZ1        2
#define    UCSZ0        1
#define    UCPOL        0

/* USART Status Register A  */
#define    RXC          7
#define    TXC          6
#define    UDRE         5
#define    FE           4
#define    DOR          3
#define    UPE          2
#define    U2X          1
#define    MPCM         0
/* USART Control Register B  */
#define    RXCIE        7
#define    TXCIE        6
#define    UDRIE        5
#define    RXEN         4
#define    TXEN         3
#define    UCSZ         2
#define    UCSZ2        2
#define    RXB8         1
#define    TXB8         0


/******************INTERRUPT*********************/

#define SREG    (*(volatile unsigned char*)0X5F)


#define ISR(VECTOR,...) \
	void VECTOR(void) __attribute__((signal))__VA_ARGS__;\
	void VECTOR(void)
#define sei() __asm__ __volatile__ ("sei" ::)
#define cli() __asm__ __volatile__ ("cli" ::)	
	
/*****************vector table *****************/
#define INT0_vect			 __vector_1 	//	External Interrupt Request 0
#define INT1_vect 			 __vector_2 	//External Interrupt Request 1
#define INT2_vect 			 __vector_3 	//External Interrupt Request 2
#define TIMER2_COMP_vect 	 __vector_4 	//	Timer/Counter2 Compare Match
#define TIMER2_OVF_vect 	 __vector_5 	//	Timer/Counter2 Overflow
#define TIMER1_CAPT_vect 	 __vector_6 	//	Timer/Counter1 Capture Event
#define TIMER1_COMPA_vect 	 __vector_7 	//Timer/Counter1 Compare Match A
#define TIMER1_COMPB_vect 	 __vector_8 	//Timer/Counter1 Compare Match B
#define TIMER1_OVF_vect 	 __vector_9 	//	Timer/Counter1 Overflow
#define TIMER0_COMP_vect 	 __vector_10	//Timer/Counter0 Compare Match
#define TIMER0_OVF_vect 	 __vector_11	//	Timer/Counter0 Overflow
#define SPI_vect 			 __vector_12	//Serial Transfer Complete
#define RXC_vect 			 __vector_13	//	USART, Rx Complete
#define UDRE_vect 			 __vector_14	//USART Data Register Empty
#define TXC_vect 			 __vector_15	//	USART, Tx Complete
#define ADC_vect 			 __vector_16	//ADC Conversion Complete
#define EE_RDY_vect 		 __vector_17	//	EEPROM Ready
#define ANA_COMP_vect 		 __vector_18	//Analog Comparator
#define TWI_vect 			 __vector_19    //Two-wire Serial Interface
#define SPM_RDY_vect 	 	 __vector_20    // Store Program Memory Ready
/************************************************************************************************************/





#endif /* MCAL_REGISTERS_MEM_MAP32_H_ */
