#include "lcd.h"
#include "timer.h"
#include "ping.h"


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
    ping_init();

    while (1) {
        GPIO_PORTB_DEN_R |= 0x8; //set pin 3 as output

        GPIO_PORTB_DATA_R = 0x8;
        timer_waitMicros(5000000);
        GPIO_PORTB_DATA_R = 0x0;

        GPIO_PORTB_DEN_R &= 0b11110111; //Set portb 3 to input

        timer_waitMicros(10000000);


        ping_read();
    }

}
