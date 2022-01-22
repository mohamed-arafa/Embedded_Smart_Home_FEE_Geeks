
#include"LCD.h"



void LCD_Initial(void)
{
    //set LCD pins as output in case of 4 bit lcd D4,D5,D6,D7
    
	set_pin_directin(LCD_PORT,pin4,OUTPUT); //SET D4 AS OUTPUT
    set_pin_directin(LCD_PORT,pin5,OUTPUT); //SET D5 AS OUTPUT
    set_pin_directin(LCD_PORT,pin6,OUTPUT); //SET D6 AS OUTPUT
    set_pin_directin(LCD_PORT,pin7,OUTPUT); //SET D7 AS OUTPUT
	
	
    set_pin_directin(LCD_CONTROL_PORT,LCD_EN_PIN,OUTPUT); //EN
    //set_pin_directin(LCD_CONTROL_PORT,LCD_RW_PIN,OUTPUT); //RW
    set_pin_directin(LCD_CONTROL_PORT,LCD_RS_PIN,OUTPUT); //RS
	_delay_ms(50);									// small delay after power on of lcd. edited by/Mo Arafa
    //write_pin(LCD_CONTROL_PORT,LCD_RW_PIN,LOW); // enable write to LCD
	LCD_Cmd(0X33);
	_delay_ms(1);
	LCD_Cmd(0X32);
	_delay_ms(1);
	LCD_Cmd(0x0c);				//turn off cursor
	_delay_ms(1);
	LCD_Cmd(0x06);
	_delay_ms(1);			
    LCD_Cmd(FOUR_BIT_MODE);  //enable 4 bit LCD Mode
    LCD_clearscreen();			// CLR LCD screen
    _delay_ms(10);				//small delay to ensure LCD finish the initialization

}
static void send_falling_edge(void)
{

    set_pin(LCD_CONTROL_PORT,LCD_EN_PIN);		// set enable pin to one //upper
    _delay_us(2);								//period of high
    reset_pin(LCD_CONTROL_PORT,LCD_EN_PIN);		// clear enable pin //low
    _delay_us(2);								// period of low
}

void LCD_Cmd(u8 cmd)
{
    //Cmd **** ****
    write_highnibble(LCD_PORT,cmd);				// edited by /Mo Arafa "cmd&0xf0"
    write_pin(LCD_CONTROL_PORT,LCD_RS_PIN,LOW); //enable LCD to receive command
    send_falling_edge();						//send falling edge
	_delay_us(100);
    write_highnibble(LCD_PORT,cmd<<4);			//instruction so cmd<<4
    write_pin(LCD_CONTROL_PORT,LCD_RS_PIN,LOW); //enable LCD to receive command
    send_falling_edge();						//send falling edge
	_delay_us(100);
}

void LCD_clearscreen(void)
{
    LCD_Cmd(CLR_SCREEN); // clear the screen
	_delay_ms(5);
}
void LCD_char(u8 data)
{
    //data **** ****
    write_highnibble(LCD_PORT,data&0xf0);
    write_pin(LCD_CONTROL_PORT,LCD_RS_PIN,HIGH);//enable LCD to receive data
    send_falling_edge(); //send falling edge
    //store high 4 bits
	_delay_us(100);
    write_highnibble(LCD_PORT,data<<4); //data so data <<4
    write_pin(LCD_CONTROL_PORT,LCD_RS_PIN,HIGH); //enable LCD to receive data
    //store next 4 bits
    send_falling_edge(); //send falling edge
	_delay_us(100);

}
void LCD_string(u8 *str)
{
    u8 index=0;
    while( str[index] != 0 )
    {
        LCD_char(str[index]);   // print the characters of the string
        index++;                // make the pointer points to the next character
    }

}
void LCD_cursor(u8 row, u8 coloumn)
{
if (row==0)
	LCD_Cmd(0x80+coloumn);
else
	LCD_Cmd(0x80+coloumn+0x40);
}

