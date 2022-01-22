/*
 * File:   main.c
 * Author: Mohamed_Arafa
 *
 * Created on April 13, 2021, 2:18 PM
 */


#include "PROJECT_CONFIG.h"

u8 task_queu[20];
u8 push_var = 0;
u8 pop_var = 0;

u8 command;
u8 lcd_status;

void main(void) {
    init_ex_interrupt(EX_INT0, falling_edge);
    enable_ex_interrupt(EX_INT0);
    EX_setCallBack(fire_off);


    DDRB = 0xff;

    while (1) {
		//recieve IP
		
		
		//recieve command

        task_excution(command);
        if (gas_read() > 180) {
            set_pin(GPIOD, led_buzzer_fire);

            delay_ms(20);
            if (gas_read() < 180) { //retest

                reset_pin(GPIOD, led_buzzer_fire);
			
            }
				//Notification
        }

        return;
    }
}

void fan_speed(u8 speed, u8 fan_number) {
    //uncompleted
}

void door_open_off(u8 door_status) {
    //uncompleted
}

void fire_off() {
    reset_pin(GPIOD, led_buzzer_fire);
}

u8 gas_read() {
    return read_ADC();
}

void task_excution(u8 command) {

    switch (command) {
        case 1:
            LED_1 = ON;
            break;

        case 2:
            LED_2 = ON;
            break;
        case 3:
            LED_3 = ON;
            break;
        case 4:
            LED_4 = ON;
            break;
        case 5:
            LED_5 = ON;
            break;
        case 6:
            LED_1 = OFF;
        case 7:
            LED_2 = OFF;
            break;
        case 8:
            LED_3 = OFF;
            break;
        case 9:
            LED_4 = OFF;
            break;
        case 10:
            LED_5 = OFF;
            break;
        case 11:
            fan_speed(0, fan_1);
            break;
        case 12:
            fan_speed(1, fan_1);
            break;
        case 13:
            fan_speed(2, fan_1);
            break;
        case 14:
            fan_speed(3, fan_1);
            break;
        case 15:
            fan_speed(4, fan_1);
            break;
        case 16:
            fan_speed(0, fan_2);
            break;
        case 17:
            fan_speed(1, fan_2);
            break;
        case 18:
            fan_speed(2, fan_2);
            break;
        case 19:
            fan_speed(3, fan_2);
            break;
        case 20:
            fan_speed(4, fan_2);
            break;
        case 21:
            door_open_off(ON);
            break;
        case 22:
            door_open_off(OFF);
            break;
        case 23:
            lcd_status = OFF;
            break;
        case 24:
            lcd_status = ON;
            break;
    }
}

void push_into_queu(u8 data) {
    if(push_var==20){
        push_var=0;
       
    }
    task_queu[push_var];
    ++push_var;
}

u8 pop_outof_queu() {
    if(pop_var==20){
         pop_var=0;
    }
    if (pop_var < push_var) {
        u8 data = task_queu[pop_var];
        ++pop_var;
        return data;
    } else
        return 0;
}
