/* 
 * File:   fan.h
 * Author: Mohamed_Arafa
 *
 * Created on July 2, 2021, 10:25 AM
 */

#ifndef MOTOR_H
#define	MOTOR_H
typedef enum {
            off,
            level_1,
            level_2,
            full_speed
}SPEED_LEVEL;

#define fan1_GPIO_g     GPIOB
#define fan1_pin_num_g  pin0
#define fan2_GPIO_g     GPIOB
#define fan2_pin_num_g  pin1
#define fan3_GPIO_g     GPIOD
#define fan3_pin_num_g  pin2


void 
fans_init();

void 
fans_set_speed(SPEED_LEVEL fan1_level_local,SPEED_LEVEL fan2_level_local,SPEED_LEVEL fan3_level_local);

/*
void fan2_init(portname_t GPIO,pinnumber_t pin);
void fan3_init(portname_t GPIO,pinnumber_t pin);
void heater1_init(portname_t GPIO,pinnumber_t pin);
void heater2_init(portname_t GPIO,pinnumber_t pin);

void fan1_set_speed(SPEED_LEVEL level);
void fan2_set_speed(SPEED_LEVEL level);
void fan3_set_speed(SPEED_LEVEL level);
void heater1_set_speed(SPEED_LEVEL level);
void heater2_set_speed(SPEED_LEVEL level);
*/




#endif	/* FAN_H */

