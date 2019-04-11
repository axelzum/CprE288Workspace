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

    double ir_raw, ir_distance; //adc IR variables
    double ir_average;

    double ping_average;

    int i;

    struct reading reading_array[180];
    int reading_index = 0;

    while (servo_position < 180) {

        //IR
        ir_average = 0;
        for (i = 0; i < 5; i++) {
            adc_read(&ir_raw);
            ir_distance = 81189*(pow(ir_raw, -1.132)); //TODO calibrate

            ir_average += ir_distance;
        }
        ir_average /= 5;

        char ir_char[20];
        sprintf(ir_char, "%f", ir_average);


        //PING)))
        ping_average = 0;
        for (i = 0; i < 5; i++) {
            switch_function();

            ping_send();

            switch_function();

            timer_waitMillis(20);

            ping_average += ping_read();
        }
        ping_average /= 5;

        char ping_char[20];
        sprintf(ping_char, "%f", ping_average);


        //Degrees
        char degrees[5];
        sprintf(degrees, "%d", servo_position);


        //Print to UART
        uart_sendString(degrees);
        uart_sendChar('\t');
        uart_sendString(ir_char);
        uart_sendChar('\t');
        uart_sendString(ping_char);
        uart_sendChar('\r');
        uart_sendChar('\n');

        reading_array[reading_index].degrees = servo_position;
        reading_array[reading_index].ir_distance = ir_average;
        reading_array[reading_index].sonar_distance = ping_average;
        reading_index++;

        //Move servo
        servo_position = servo_move(1);
    }

    struct object object_array[10];
    int num_objects = detect_objects(reading_array, object_array);

    //Send all objects to UART
    for (i = 0; i < num_objects; i++) {
        char objects[20];
        sprintf(objects, "%d", object_array[i].degree_start);
        uart_sendString(objects);
        uart_sendChar('\t');
        sprintf(objects, "%d", object_array[i].degree_stop);
        uart_sendString(objects);
        uart_sendChar('\r');
        uart_sendChar('\n');

    }

    find_smallest(reading_array, object_array, num_objects);

    return 0;
}
