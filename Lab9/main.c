#include "lcd.h"
#include "timer.h"
#include "servo.h"
#include "button.h"
#include "adc.h"
#include "uart.h"
#include "ping.h"
#include "analysis.h"
#include <math.h>

/**
 * @file main.c
 *
 * Lab 9 main file.
 *
 *
 * @author Axel Zumwalt, Allan Juarez
 * @date 4/4/19
 */
int main(void) {

    lcd_init();
    servo_init();
    uart_init();
    adc_init();
    ping_init();

    uart_sendString("Degrees");
    uart_sendChar('\t');
    uart_sendString("IR Distance (cm)");
    uart_sendChar('\t');
    uart_sendString("Sonar Distance (cm)");
    uart_sendChar('\r');
    uart_sendChar('\n');

    double average, distance; //adc IR variables

    struct reading reading_array[180];
    int reading_index = 0;

    while (servo_position < 180) {

        //IR
        adc_read(&average);
        distance = 81189*(pow(average, -1.132)); //TODO calibrate

        char ir_distance[20];
        sprintf(ir_distance, "%f", distance);


        //PING)))
        switch_function();

        ping_send();

        switch_function();

        timer_waitMillis(100);

        char ping_distance[20];
        double ping_dist_float = ping_read();
        sprintf(ping_distance, "%f", ping_dist_float);


        //Degrees
        char degrees[5];
        sprintf(degrees, "%d", servo_position);


        //Print to UART
        uart_sendString(degrees);
        uart_sendChar('\t');
        uart_sendString(ir_distance);
        uart_sendChar('\t');
        uart_sendString(ping_distance);
        uart_sendChar('\r');
        uart_sendChar('\n');

        reading_array[reading_index].ir_distance = ir_distance;
        reading_array[reading_index].sonar_distance = ping_distance;
        reading_index++;

        //Move servo
        servo_position = servo_move(2);
    }

    return 0;
}
