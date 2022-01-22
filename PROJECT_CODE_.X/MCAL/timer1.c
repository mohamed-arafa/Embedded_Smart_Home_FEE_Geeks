
#include "../HELPERS/STD_TYPES.h"
#include "../MEM_MAP_AT32/MACROS.h"
#include"../MEM_MAP_AT32/Mem_map32.h"
#include "timer1.h"

static void (*timer1_compa_ptr)(void)=NULL_PTR;
static void (*timer1_compb_ptr)(void)=NULL_PTR;
static void (*timer1_ovf_ptr)(void)=NULL_PTR;

void 
timer1_init(TIMER1_MODE_t timer_mode,OC1A_MODE_t oc1A_mode ,OC1B_MODE_t oc1B_mode ,TIMER1_CLOCK_SELECT_t prescaler){  
    
    /*******************select CLOCK SOURCE/PRESCALER FOR timer1 *************/
    
    TCCR1B=prescaler;

    /*******************select timer1 mode*************/
    switch(timer_mode){                    
        case normal_top_max_mode:
            CLR_BIT(TCCR1A,WGM10);
            CLR_BIT(TCCR1A,WGM11);
            CLR_BIT(TCCR1B,WGM12);
            CLR_BIT(TCCR1B,WGM13);
            break;
        case phase_correct_top_0xff_mode:
            SET_BIT(TCCR1A,WGM10);
            CLR_BIT(TCCR1A,WGM11);
            CLR_BIT(TCCR1B,WGM12);
            CLR_BIT(TCCR1B,WGM13); 
            break;
        case phase_correct_top_0x1ff_mode:
            CLR_BIT(TCCR1A,WGM10);
            SET_BIT(TCCR1A,WGM11);
            CLR_BIT(TCCR1B,WGM12);
            CLR_BIT(TCCR1B,WGM13); 
            break;
        case phase_correct_top_0x3ff_mode:
            SET_BIT(TCCR1A,WGM10);
            SET_BIT(TCCR1A,WGM11);
            CLR_BIT(TCCR1B,WGM12);
            CLR_BIT(TCCR1B,WGM13); 
            break;
        case ctc_top_ocr1a_mode:
            CLR_BIT(TCCR1A,WGM10);
            CLR_BIT(TCCR1A,WGM11);
            SET_BIT(TCCR1B,WGM12);
            CLR_BIT(TCCR1B,WGM13); 
            break;
        case fast_pwm_top_0xff_mode:
           SET_BIT(TCCR1A,WGM10);
            CLR_BIT(TCCR1A,WGM11);
            SET_BIT(TCCR1B,WGM12);
            CLR_BIT(TCCR1B,WGM13); 
            break;
        case fast_pwm_0x1ff_mode:
            CLR_BIT(TCCR1A,WGM10);
            SET_BIT(TCCR1A,WGM11);
            SET_BIT(TCCR1B,WGM12);
            CLR_BIT(TCCR1B,WGM13); 
            break;
        case fast_pwm_0x3ff_mode:
            SET_BIT(TCCR1A,WGM10);
            SET_BIT(TCCR1A,WGM11);
            SET_BIT(TCCR1B,WGM12);
            CLR_BIT(TCCR1B,WGM13); 
            break;
        case phase_freq_correct_top_icr1_mode:
            CLR_BIT(TCCR1A,WGM10);
            CLR_BIT(TCCR1A,WGM11);
            CLR_BIT(TCCR1B,WGM12);
            SET_BIT(TCCR1B,WGM13); 
            break;
        case phase_freq_correct_top_ocr1a_mode:
            SET_BIT(TCCR1A,WGM10);
            CLR_BIT(TCCR1A,WGM11);
            CLR_BIT(TCCR1B,WGM12);
            SET_BIT(TCCR1B,WGM13); 
            break;
        case phase_correct_top_icr1_mode:
            CLR_BIT(TCCR1A,WGM10);
            SET_BIT(TCCR1A,WGM11);
            CLR_BIT(TCCR1B,WGM12);
            SET_BIT(TCCR1B,WGM13); 
            break;
        case phase_correct_top_ocr1a_mode:
           SET_BIT(TCCR1A,WGM10);
            SET_BIT(TCCR1A,WGM11);
            CLR_BIT(TCCR1B,WGM12);
            SET_BIT(TCCR1B,WGM13); 
            break;
        case ctc_top_icr1:
            CLR_BIT(TCCR1A,WGM10);
            CLR_BIT(TCCR1A,WGM11);
            SET_BIT(TCCR1B,WGM12);
            SET_BIT(TCCR1B,WGM13); 
            break;
        case fast_pwm_top_icr1:
            CLR_BIT(TCCR1A,WGM10);
            SET_BIT(TCCR1A,WGM11);
            SET_BIT(TCCR1B,WGM12);
            SET_BIT(TCCR1B,WGM13); 
            break;
        case fast_pwm_top_ocr1a:
            SET_BIT(TCCR1A,WGM10);
            SET_BIT(TCCR1A,WGM11);
            SET_BIT(TCCR1B,WGM12);
            SET_BIT(TCCR1B,WGM13); 
            break;
            
        default:
            CLR_BIT(TCCR1A,WGM10);
            CLR_BIT(TCCR1A,WGM11);
            CLR_BIT(TCCR1B,WGM12);
            CLR_BIT(TCCR1B,WGM13); 
    }
    
    /*******************select OC0 mode*************/
    switch(oc1A_mode){                     
        case OCA_disconnected:
            CLR_BIT(TCCR1A,COM1A0);
            CLR_BIT(TCCR1A,COM1A1);
            break;
            
        case OCA_toggle:
            SET_BIT(TCCR1A,COM1A0);
            CLR_BIT(TCCR1A,COM1A1);
            break;
        case OCA_non_inverting:
            CLR_BIT(TCCR1A,COM1A0);
            SET_BIT(TCCR1A,COM1A1);
            break;
        case OCA_inverting:
            SET_BIT(TCCR1A,COM1A0);
            SET_BIT(TCCR1A,COM1A1);
            break;
            
        default:
            CLR_BIT(TCCR1A,COM1A0);
            CLR_BIT(TCCR1A,COM1A1);
    }
        switch(oc1B_mode){                     
        case OCB_disconnected:
            CLR_BIT(TCCR1A,COM1B0);
            CLR_BIT(TCCR1A,COM1B1);
            break;
            
        case OCB_toggle:
            SET_BIT(TCCR1A,COM1B0);
            CLR_BIT(TCCR1A,COM1B1);
            break;
        case OCB_non_inverting:
            CLR_BIT(TCCR1A,COM1B0);
            SET_BIT(TCCR1A,COM1B1);
            break;
        case OCB_inverting:
            SET_BIT(TCCR1A,COM1B0);
            SET_BIT(TCCR1A,COM1B1);
            break;
            
        default:
            CLR_BIT(TCCR1A,COM1B0);
            CLR_BIT(TCCR1A,COM1B1);
    }
   
}
   




