#include "lcd.h"
#include "timer.h"
#include "adc.h"
#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 100


/**
 * @file main.c
 *
 * Lab 6 main file.
 *
 * @author Axel Zumwalt, Allan Juarez
 * @date 3/7/19
 */
int main(void) {

    lcd_init();
    adc_init();

    double buffer[BUFF_SIZE];
    int i;
    double average;
    double sum;

    while(1) {
        for(i = 0; i < BUFF_SIZE; i++) {
            adc_read(&buffer[i]);
        }
        sum = 0;
        for (i = 0; i < BUFF_SIZE; i++) {
            sum += buffer[i];
        }
        average = sum / BUFF_SIZE;

        lcd_printf("%f", average);
        timer_waitMillis(100);

    }

}
