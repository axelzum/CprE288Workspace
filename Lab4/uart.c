#include "uart.h"

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80

void uart_init(void) {

    //Turn on clock for UART1 and Port B
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;

    //Enable alternate function for PB0, PB1
    GPIO_PORTB_AFSEL_R |= (BIT1 | BIT0);
    GPIO_PORTB_PCTL_R |= (BIT0 | BIT4);

    GPIO_PORTB_DEN_R |= (BIT1 | BIT0); //Set pins0,1 digital mode
    GPIO_PORTB_DIR_R &= ~BIT0; // Set pin 0 (Rx) to input(0)
    GPIO_PORTB_DIR_R |= BIT1;  // Set pin 1 (Tx) to output(1)

    //Disable UART0 device while we set it up
    UART1_CTL_R &= ~UART_CTL_UARTEN;

    // Set desired UART functionality
    UART1_CTL_R = 0b001000000000;

    //Set baud rate (9600 Baud)
    UART1_IBRD_R = 104; //16,000,000 / (16 * 9600) = 104.16666
    UART1_FBRD_R = 11;  // .1666*64+.5 = 11.16666
    UART1_CC_R = 0; //Use system clock as UART clock source

    //Set frame format: 1 start bit, 8databits, an odd parity bit, and 1 stop bit
    UART1_LCRH_R = 0b;//TODO

    //Setup UART0 interrupts
    UART1_ICR_R |= 0b00010000; // Clear RX interrupt status flag
    UART1_IM_R  |= 0b00010000; // Enable RX interrupts

    //Configure NVIC to allow UART interrupts
    NVIC_PRI1_R |= 0x00002000;//Set UART1 IRQ pri to 1(bits 15-13)
    NVIC_EN0_R |= 0x_______________;//Enable UART0 IRQ (IRQ 5)
}


//TODO
void UART1_handler() {

    // Clear interrupt status register
    GPIO_PORTE_ICR_R |= 0b00000000000000000000000000111111;
    button_event = 1;
    button_num = button_getButton();
}

void uart_sendChar(char data) {

}

char uart_receive(void) {

}
