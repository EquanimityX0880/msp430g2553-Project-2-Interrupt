#include <msp430.h> 

int a;

#pragma vector = PORT1_VECTOR
__interrupt void Port1(void)
{
    if(P1IFG & BIT5)
    {
        P1IFG &= ~BIT5;
        for(a = 0; a < 3; a++)
        {
            P2OUT = BIT0 | BIT2 | BIT4| BIT6;
            __delay_cycles(200000);
            P2OUT = BIT1 | BIT3 | BIT5 | BIT7;
            __delay_cycles(200000);
            P2OUT = 0x00;
        }
        //P1IFG &= ~BIT5;
    }

    else if(P1IFG & BIT6)
    {
        P1IFG &= ~BIT6;
        for(a = 0; a < 2; a++)
        {
            P2OUT = BIT7;
            __delay_cycles(200000);
            P2OUT = BIT6;
            __delay_cycles(200000);
            P2OUT = BIT5;
            __delay_cycles(200000);
            P2OUT = BIT4;
            __delay_cycles(200000);
            P2OUT = BIT3;
            __delay_cycles(200000);
            P2OUT = BIT2;
            __delay_cycles(200000);
            P2OUT = BIT1;
            __delay_cycles(200000);
            P2OUT = BIT0;
            __delay_cycles(200000);
            P2OUT = 0x00;
        }
        //P1IFG &= ~BIT6;
    }

    // Button 3 (Bit7)
    else if(P1IFG & BIT7)
    {
        P1IFG &= ~BIT7;
        for(a = 0; a < 2; a++)
        {
            P2OUT = BIT0;
            __delay_cycles(200000);
            P2OUT = BIT1;
            __delay_cycles(200000);
            P2OUT = BIT2;
            __delay_cycles(200000);
            P2OUT = BIT3;
            __delay_cycles(200000);
            P2OUT = BIT4;
            __delay_cycles(200000);
            P2OUT = BIT5;
            __delay_cycles(200000);
            P2OUT = BIT6;
            __delay_cycles(200000);
            P2OUT = BIT7;
            __delay_cycles(200000);
            P2OUT = 0x00;
        }
        //P1IFG &= ~BIT7;
    }

}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// to use p2.6 and p2.7
	P2SEL = 0;
	P2SEL2 = 0;

    P1DIR &= ~(BIT5 | BIT6 | BIT7);
    P1REN |= BIT5 | BIT6 | BIT7;
    P1OUT |= BIT5 | BIT6 | BIT7;

    // flash to ensure reset works
	P2DIR = 0xFF;
	P2OUT = 0xFF;
    __delay_cycles(300000);
    P2OUT = 0x00;
    __delay_cycles(300000);

    // Interrupt
	P1IE |= (BIT5 | BIT6 | BIT7); // Input
	P1IES |= (BIT5 | BIT6 | BIT7); // edge
	P1IFG &= ~(BIT5 | BIT6 | BIT7); // Interrupt Flag, use software to reset
	__bis_SR_register(LPM4_bits+GIE); // LPM4 w/interrupt

	return 0;
}
