// HD44780 2-line LCD library
//
// Compiler: HI-TECH C for PIC18
//
// 2015 Copyleft


#define _XTAL_FREQ 8000000

#include <htc.h>


// define LCD lines connected to MCU's pins (can be used any pins)

// LCD line RW connected to Vss (ground)

// LCD line RS connected to RD6 pin
#define RS_PIN  TRISD6=0
#define RS_H    RD6=1
#define RS_L    RD6=0

// LCD line E connected to RD7 pin
#define EN_PIN  TRISD7=0
#define EN_H    RD7=1
#define EN_L    RD7=0

// LCD data bus (4-bit interface)
// data line 4..7 connected to RB0..RB3 pins
#define D4_PIN  TRISB0=0
#define D4_H    RB0=1
#define D4_L    RB0=0

#define D5_PIN  TRISB1=0
#define D5_H    RB1=1
#define D5_L    RB1=0

#define D6_PIN  TRISB2=0
#define D6_H    RB2=1
#define D6_L    RB2=0

#define D7_PIN  TRISB3=0
#define D7_H    RB3=1
#define D7_L    RB3=0

// LCD backlight line connected to RD5 pin
#define BL_PIN  TRISD5=0
#define BL_ON   RD5=1
#define BL_OFF  RD5=0


typedef unsigned char uint8_t; //stdint


void lcd_init(void);
void lcd_write(uint8_t data);
void lcd_cmd(uint8_t data);
void lcd_clear(void);
void lcd_goto(uint8_t line, uint8_t column);
void lcd_char(uint8_t sign);
void lcd_print(const char *str);
void lcd_right(void);
void lcd_left(void);


///////////////////////////////////////////////////////////////////////////////
void lcd_init(void)
{
//init MCU pins (set as output)
RS_PIN;
EN_PIN;
D4_PIN;
D5_PIN;
D6_PIN;
D7_PIN;
BL_PIN;

//init LCD controller
__delay_ms(20); //delay on power up
lcd_cmd(0b0011);
__delay_ms(5); //wait for the instruction to complete
lcd_cmd(0b0011);
__delay_us(200); //wait for the instruction to complete
lcd_cmd(0b0011);
__delay_us(200);
lcd_cmd(0b0010); //enable 4-bit mode
__delay_us(50);
lcd_cmd(0b0010);
lcd_cmd(0b1000); //4-bit mode, 2-line, 5x8 font
__delay_us(50);
lcd_cmd(0b0000);
lcd_cmd(0b1000); //display off
__delay_us(50);
lcd_clear();
lcd_cmd(0b0000);
lcd_cmd(0b0110); //entry mode set
__delay_us(50);
lcd_cmd(0b0000);
lcd_cmd(0b1100); //display on, cursor off, blink off
__delay_us(50);
}


///////////////////////////////////////////////////////////////////////////////
void lcd_write(uint8_t data) //write data to LCD
{
if(data & 1) D4_H;
else D4_L;
	
if(data & 2) D5_H;
else D5_L;
	
if(data & 4) D6_H;
else D6_L;
	
if(data & 8) D7_H;
else D7_L;

EN_H;
__delay_us(100);
EN_L;
}


///////////////////////////////////////////////////////////////////////////////
void lcd_cmd(uint8_t data) //send command to LCD
{ 
RS_L;
lcd_write(data);
}


///////////////////////////////////////////////////////////////////////////////
void lcd_clear(void) //clear screen
{
lcd_cmd(0b0000);
lcd_cmd(0b0001);
__delay_ms(5);
}


///////////////////////////////////////////////////////////////////////////////
void lcd_goto(uint8_t line, uint8_t column) //line 0..1, column 0..39
{
lcd_cmd(((0x80+(line<<6))+column)>>4);
lcd_cmd((0x80+(line<<6))+column);
}


///////////////////////////////////////////////////////////////////////////////
void lcd_char(uint8_t sign) //print a character
{
RS_H;
lcd_write(sign>>4);
lcd_write(sign);
}


///////////////////////////////////////////////////////////////////////////////
void lcd_print(const char *str) //print a string
{
while(*str) lcd_char(*str++);
}


///////////////////////////////////////////////////////////////////////////////
void lcd_right(void) //shift right display 
{
lcd_cmd(0x01);
lcd_cmd(0x0C);
}


///////////////////////////////////////////////////////////////////////////////
void lcd_left(void) //shift left display
{
lcd_cmd(0x01);
lcd_cmd(0x08);
}
