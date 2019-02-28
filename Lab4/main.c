#include "lcd.h"
#include "button.h"
#include "uart.h"
#include "movement.h"
#include <stdio.h>
#include <string.h>


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

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    //Part 1
//    while(1) {
//        char data[21];
//        int data_index = 0;
//
//        while(data_index < 20){
//
//            data[data_index] = uart_receive();
//
//            if(data[data_index] == '\r' ){
//                data[data_index] = '\0';
//                //uart_sendChar('\r');
//                //uart_sendChar('\n');
//
//                lcd_printf("Index=%d, Char=%c", data_index, data[data_index]);
//
//                break;
//            }
//            else{
//                //uart_sendChar(data[data_index]);
//                lcd_printf("Index=%d, Char=%c", data_index, data[data_index]);
//                data_index++;
//            }
//        }
//        data[20] = '\0';
//        lcd_printf("%s", data);
//    }

    //Part 2
//    while(1) {
//            char data[21];
//            int data_index = 0;
//
//            while(data_index < 20){
//
//                data[data_index] = uart_receive();
//
//                if(data[data_index] == '\r' ){
//                    data[data_index] = '\0';
//                    uart_sendChar('\r');
//                    uart_sendChar('\n');
//
//                    lcd_printf("Index=%d, Char=%c", data_index, data[data_index]);
//
//                    break;
//                }
//                else{
//                    uart_sendChar(data[data_index]);
//                    lcd_printf("Index=%d, Char=%c", data_index, data[data_index]);
//                    data_index++;
//                }
//            }
//            data[20] = '\0';
//            lcd_printf("%s", data);
//        }


    //Part 3
//    while(1) {
//
//    }

    //Part 5
        while(1) {
            char data[21];
            int data_index = 0;

            while(data_index < 20){

                data[data_index] = uart_receive();

                if(data[data_index] == '\r' ){
                    data[data_index] = '\0';
                    //uart_sendChar('\r');
                    //uart_sendChar('\n');

                    //lcd_printf("Index=%d, Char=%c", data_index, data[data_index]);

                    break;
                }
                else{
                    //uart_sendChar(data[data_index]);
                    //lcd_printf("Index=%d, Char=%c", data_index, data[data_index]);
                    data_index++;
                }
            }
            data[20] = '\0';
            lcd_printf("%s", data);

            char command[20], dtm[100];
            int parameter;

            strcpy(dtm, data);
            sscanf(dtm, "%s %d", command, &parameter);

            if (strcmp(command, "forward") == 0) {
                move_forward(sensor_data, (int)parameter);
            }
            else if (strcmp(command, "backward") == 0) {
                move_backward(sensor_data, (int)parameter);
            }
            else if (strcmp(command, "right") == 0) {
                turn_right(sensor_data, parameter);
            }
            else if (strcmp(command, "left") == 0) {
                turn_left(sensor_data, parameter);
            }

        }
}
