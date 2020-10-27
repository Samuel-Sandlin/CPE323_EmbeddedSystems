/*------------------------------------------------------------------------------
* Instructor:   Aleksander Milenkovic
* Program:      BLINK LEDs
* Date:         September 12, 2020
* Input:        SW1 and SW2
* Output:       LED1 and LED2
* Description:  This C program controls the output LEDs on the msp430 based
*               off input from the two switches:
*               DEFAULT STATE => Green LED on, Red LED Off
*               Hold Switch 1 => Blink Red LED, Turn off Green LED
*               Hold Switch 2 => Blink Green LED, Turn off Red LED
*               Hold Switch 1 & 2 => Alternate Blinking on both LEDs
*-----------------------------------------------------------------------------*/

#include <msp430.h> 

#define REDLED 0x01     // mask for BIT0 = 0000 0001 b
#define GREENLED 0x80   // mask for BIT7 = 1000 0000 b

#define S1 P2IN&BIT1    // S1
#define S2 P1IN&BIT1    // S2

void AlternateBlink();

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	    // Interface LED1 as OUTPUT
	P1DIR |= REDLED;

        // Interface LED2 as OUTPUT
	P4DIR |= GREENLED;

        // Interface SW1 and SW2 as INPUT
	P2DIR &= ~BIT1;
	P2REN |= BIT1;
    P2OUT |= BIT1;

    P1DIR &= ~BIT1;
    P1REN |= BIT1;
    P1OUT |= BIT1;

//*********************************************************

        // Infinite Loop
    for(;;)
    {
        unsigned int i = 0;
	        // LED1(RED) OFF
        P1OUT &= ~REDLED;

	        // LED2(GREEN) ON
        P4OUT |= GREENLED;

        if( (S1) == 0 )
	        {
                    // Debounce 20ms
	            for (i = 2000; i > 0; i--);

	            while((S1) == 0)
	            {
	                    // Check if both are Pressed
	                if( (S2) == 0)
	                {
	                    AlternateBlink();
	                }
	                    // Turn Off Green LED and Toggle RED LED
	                P4OUT &= ~GREENLED;
	                P1OUT ^= REDLED; // P1OUT ^= BIT0;

	                // Delay 0.25s  => 0.25s ON, 0.25s OFF => 0.5s Period = 2Hz
	                // 250ms ON + 250ms OFF = 500ms Cycle = 2Hz
	                __delay_cycles(250000);
	            }
	        }


        if( (S2) == 0)
        {
                // Debounce 20ms
            for (i = 2000; i > 0; i--);

            while((S2) == 0)
            {
                    // Check if Both are pressed
                if( (S1) == 0)
                {
                    AlternateBlink();
                }
                    // Turn RED LED off and Blink GREEN LED
                P1OUT &= ~REDLED;
                P4OUT ^= GREENLED;

                    // 5hz => 1/5 = 0.2s Cycle => 200ms
                    // 100ms ON + 100ms OFF = 200ms Cycle = 5Hz
                __delay_cycles(100000);
            }
        }
    } // END INFINITE LOOP
	return 0;
}

    // Function will only get called inside of the while loops,
    // implying both switches are pressed when this function calls.
void AlternateBlink()
{
    unsigned int i = 0;
        // Debounce 20ms
    for (i = 2000; i > 0; i--);

        // 2nd Check As long as Both of the switches are held
    while( ((S1) == 0) && ((S2) == 0) )
    {
            // 8hz => 1.25 Cycle => LED1 ON 62.5ms => LED2 ON 62.5ms
        P1OUT ^= REDLED;
        __delay_cycles(62500);
        P4OUT ^= GREENLED;
        __delay_cycles(62500);
    }
}
