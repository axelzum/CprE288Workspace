#include "lcd.h"
#include "button.h"
#include "uart.h"

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


    while(1) {
       char data[21];
       int count =0;

       while(count<21){

           data[count] = uart_receive();

           if(data[count]== '\r' ){
               data[count]= '\0';

               lcd_printf("%s %d, %s %c", "index=", count,"char=", data[count]);

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
