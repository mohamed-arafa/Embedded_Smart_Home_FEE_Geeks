/* 
 * File:   Timer0.h
 * Author: Mohamed_Arafa
 *
 * Created on June 30, 2021, 11:35 PM
 */

#ifndef TIMER0_H
#define	TIMER0_H


typedef enum{
            normal_mode=0,
            phase_correct_mode,
            ctc_mode,
            fast_pwm_mode
}TIMER0_MODE_t;


typedef enum{
            OC0_disconnected=0,
            OC0_toggle,
            OC0_non_inverting,
            OC0_inverting
}OC0_MODE_t;


typedef enum{
            timer0_stop=0,
            timer0_pre_1,
            timer0_pre_8,
            timer0_pre_64,
            timer0_pre_256,
            timer0_pre_1024,
            timer0_external_falling,
            timer0_external_rising,
}CLOCK_SELECT_t;

/*************TIMSK_bits*******/

#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0

/*************TCCR0_bits*******/
#define FOC0  7  
#define WGM00 6
#define COM01 5
#define COM00 4
#define WGM01 3
#define CS01  1
#define CS00  0


void timer0_init(TIMER0_MODE_t timer_mode,OC0_MODE_t oc_mode ,CLOCK_SELECT_t prescaler);

void timer0_OVF_interrupt_disable();
void timer0_OVF_interrupt_enable();

void timer0_COMP_interrupt_disable();
void timer0_COMP_interrupt_enable();
     
void timer0_OVF_setCallBack( void (*localPtr)(void));
void timer0_COMP_setCallBack( void (*localPtr)(void));

#endif	/* TIMER0_H */

