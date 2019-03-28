/*
 * servo.c
 *
 *  Created on: Mar 28, 2019
 *      Author: ajuarez
 */

#include "servo.h"

void servo_init(void) {
    //Setup GPIO
        SYSCTL_RCGCGPIO_R |= 0b10; //Enable clock on Port B
        SYSCTL_RCGCTIMER_R |= 0x20; //Enable timer 1 clock

        GPIO_PORTB_AFSEL_R |= 0b00100000; //Use alternate function on port 5
        GPIO_PORTB_PCTL_R |= 0x00007000; //Use function T1CCP1

//        GPIO_PORTB_DIR_R &= 0x7; //Set pin 5 input
//        GPIO_PORTB_DEN_R |= 0x8; //set pin 3 as digital mode

    //Setup Timer 1B
        TIMER1_CTL_R &= 0xFFFFFEFF; //Disable timer while we set it up
        //DISABLE TB INSTEA DOF TA

        TIMER1_CFG_R = 0x4; //Set to 16-bit mode

        TIMER1_TBMR_R = 0b1011; //PWM, edge count, periodic timer
        //TIMER1_CTL_R = 0xC00; //Detect both edge //TODO output is unaffected

        TIMER1_TBPR_R = 0xFF; //Use prescaler extension to 24 bits
        TIMER1_TBILR_R = 0xC350; //Load max 24-bit value  //50000 c350
        TIMER1_TBPMR_R = 0xFF; //use prescaler extension to 24 bits
        TIMER1_TBMATCHR_R = 0xF4240; //load match value //1000000

        TIMER1_CTL_R = 0x100; //enable

}

int servo_move(float degrees) {

}


