
#define F_CPU 8000000UL

#include"util/delay.h"


#include "HELPERS/STD_TYPES.h"
#include "MEM_MAP_AT32/MACROS.h"
#include "HAL/LCD.h"
#include "MCAL/GPIO_INTERFACE.h"
#include "HAL/motor.h"
#include "HAL/servo.h"
#include "MCAL/Timer0.h"
#include "MCAL/UART_driver.h"
#include<stdio.h>
#include <math.h>
#include "PROJECT_CONFIG.h"
#include"MCAL/EEPROM.h"
#include "HAL/servo.h"
#include "HAL/keypad_e.h"

//#include "MCAL/ADC_Function.h"

u8 read_sensors();
void take_action(u16 command);
void door_open();
void door_close();
void Check_Password(void);
void Get_Password(u8* text);
void Enter_1st_pass();
void Change_pass();
// strings for comunication
u8 txt_received[5] = "a";
u8 txt_sent[4] = "a";

//the command received
u16 command_to_done = 0x00;

//eeprom flag of first use

u8 first_use_f_data = 0xff;

//eeprom data for packup

u8 packup_data_L = 0xff;
u8 packup_data_H = 0xff;
u16 packup_data = 0xff;

u8 sensors_status = 0;
u8 sensors_status_new = 0;

/*u8 stringtoint(char* text) {

    u8 size;
    for (size = 1; text[size] != '\0'; size++);
    u8 num = 0;
    u8 j;
    for (j = 0; j < size; j++) {
        num += ((text[size - j - 1] - '0') * pow(10, j));
    }
    return num;
}*/
volatile u8 finish_receiving_f = 0;


int main() {
    DDRA = 0xff;
    PORTA = 0;
    DDRD = 0b11000111;
    DDRB=0x03;
    UART_init(9600, 8000000);
 //   fans_init();
    servo_init();

    LCD_Initial();
    keypad_init();

    sei();
    //    _delay_ms(2000);
    //fans_set_speed(0, 0, 0);
    CLR_BIT(EECR, EEWE);
    first_use_f_data = eeprom_read_char(first_use_f_adr);
    if (first_use_f_data == 0xff) {
        take_action((u16) 0); //all is off

        Enter_1st_pass();
        eeprom_write_char(0, first_use_f_adr);

    } else {
        packup_data_H = eeprom_read_char(packup_adr);
        packup_data_L = eeprom_read_char(packup_adr + 1);
        packup_data = (u16) packup_data_L | (packup_data_H << 8);
        LCD_cursor(0, 0);
        Check_Password();
        LCD_clearscreen();
        Change_pass();
        LCD_clearscreen();
        take_action(packup_data&0x00ff);
    }
    
    PORTA=0x00;
    sei();

    while(1){

        sensors_status_new = read_sensors();
        if (sensors_status_new != sensors_status) {
            UART_Send_Byte(sensors_status_new + 48);
            UART_Send_Byte('\0');
            LCD_cursor(1, 0);
            LCD_char(sensors_status_new + 48);
            sensors_status = sensors_status_new;
            if(sensors_status==2||sensors_status==0)
                set_pin(led_buzzer_port,led_buzzer_fire);
            else 
                reset_pin(led_buzzer_port,led_buzzer_fire);
        }

        UART_recieve_string_noblock(txt_received, &finish_receiving_f);
        if (finish_receiving_f){
            finish_receiving_f = 0;
            command_to_done = (u16) txt_received[1] | ((u16) txt_received[0] << 8);
            take_action(command_to_done);
            eeprom_write_char(txt_received[1], packup_adr);
            eeprom_write_char(txt_received[0], packup_adr + 1);
        }
    }
}

u8 read_sensors() {
    u8 data = 0;
    data = read_u8pin(pir_port, pir_pin);
    data = data << 1;

    data |= read_u8pin(gas_port, gas_pin);
    return data;
}

