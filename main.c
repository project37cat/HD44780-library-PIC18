// LCD test
// PIC18LF4320 8MHz


#include "lcd.h"

#include <htc.h>

__CONFIG(1, HS );
__CONFIG(2, BORDIS & WDTDIS );


///////////////////////////////////////////////////////////////////////////////
void main(void)
{
ADCON1=0b1111; //disable analog inputs

lcd_init();

BL_ON; //LCD backlight turned ON

lcd_print("HD44780");
lcd_goto(1,0);
lcd_print("LCD");

for(;;);
}