/************enable/disable**********/

void 
timer1_OVF_interrupt_enable(){
    SET_BIT(TIMSK,TOIE1);
}

void 
timer1_OVF_interrupt_disable(){
    CLR_BIT(TIMSK,TOIE1);
}

void 
timer1_COMPB_interrupt_enable(){
    SET_BIT(TIMSK,OCIE1B);
}

void 
timer1_COMPB_interrupt_disable(){
     CLR_BIT(TIMSK,OCIE1B);
}
void 
timer1_COMPA_interrupt_enable(){
    SET_BIT(TIMSK,OCIE1A);
}

void 
timer1_COMPA_interrupt_disable(){
     CLR_BIT(TIMSK,OCIE1A);
}

/***************interrupt **************/

void timer1_OVF_setCallBack(void (*localPtr)(void)){
    timer1_ovf_ptr=localPtr;
  
}

void timer1_COMPA_setCallBack(void (*localPtr)(void)){
    timer1_compa_ptr=localPtr;
  
}

void timer1_COMPB_setCallBack(void (*localPtr)(void)){
    timer1_compb_ptr=localPtr;
  
}



/**************ISR****************/
ISR(TIMER1_OVF_vect){
    if(timer1_ovf_ptr!=NULL_PTR){
        timer1_ovf_ptr();
    }
}

ISR(TIMER1_COMPA_vect){
    if(timer1_compa_ptr!=NULL_PTR){
        timer1_compa_ptr();
    }
}

ISR(TIMER1_COMPB_vect){
    if(timer1_compb_ptr!=NULL_PTR){
        timer1_compb_ptr();
    }
}
