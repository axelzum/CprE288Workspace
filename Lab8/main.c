#include "lcd.h"
#include "timer.h"
#include "servo.h"
#include "button.h"

/**
 * @file main.c
 *
 * Lab 7 main file.
 *
 * @author Axel Zumwalt, Allan Juarez
 * @date 3/14/19
 */
int main(void) {

    lcd_init();
    servo_init();
    button_init();
    init_button_interrupts(button_event, button_num);

    while (1) {



    }
}
