

#ifndef SERVO_H
#define SERVO_H

#define servo_pin pin5
#define servo_gpio GPIOD


void servo_init(void);
void servo_set_angle(u8 angle);

#endif
