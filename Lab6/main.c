#include "lcd.h"
#include "timer.h"
#include "adc.h"
#include "movement.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#define BUFF_SIZE 16


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
    uart_init();

    //oi_t *sensor_data = oi_alloc();
    //oi_init(sensor_data);

    //double buffer[BUFF_SIZE];
    //int i;
    double average, distance;
    //double sum;

//    double error_average = 0;;
//    for (i = 0; i < 9; i++) {
//        //start at 5cm
//        move_backward(sensor_data, 5);
//        timer_waitMillis(2000);
//
//        for(i = 0; i < BUFF_SIZE; i++) {
//            adc_read(&buffer[i]);
//        }
//        sum = 0;
//        for (i = 0; i < BUFF_SIZE; i++) {
//            sum += buffer[i];
//        }
//        average = sum / BUFF_SIZE;
//        distance = 8*(pow(10, 6))*(pow(average, -1.714));
//
//        error_average += distance - (10 + (i * 5));
//
//    }
//    error_average /= 9;
//    lcd_printf("Error: %f", error_average);
//    timer_waitMillis(5000);

    uart_sendString("Value (RAW)");
    uart_sendChar('\t');
    uart_sendString("Sonar Distance (cm)");
    uart_sendChar('\n');

    while(1) {


//                for(i = 0; i < BUFF_SIZE; i++) {
//                    adc_read(&buffer[i]);
//                }
//                sum = 0;
//                for (i = 0; i < BUFF_SIZE; i++) {
//                    sum += buffer[i];
//                }
//                average = sum / BUFF_SIZE;
                adc_read(&average);
                distance = 22475*(pow(average, -.905)) /2; //+ error_average;

                lcd_printf("Value: %.3f\nDistance: %.3f", average, distance);

                char raw_value[20];
                char sonar_distance[20];

                sprintf(raw_value, "%f", average);
                sprintf(sonar_distance, "%f", distance);

                uart_sendString(raw_value);
                uart_sendChar('\t');
                uart_sendString(sonar_distance);
                uart_sendChar('\n');

                timer_waitMillis(100);



    }

}
