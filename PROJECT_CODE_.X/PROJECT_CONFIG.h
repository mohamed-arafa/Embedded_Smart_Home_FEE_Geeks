/* 
 * File:   PROJECT_CONFIG.h
 * Author: Mohamed_Arafa
 *
 * Created on April 26, 2021, 12:36 PM
 */
#ifndef PROJECT_CONFIG_H
#define	PROJECT_CONFIG_H

#define F_CPU 8000000

#include <util/delay.h>
#include "MCAL/GPIO_INTERFACE.h"
//#include "MCAL/ADC_Function.h"
#include "MCAL/UART_driver.h"
//#include "MCAL/External_intrrupt_Atmega32H.h"

#include "HAL/LCD.h"
#include "HAL/servo.h"

#define leds_port PORTA
#define LED_1   0
#define LED_2   1
#define LED_3   2
#define LED_4   3
#define LED_5   4
#define LED_6   5

#define fans_port GPIOD
#define fan_1   5
#define fan_2   6
#define fan_3   7

#define door_port GPIOD
#define door_pin0 3
#define door_pin1 2

#define pir_port GPIOD
#define pir_pin  3

#define gas_port GPIOD
#define gas_pin  4

#define led_buzzer_port GPIOD
#define led_buzzer_fire 7
/**********EEPROM */
#define first_use_f_adr 0x30
#define packup_adr  0x31
#define pass_adr    33

#endif	/* PROJECT_CONFIG_H */
