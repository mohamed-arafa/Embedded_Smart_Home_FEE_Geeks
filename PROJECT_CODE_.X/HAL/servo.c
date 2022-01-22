#include "../MCAL/GPIO_INTERFACE.h"
#include "../MCAL/Timer1.h"
#include "servo.h"



void servo_init(void){
    set_pin_directin(servo_gpio,servo_pin,OUTPUT);
    ICR1=19999;
    timer1_init(fast_pwm_top_icr1,OCA_non_inverting,OCB_inverting,timer1_pre_8);

}


void servo_set_angle(u8 angle){    
    OCR1A=999+((u32)angle*1000)/180;
    OCR1B=999+((u32)angle*1000)/180;
    
}

 