/*------------------------------------------------------------------------------
* Instructor:   Aleksander Milenkovic
* Program:      Print Multiplication Table
* Date:         Aug 24, 2020
* Input:        None
* Output:       Multiplication Table of a single integer
* Description:  This C program takes a defined integer and prints out the
*               multiplication table for that given integer
*-----------------------------------------------------------------------------*/

#include <msp430.h>
#include <stdio.h>

void print_multiplication_table(int);   // prototype for the print func

int main(void)
{
        // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;

        // define a number  for its multiplication table
    unsigned int a = 7;

        // Call the function to print table
    print_multiplication_table(a);

    return 0;
}


    // Prints the multiplication table 1-10
    // of whats passed into it
void print_multiplication_table(int a)
{
    int i;

    for(i = 1; i <= 10; i++)
    {
        printf("%d X %d = %d \n", a, i, a*i);
    }
}
