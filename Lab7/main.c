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

        switch_function();

        ping_send();

        switch_function();

        timer_waitMillis(500);

        ping_read();

    }
}
