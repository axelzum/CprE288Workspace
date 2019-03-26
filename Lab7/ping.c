/*
 * @file ping.c
 *
 * @brief Contains the functions called by main to enable and use PING))).
 *
 * @author Axel Zumwalt, Allan Juarez
 * @date 3/14/2019
 */

#include "ping.h"
#include "timer.h"
#include "lcd.h"


/**
 * Initilize PING))) with GPTM
 *
 * @author Axel Zumwalt, Allan Juarez
 *
 * @date 3/14/19
 *
 */
void ping_init(void) {
//Setup GPIO
    SYSCTL_RCGCGPIO_R |= 0b10; //Enable clock on Port B
    SYSCTL_RCGCTIMER_R |= 0x8; //Enable timer 3 clock

    //GPIO_PORTB_AFSEL_R |= 0b00001000; //Use alternate function on port 3
    GPIO_PORTB_PCTL_R |= 0x00007000; //Use function T3CCP1

    GPIO_PORTB_DIR_R |= 0x8; //Set pin 3 digital mode
    GPIO_PORTB_DEN_R |= 0x8; //set pin 3 as output

//Setup Timer 3B
    TIMER3_CTL_R &= ~0x1; //Disable timer while we set it up

    TIMER3_CFG_R = 0x4; //Set to 16-bit mode
    TIMER3_TBMR_R = 0b10111; //count up, edge time, capture mode
    TIMER3_CTL_R = 0b0000; //Detect positive edge

    TIMER3_TBPR_R = 0xFF; //Use prescaler extension to 24 bits
    TIMER3_TBILR_R = 0xFFFF; //Load max 24-bit value

    TIMER3_ICR_R |= 0b10000000000; //Clear capture event interrupt status
    TIMER3_IMR_R |= 0b10000000000; //Enable capture event interrupts

//NVIC setup
    NVIC_PRI9_R |= 0x20; //Timer 3B pri=1
    NVIC_EN1_R |= 0x10; //Enable interrupt 36

    IntRegister(52, TIMER3B_Handler);

    //TIMER3_CTL_R |= 0x1; //Reenable Timer3

    IntMasterEnable();
}

void TIMER3B_Handler() {
    if (state == 0) { //state == send pulse
        state = 1;
        time_first = TIMER3_TBR_R;
    }
    else if(state == 1) { //state == recieve pulse
        state = 0;
        time_last = TIMER3_TBR_R;
    }
}

/**
 * Read from PING)))
 *
 * @author Axel Zumwalt, Allan Juarez
 *
 * @date 3/14/19
 *
 */
void ping_read(void) {
    int pulse_width;
    pulse_width = time_last - time_first;
    lcd_printf("Pulse Width: %d", pulse_width);
}

/**
 * Switch from PB3 output ping to PB3 input timer
 *
 * @author Axel Zumwalt
 *
 * @date 3/25/2019
 */
void switch_function(void) {
    if (state == 0) { //state == send pulse
        TIMER3_CTL_R &= ~0x1; //Disable timer3
        state = 1;
        GPIO_PORTB_AFSEL_R = 0; //Disable alternate function port 3
        GPIO_PORTB_DEN_R |= 0x8; //set pin 3 as output
    }
    else if (state == 1) { //state == recieve pulse
        TIMER3_CTL_R |= 0x1; //enable Timer3
        state = 0;
        GPIO_PORTB_AFSEL_R |= 0b00001000; //Enable alternate function port 3
        GPIO_PORTB_DEN_R &= 0b11110111; //Set portb 3 to input
    }
}

/**
 * Send a pulse with the PING))) sensor
 *
 * @author Axel Zumwalt
 *
 * @date 3/25/2019
 */
void ping_send(void) {
    GPIO_PORTB_DATA_R = 0x8;
    timer_waitMicros(5);
    GPIO_PORTB_DATA_R = 0x0;
}
