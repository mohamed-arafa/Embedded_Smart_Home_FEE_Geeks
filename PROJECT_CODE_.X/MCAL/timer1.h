/* 
 * File:   timer1.h
 * Author: Mohamed_Arafa
 *
 * Created on June 30, 2021, 11:35 PM
 */

#ifndef TIMER1_H
#define	TIMER1_H
#include "Timer0.h"
typedef enum{
            normal_top_max_mode=0,
            phase_correct_top_0xff_mode,
            phase_correct_top_0x1ff_mode,
            phase_correct_top_0x3ff_mode,
            ctc_top_ocr1a_mode,
            fast_pwm_top_0xff_mode,
            fast_pwm_0x1ff_mode,
            fast_pwm_0x3ff_mode,
            phase_freq_correct_top_icr1_mode,
            phase_freq_correct_top_ocr1a_mode,
            phase_correct_top_icr1_mode,        
            phase_correct_top_ocr1a_mode,        
            ctc_top_icr1,
            reserved,
            fast_pwm_top_icr1,
            fast_pwm_top_ocr1a

}TIMER1_MODE_t;


typedef enum{
            OCB_disconnected=0,
            OCB_toggle,
            OCB_non_inverting,
            OCB_inverting
}OC1B_MODE_t;


typedef enum{
            OCA_disconnected=0,
            OCA_toggle,
            OCA_non_inverting,
            OCA_inverting
}OC1A_MODE_t;

typedef enum{
            timer1_stop=0,
            timer1_pre_1,
            timer1_pre_8=2,
            timer1_pre_64,
            timer1_pre_256,
            timer1_pre_1024,
            timer1_external_falling,
            timer1_external_rising,
}TIMER1_CLOCK_SELECT_t;

/*************TIMSK_bits*******/
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0

/*************TCCR1A_bits*******/
#define COM1A1 7
#define COM1A0 6
#define COM1B1 5
#define COM1B0 4
#define FOC1A  3
#define FOC1B  2
#define WGM11  1
#define WGM10  0


/*************TCCR1B_bits*******/
#define ICNC1 7
#define ICES1 6

#define WGM13  4
#define WGM12  3
#define CS12   2
#define CS11   1
#define CS10   0

void 
timer1_init(TIMER1_MODE_t timer_mode,OC1A_MODE_t oc1A_mode ,OC1B_MODE_t oc1B_mode ,TIMER1_CLOCK_SELECT_t prescaler);

/************enable/disable**********/
void 
timer1_OVF_interrupt_enable();
void 
timer1_OVF_interrupt_disable();
void 
timer1_COMPB_interrupt_enable();
void 
timer1_COMPB_interrupt_disable();
void 
timer1_COMPA_interrupt_enable();
void 
timer1_COMPA_interrupt_disable();

/*************** setCallBack **************/

void timer1_OVF_setCallBack(void (*localPtr)(void));
void timer1_COMPA_setCallBack(void (*localPtr)(void));
void timer1_COMPB_setCallBack(void (*localPtr)(void));


#endif	/* timer1_H */

