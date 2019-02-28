#include "lcd.h"
#include "button.h"
#include "uart.h"
#include "movement.h"
#include "timer.h"
#include <stdio.h>
#include <string.h>
#include "lab5_scan_data.h"

/**
 * @file main.c
 *
 * Reads a csv file with IR and Sonar sensor values and sends then to the computer over UART.
 *
 * @author Axel Zumwalt, Allan Juarez
 * @date 2/28/19
 */
int main(void) {

    lcd_init();
    uart_init();

    struct reading reading_array[181];

    get_reading("dataset3.csv", reading_array);

    int i;

    //First line formatting
    uart_sendString("Degrees");
    uart_sendChar('\t');
    uart_sendString("IR Distance (cm)");
    uart_sendChar('\t');
    uart_sendString("Sonar Distance (cm)");
    uart_sendChar('\n');

    //Prints data for each index of reading_array
    for (i = 0; i < 181; i++) {
        char degree[5];
        char ir_distance[20];
        char sonar_distance[20];

        sprintf(degree, "%d", i);
        sprintf(ir_distance, "%f", reading_array[i].ir_distance);
        sprintf(sonar_distance, "%f", reading_array[i].sonar_distance);

        uart_sendString(degree);
        uart_sendChar('\t');
        uart_sendString(ir_distance);
        uart_sendChar('\t');
        uart_sendString(sonar_distance);
        uart_sendChar('\n');
    }
}
