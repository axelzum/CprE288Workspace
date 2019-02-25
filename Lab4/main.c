#include "lcd.h"
#include "button.h"
#include "uart.h"
#include "movement.h"
#include <stdio.h>
#include <string.h>
// Your code can use the global variables defined in button.c: button_event, button_num
// They are declared with the extern qualifier in button.h, which makes the variables visible to this file.


/**
 * @file main.c
 *
 * Prints the button that has been pressed
 *
 * @author Axel Zumwalt, Allan Juarez
 * @date 2/14/19
 */
int main(void) {
    // Hint: You may need to use pointers to return the button that has been pressed

    lcd_init();
    uart_init();
    oi_t *sensor_data = oi_alloc();
       oi_init(sensor_data);

    while(1) {
       char data[21];
       int count =0;
      data[1] ='r';
       uart_sendChar(data[1]);

       while(count<21){

          data[count] = uart_receive();

           if(data[count]== '\r' ){
               data[count]= '\0';
               uart_sendChar('\r');
               uart_sendChar('\n');
               if(strcmp(data,"move")==0){
                   move_forward(sensor_data, 50);
               }


              // lcd_printf("%s %d, %s %c", "index=", count,"char=", data[count]);

               break;
           }
           else{

               uart_sendChar(data[count]);
               lcd_printf("%s %d, %s %c", "index=", count,"char=", data[count]);
               count++;
           }


       }
        data[20] = '\0';
       lcd_printf("%s", data);




    }

}
