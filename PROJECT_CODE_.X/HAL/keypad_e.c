#include "keypad_e.h" 
#define no_pressed_key 0
volatile char key_pressed ; 
void keypad_init(void) {
    KEYPAD_DIR = 0x0F;
    KEYPAD_PORT = 0xFF;
}

char keypad_scan(void) {
    u8 row = 0, key;
    for (row = 0; row < 4; row++) {
        //set all row high
        SET_BIT(KEYPAD_PORT, ROW0);
        SET_BIT(KEYPAD_PORT, ROW1);
        SET_BIT(KEYPAD_PORT, ROW2);
        SET_BIT(KEYPAD_PORT, ROW3);
        //clear row number from iteration
        switch (row) {
            case 0:CLR_BIT(KEYPAD_PORT, ROW0);
                break;
            case 1:CLR_BIT(KEYPAD_PORT, ROW1);
                break;
            case 2:CLR_BIT(KEYPAD_PORT, ROW2);
                break;
            case 3:CLR_BIT(KEYPAD_PORT, ROW3);
                break;
        }
        //read the input
        key  = (KEYPAD_PIN & (1 << LINE0));
        key |= (KEYPAD_PIN & (1 << LINE1));
        key |= (KEYPAD_PIN & (1 << LINE2));
        key |= (KEYPAD_PIN & (1 << LINE3));

        //if it was input
        if (ALL_LINES != 1) {
            //wait till the input is gone
            while (ALL_LINES != 1);
            break;
        }
    }

    if (row == 4) {
        return no_pressed_key;
    } else {
        switch (row) {
            case 0://switch the input
                switch (key) {
                    case 0x70: return 'A';
                    case 0xB0: return '3';
                    case 0xD0: return '2';
                    case 0xE0: return '1';
                }
            case 1://switch the input
                switch (key) {
                    case 0x70: return 'B';
                    case 0xB0: return '6';
                    case 0xD0: return '5';
                    case 0xE0: return '4';
                }
            case 2://switch the input
                switch (key) {
                    case 0x70: return 'C';
                    case 0xB0: return '9';
                    case 0xD0: return '8';
                    case 0xE0: return '7';
                }
            case 3://switch the input
                switch (key) {
                    case 0x70: return 'D';
                    case 0xB0: return '#';
                    case 0xD0: return '0';
                    case 0xE0: return '*';
                }
        }
        return 0;
    }
}

/*char keypad_result() {
    key_pressed = keypad_scan();
    if (key_pressed != 0) {
        return (key_pressed-48) ;
    }
    return (0);
}*/