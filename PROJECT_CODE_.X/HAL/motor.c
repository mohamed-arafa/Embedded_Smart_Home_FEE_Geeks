#include"../MCAL/GPIO_INTERFACE.h"
#include "../MCAL/Timer0.h"
#include "motor.h"

/*********** initialization ***********/
static void fans_speed();

static volatile u16 c = 0;

static volatile u16 s = 0;


SPEED_LEVEL fan1_level;
SPEED_LEVEL fan2_level;
SPEED_LEVEL fan3_level;

void
fans_init() {

    set_pin_directin(fan1_GPIO_g, fan1_pin_num_g, OUTPUT);
    set_pin_directin(fan3_GPIO_g, fan3_pin_num_g, OUTPUT);
    set_pin_directin(fan2_GPIO_g, fan2_pin_num_g, OUTPUT);

    timer0_init(normal_mode, OC0_disconnected, timer0_pre_8);
    timer0_OVF_interrupt_enable();
    timer0_OVF_setCallBack(fans_speed);


}

/**************setting level****************/

void
fans_set_speed(SPEED_LEVEL fan1_level_local, SPEED_LEVEL fan2_level_local, SPEED_LEVEL fan3_level_local) {
    fan1_level = fan1_level_local;
    fan2_level = fan2_level_local;
    fan3_level = fan3_level_local;


}

static void fans_speed() {
    c++;

    TCNT0 = 62;
    if (fan1_level == full_speed)
        set_pin(fan1_GPIO_g, fan1_pin_num_g);

    if (fan2_level == full_speed)
        set_pin(fan2_GPIO_g, fan2_pin_num_g);

      if (fan3_level == full_speed)
          set_pin(fan3_GPIO_g, fan3_pin_num_g);
    


    if (c == 10) {
    
             if (fan3_level == level_2)
                set_pin(fan3_GPIO_g, fan3_pin_num_g);
    
        if (fan2_level == level_2)
            set_pin(fan2_GPIO_g, fan2_pin_num_g);
        if (fan1_level == level_2)
            set_pin(fan1_GPIO_g, fan1_pin_num_g);

    } else if (c == 20) {


        if (fan3_level == level_1)
                set_pin(fan3_GPIO_g, fan3_pin_num_g);
    
        if (fan2_level == level_1)
            set_pin(fan2_GPIO_g, fan2_pin_num_g);
        if (fan1_level == level_1)
            set_pin(fan1_GPIO_g, fan1_pin_num_g);

    } else if (c == 50) {
        c = 0;
      if (fan3_level != full_speed)
              reset_pin(fan3_GPIO_g, fan3_pin_num_g);
     if (fan2_level != full_speed)
            reset_pin(fan2_GPIO_g, fan2_pin_num_g);
        if (fan1_level != full_speed)
            reset_pin(fan1_GPIO_g, fan1_pin_num_g);
    }
}


/*
void fan1_set_speed(SPEED_LEVEL level){
      
    c++;
    if(level==0){
        reset_pin(GPIOB,pin1);
        c=0;
    }else if(level==5){
        set_pin(GPIOB,pin1);
        c=0;
    }else if(c==10&&level==4){
         set_pin(GPIOB,pin1);
    }else if(c==20&&level==3){
         set_pin(GPIOB,pin1);
    }else if(c==30&&level==2){
         set_pin(GPIOB,pin1);
    }else if(c==40&&level ==1){
         set_pin(GPIOB,pin1);
    }else if(c==50&&level!=5){
        c=0;
        reset_pin(GPIOB,pin1);
    }
}
void fan2_set_speed(SPEED_LEVEL level){
      
    c++;
    if(level==0){
        reset_pin(GPIOB,pin1);
        c=0;
    }else if(level==5){
        set_pin(GPIOB,pin1);
        c=0;
    }else if(c==10&&level==4){
         set_pin(GPIOB,pin1);
    }else if(c==20&&level==3){
         set_pin(GPIOB,pin1);
    }else if(c==30&&level==2){
         set_pin(GPIOB,pin1);
    }else if(c==40&&level ==1){
         set_pin(GPIOB,pin1);
    }else if(c==50&&level!=5){
        c=0;
        reset_pin(GPIOB,pin1);
    }
}
void fan3_set_speed(SPEED_LEVEL level){
      
    c++;
    if(level==0){
        reset_pin(GPIOB,pin1);
        c=0;
    }else if(level==5){
        set_pin(GPIOB,pin1);
        c=0;
    }else if(c==10&&level==4){
         set_pin(GPIOB,pin1);
    }else if(c==20&&level==3){
         set_pin(GPIOB,pin1);
    }else if(c==30&&level==2){
         set_pin(GPIOB,pin1);
    }else if(c==40&&level ==1){
         set_pin(GPIOB,pin1);
    }else if(c==50&&level!=5){
        c=0;
        reset_pin(GPIOB,pin1);
    }
}
void heater1_set_speed(SPEED_LEVEL level){
      
    c++;
    if(level==0){
        reset_pin(GPIOB,pin1);
        c=0;
    }else if(level==5){
        set_pin(GPIOB,pin1);
        c=0;
    }else if(c==10&&level==4){
         set_pin(GPIOB,pin1);
    }else if(c==20&&level==3){
         set_pin(GPIOB,pin1);
    }else if(c==30&&level==2){
         set_pin(GPIOB,pin1);
    }else if(c==40&&level ==1){
         set_pin(GPIOB,pin1);
    }else if(c==50&&level!=5){
        c=0;
        reset_pin(GPIOB,pin1);
    }
}
void heater2_set_speed(SPEED_LEVEL level){
      
    c++;
    if(level==0){
        reset_pin(GPIOB,pin1);
        c=0;
    }else if(level==5){
        set_pin(GPIOB,pin1);
        c=0;
    }else if(c==10&&level==4){
         set_pin(GPIOB,pin1);
    }else if(c==20&&level==3){
         set_pin(GPIOB,pin1);
    }else if(c==30&&level==2){
         set_pin(GPIOB,pin1);
    }else if(c==40&&level ==1){
         set_pin(GPIOB,pin1);
    }else if(c==50&&level!=5){
        c=0;
        reset_pin(GPIOB,pin1);
    }
}

 */