void take_action(u16 command) {
    LCD_cursor(0, 0);
    LCD_char((u8) command);
    LCD_char((u8) (command >> 8));

    u8 leds_data = 0;
    u8 door_status_new = 0;
    volatile u8 door_status = eeprom_read_char((u16)0x0050);
    u8 fan1_var, fan2_var, fan3_var = 0;

    // extract binary data
    leds_data = (u8) command & 0x00ff;
    fan1_var = ((u16) command >> 8) & 0x0003;
    fan2_var = ((u16) command >> 8) & 0x000c;
    //fan3_var = ((u16) command >> 12) & 0x003;
    door_status_new = ((u16) command >> 12) & 0x0001;

    // apply the action
    leds_port = leds_data; //LEDs
    
    if(fan1_var==0)
        reset_pin(GPIOB,0);
    else
        set_pin(GPIOB,0);
     if(fan2_var==0)
        reset_pin(GPIOB,1);
     else
        set_pin(GPIOB,1);
    
    if (door_status_new != door_status) { //door
        if (door_status_new == 1) { //DOOR
            door_open();
        } else {
            door_close();
        }
        eeprom_write_char(door_status_new,(u16) 0x0050);
    }

}

void door_open() {
    servo_set_angle(150);
}

void door_close() {
    servo_set_angle(0);
}

void Get_Password(u8* text) {
    u8 i = 0;
    LCD_cursor(1, 1);
    LCD_string((u8 *) ("               "));
    for (i = 0; i < 4; i++) {
        do {
            text[i] = keypad_scan();
        } while (text[i] == 0);
        LCD_cursor(1, i);
        LCD_char(text[i]);

        _delay_ms(50);
        LCD_cursor(1, i);
        LCD_char('*');
    }
    text[i] = '\0';
    LCD_cursor(0, 1);

}

void Enter_1st_pass() {
    u8 saved_pass[5] = " ";
    LCD_cursor(0, 2);
    LCD_string((u8*) "Enter Pass");
    Get_Password(saved_pass);
    u8 i = 0;
    for (; i < 4; i++) {
        eeprom_write_char(*(saved_pass + i), pass_adr + i);
    }
    LCD_clearscreen();
    LCD_cursor(0, 5);
    LCD_string((u8 *) ("Welcome"));
}

void Check_Password(void) {
    u8 text[5] = " ";
    u8 saved_pass[5] = " ";
    u8 entered_pass[5] = "  ";

    u8 i = 0;
    for (; i < 4; i++) {
        *(saved_pass + i) = eeprom_read_char(pass_adr + i);
    }

    u8 flag = 0;
    while (1) {
        LCD_cursor(0, 2);
        LCD_string((u8*) "Enter Pass");
        Get_Password(entered_pass);
        for (i = 0; i < 4; i++) {
            if (*(entered_pass + i) != *(saved_pass + i)) {
                flag++;
                break;
            }
        }

        if (flag == 0 || i == 4) {
            LCD_clearscreen();
            LCD_cursor(0, 5);
            LCD_string((u8 *) ("Welcome"));
            flag = 0;
            _delay_ms(1000);
            return;
        } else if (flag == 1) {
            LCD_clearscreen();
            LCD_cursor(0, 2);
            LCD_string((u8 *) ("Wrong Pass #1"));
            _delay_ms(1000);
            LCD_clearscreen();
        } else {
            LCD_clearscreen();
            LCD_cursor(0, 2);
            LCD_string((u8 *) ("Wrong Pass #2"));
            _delay_ms(1000);
            LCD_clearscreen();
            LCD_cursor(0, 2);
            LCD_string((u8 *) ("Log Out ..."));
            flag = 0;
            _delay_ms(3000);
        }
    }
    return;
}

void Change_pass() {
    char text;
    LCD_cursor(0, 0);
    LCD_string((u8*) "change pass?");
    LCD_cursor(1, 0);
    LCD_string((u8*) "1)y or 2)n");
    do {
        text = keypad_scan();
    } while (text == 0);
    LCD_char(text);
    _delay_ms(50);
    if (text == '1') {
        LCD_clearscreen();
        Enter_1st_pass();
    } else {
        LCD_clearscreen();
    }
}