
#include "GPIO_INTERFACE.h"

void set_pin(portname_t portname, pinnumber_t pinnumber) {
    switch (portname) {
        case GPIOA:
            SET_BIT(PORTA, pinnumber);
            break;
        case GPIOB:
            SET_BIT(PORTB, pinnumber);
            break;
        case GPIOC:
            SET_BIT(PORTC, pinnumber);
            break;
        case GPIOD:
            SET_BIT(PORTD, pinnumber);
            break;
    }
}

void reset_pin(portname_t portname, pinnumber_t pinnumber) {
    switch (portname) {

        case GPIOA:
            CLR_BIT(PORTA, pinnumber);
            break;
        case GPIOB:
            CLR_BIT(PORTB, pinnumber);
            break;
        case GPIOC:
            CLR_BIT(PORTC, pinnumber);
            break;
        case GPIOD:
            CLR_BIT(PORTD, pinnumber);
            break;

    }
}

void toggle_pin(portname_t portname, pinnumber_t pinnumber) {
    switch (portname) {

        case GPIOA:
            TGL_BIT(PORTA, pinnumber);
            break;
        case GPIOB:
            TGL_BIT(PORTB, pinnumber);
            break;
        case GPIOC:
            TGL_BIT(PORTC, pinnumber);
            break;
        case GPIOD:
            TGL_BIT(PORTD, pinnumber);
            break;

    }
}

void set_pin_directin(portname_t portname, pinnumber_t pinnumber, state_t state) {
    switch (portname) {
        case GPIOA:
            if (state == OUTPUT) {
                SET_BIT(DDRA, pinnumber); //Set the direction of the given pin in port A as output
            } else {
                CLR_BIT(DDRA, pinnumber); //Set the direction of the given pin in port A as input
            }
            break;
        case GPIOB:
            if (state == OUTPUT) {
                SET_BIT(DDRB, pinnumber); //Set the direction of the given pin in port B as output
            } else {
                CLR_BIT(DDRB, pinnumber); //Set the direction of the given pin in port B as input
            }
            break;
        case GPIOC:
            if (state == OUTPUT) {
                SET_BIT(DDRC, pinnumber); //Set the direction of the given pin in port C as output
            } else {
                CLR_BIT(DDRC, pinnumber); //Set the direction of the given pin in port C as input
            }
            break;
        case GPIOD:
            if (state == OUTPUT) {
                SET_BIT(DDRD, pinnumber); //Set the direction of the given pin in port D as output
            } else {
                CLR_BIT(DDRD, pinnumber); //Set the direction of the given pin in port D as input
            }
            break;

    }
}

void write_pin(portname_t portname, pinnumber_t pinnumber, u8 outputvalue) {
    switch (portname) {
        case GPIOA:
            if (outputvalue == HIGH) {
                SET_BIT(PORTA, pinnumber); //Set the value of the given pin in port A as High
            } else {
                CLR_BIT(PORTA, pinnumber); //Set the value of the given pin in port A as Low
            }
            break;
        case GPIOB:

            if (outputvalue == HIGH) {
                SET_BIT(PORTB, pinnumber); //Set the value of the given pin in port B as High
            } else {
                CLR_BIT(PORTB, pinnumber); //Set the value of the given pin in port B as Low
            }
            break;
        case GPIOC:

            if (outputvalue == HIGH) {
                SET_BIT(PORTC, pinnumber); //Set the value of the given pin in port C as High
            } else {
                CLR_BIT(PORTC, pinnumber); //Set the value of the given pin in port C as Low
            }
            break;
        case GPIOD:

            if (outputvalue == HIGH) {
                SET_BIT(PORTD, pinnumber); //Set the value of the given pin in port D as High
            } else {
                CLR_BIT(PORTD, pinnumber); //Set the value of the given pin in port D as Low
            }
            break;

    }


}

u8 read_u8pin(portname_t portname, pinnumber_t pinnumber) {
    volatile u8 return_value = 0;
    switch (portname) {
        case GPIOA:
            return_value = GET_BIT(PINA, pinnumber); //Read the value from the given pin in port A
            break;

        case GPIOB:
            return_value = GET_BIT(PINB, pinnumber); //Read the value from the given pin in port B
            break;

        case GPIOC:
            return_value = GET_BIT(PINC, pinnumber); //Read the value from the given pin in port C
            break;

        case GPIOD:
            return_value = GET_BIT(PIND, pinnumber); //Read the value from the given pin in port D
            break;
    }
    return return_value;
}

void write_port(portname_t portname, u8 portvalue) {
    switch (portname) {
        case GPIOA:
            PORTA = portvalue; //Write the given value to the port A
            break;
        case GPIOB:
            PORTB = portvalue; //Write the given value to the port B
            break;
        case GPIOC:
            PORTC = portvalue; //Write the given value to the port C
            break;
        case GPIOD:
            PORTD = portvalue; //Write the given value to the port D
            break;

    }
}

void write_highnibble(portname_t portname, u8 value) {
    switch (portname) {
        case GPIOA:
            WRT_HIGH_NIPPLE(PORTA, value); //Set only the high nibble of the port A by the given value
            break;
        case GPIOB:
            WRT_HIGH_NIPPLE(PORTB, value); //Set only the high nibble of the port B by the given value
            break;
        case GPIOC:
            WRT_HIGH_NIPPLE(PORTC, value); //Set only the high nibble of the port C by the given value
            break;
        case GPIOD:
            WRT_HIGH_NIPPLE(PORTD, value); //Set only the high nibble of the port D by the given value
            break;

    }
}

void clear_high_nibble(portname_t portname) {
    switch (portname) {
        case GPIOA:
            CLR_HIGH_NIPPLE(PORTA); //set the value of the high nibble of the port A as low
            break;
        case GPIOB:
            CLR_HIGH_NIPPLE(PORTB); //set the value of the high nibble of the port B as low
            break;
        case GPIOC:
            CLR_HIGH_NIPPLE(PORTC); //set the value of the high nibble of the port C as low
            break;
        case GPIOD:
            CLR_HIGH_NIPPLE(PORTD); //set the value of the high nibble of the port D as low
            break;


    }
}





