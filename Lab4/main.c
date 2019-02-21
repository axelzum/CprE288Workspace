#include "lcd.h"
#include "button.h"
#include "uart.h"

// Your code can use the global variables defined in button.c: button_event, button_num
// They are declared with the extern qualifier in button.h, which makes the variables visible to this file.


/**
 * @file main.c
 *
 * Prints the button that has been pressed
 *
 * @author Axel Zumwalt, Allan Juarez
 * @date 2/14/19
 */
int main(void) {
    // Hint: You may need to use pointers to return the button that has been pressed

    lcd_init();
    button_init();
    init_button_interrupts(button_event, button_num);

    while(1) {

       lcd_printf("%d", button_num);

    }

}
