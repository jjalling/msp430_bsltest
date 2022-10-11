#include <msp430.h>				

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |=  BIT0; // Green LED

    P4DIR &= ~BIT5; // Button
    P4REN |=  BIT5;
    P4OUT |=  BIT5;

    P4DIR |=  BIT6; // Red LED
    P4OUT &= ~BIT6;

    unsigned int i = 0;

    for (;;)
    {
        P1OUT ^= BIT0;
        for(i = 0; i < 20000; i++);

        if (!(P4IN & BIT5)) // Enter BSL mode if S1 is held
        {
            P4OUT = BIT6;
            __disable_interrupt();
            ((void ( * )())0x1000)();
        }

    }
}
