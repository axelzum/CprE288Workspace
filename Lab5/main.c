#include "lcd.h"
#include "button.h"
#include "uart.h"
#include "movement.h"
#include <stdio.h>
#include <string.h>
#include "lab5_scan_data.h"

/**
 * @file main.c
 *
 * Robot recieves data from UART to drive robot.
 *
 * @author Axel Zumwalt, Allan Juarez
 * @date 2/21/19
 */
int main(void) {

    lcd_init();
    uart_init();
    reading readingArr[181];
//    oi_t *sensor_data = oi_alloc();
//    oi_init(sensor_data);

   get_reading("datasheet1.csv", readingArr);
}
