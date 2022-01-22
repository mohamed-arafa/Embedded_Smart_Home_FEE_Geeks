#include "../HELPERS/STD_TYPES.h"
#include "../MEM_MAP_AT32/Mem_map32.h"
#include "../MEM_MAP_AT32/MACROS.h"

#include "Timer0.h"
#include "GPIO_INTERFACE.h"

volatile long timer0_task_counter=0; 

static void (*timer0_ovf_ptr)(void)=NULL_PTR;
static void (*timer0_comp_ptr)(void)=NULL_PTR;

void timer0_init(TIMER0_MODE_t timer_mode,OC0_MODE_t oc_mode ,CLOCK_SELECT_t prescaler){
   
    /*******************select CLOCK SOURCE/PRESCALER FOR TIMER0 *************/
    
    TCCR0=prescaler;

    /*******************select TIMER0 mode*************/
    switch(timer_mode){                    
        case normal_mode:
            CLR_BIT(TCCR0,WGM01);
            CLR_BIT(TCCR0,WGM00);
            break;
        case phase_correct_mode:
            CLR_BIT(TCCR0,WGM01);
            SET_BIT(TCCR0,WGM00);  
            break;
        case ctc_mode:
            SET_BIT(TCCR0,WGM01);
            CLR_BIT(TCCR0,WGM00);
            break;
        case fast_pwm_mode:
            SET_BIT(TCCR0,WGM01);
            SET_BIT(TCCR0,WGM00);
            break;
        default:
            CLR_BIT(TCCR0,WGM01);
            CLR_BIT(TCCR0,WGM00);
    }
    
    /*******************select OC0 mode*************/
    switch(oc_mode){                     
            case OC0_disconnected:
            CLR_BIT(TCCR0,COM00);
            CLR_BIT(TCCR0,COM01);
            break;
            
            case OC0_toggle:
            SET_BIT(TCCR0,COM00);
            CLR_BIT(TCCR0,COM01);
            break;
            case OC0_non_inverting:
            CLR_BIT(TCCR0,COM00);
            SET_BIT(TCCR0,COM01);
            break;
            case OC0_inverting:
            SET_BIT(TCCR0,COM00);
            SET_BIT(TCCR0,COM01);
            break;
            
            default:
            CLR_BIT(TCCR0,COM00);
            CLR_BIT(TCCR0,COM01);
    }
   
}
/************enable/disable**********/
void 
timer0_OVF_interrupt_enable(){
    SET_BIT(TIMSK,TOIE0);
}

void 
timer0_OVF_interrupt_disable(){
    CLR_BIT(TIMSK,TOIE0);
}
void 
timer0_COMP_interrupt_enable(){
    SET_BIT(TIMSK,OCIE0);
}

void 
timer0_COMP_interrupt_disable(){
     CLR_BIT(TIMSK,OCIE0);
}

/***************interrupt ***************/
void timer0_OVF_setCallBack(void (*localPtr)(void)){
    timer0_ovf_ptr=localPtr;
  
}

void timer0_COMP_setCallBack(void (*localPtr)(void)){
    timer0_comp_ptr=localPtr;
  
}

ISR(TIMER0_OVF_vect){
    if(timer0_ovf_ptr!=NULL_PTR){
        timer0_ovf_ptr();
    }
}

ISR(TIMER0_COMP_vect){
    if(timer0_comp_ptr!=NULL_PTR){
        timer0_comp_ptr();
        toggle_pin(GPIOC,pin4);
    }
}