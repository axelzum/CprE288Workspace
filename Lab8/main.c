#include "lcd.h"
#include "timer.h"
#include "servo.h"
#include "button.h"

/**
 * @file main.c
 *
 * Lab 8 main file.
 *
 * USE ROBOT 13
 *
 * @author Axel Zumwalt, Allan Juarez
 * @date 3/28/19
 */
int main(void) {

    lcd_init();
    servo_init();
    button_init();
    init_button_interrupts(button_event, button_num);

    while (1) {

        if (button_num == 1) {
            servo_position = servo_move(1);
            button_num=0;
        }
        else if (button_num == 2) {
            servo_position = servo_move(2.5);
            button_num=0;
        }
        else if (button_num == 3) {
            servo_position = servo_move(5);
            button_num=0;
        }
        else if (button_num == 4) {
            if (movement_direction == 0) {
                movement_direction = 1;
            }
            else {
                movement_direction = 0;
            }
            button_num=0;
        }
        else if (button_num == 5) {
            servo_position = servo_move(0);
            button_num=0;
        }
        else if (button_num == 6) {
            servo_position = servo_move(180);
            button_num=0;

        }

        if (servo_position > 180) {
            servo_position = servo_move(180);
        }
        else if (servo_position < 0) {
            servo_position = servo_move(0);
        }

        lcd_printf("Servo position: %d\nDirection: %d", servo_position, movement_direction);

    }
}
