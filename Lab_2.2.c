/*------------------------------------------------------------------------------
* Instructor:   Aleksander Milenkovic
* Program:      Dot Product
* Date:         September, 6 2020
* Input:        None
* Output:       Dot Product of 2 defined arrays
* Description:  This C program calculates the dot product of 2 arrays
*               that are hard coded into the program.
*-----------------------------------------------------------------------------*/
#include <msp430.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>


int main(void) {
        // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;

        // Declare two integer Arrays x and y
    int x[] = { 5, 6, 7, 8, 9};
    int y[] = { 10, 11, 12, 13, 14};

        // Initialize dot product to Zero
    int dotProduct = 0;

        // Assuming both arrays are going to be the same size
        // if we take the dot product, so get the size of one.
    int size = sizeof(x)/2;

        // Multiply corresponding elements in the arrays
        // And sum them for the dot product.
    int i;
    for( i = 0; i < size; i++)
    {
        dotProduct = x[i] * y[i] + dotProduct;
    }

        // Print Original Arrays
    printf("Input Array X: [");
    for( i = 0; i < size - 1; i++)
    {
        printf(" %d,", x[i]);
    }
    printf(" %d ]\n", x[i]);


    printf("Input Array Y: [");
    for( i = 0; i < size - 1; i++)
    {
        printf(" %d,", y[i]);
    }
    printf(" %d ]\n", y[i]);


        // Output Dot Product
    printf("Dot Product is: %d", dotProduct);

    return 0;
}
