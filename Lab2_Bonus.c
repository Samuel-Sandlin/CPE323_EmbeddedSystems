/*------------------------------------------------------------------------------
* Instructor:   Aleksander Milenkovic
* Program:      Size and Range of Data Types
* Date:         September 6, 2020
* Input:        None
* Output:       Chart Containing all the sizes and ranges of C data Types
* Description:  This C program creates a table listing all the C data types,
*               there size in bytes, minimum range value, and maximum
*               range value.
*-----------------------------------------------------------------------------*/
#include <msp430.h>
#include <stdio.h>

int main(void) {

        // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;

    const int SIZE = 8;

        // Initialize first 8 X 8 Array
   long int X[SIZE][SIZE] = {
                  { 1,  2,  3,  4,  5,  6,  7,  8  },
                  { 9,  10, 11, 12, 13, 14, 15, 16 },
                  { 17, 18, 19, 20, 21, 22, 23, 24 },
                  { 25, 26, 27, 28, 29, 30, 31, 32 },
                  { 33, 34, 35, 36, 37, 38, 39, 40 },
                  { 41, 42, 43, 44, 45, 46, 47, 48 },
                  { 49, 50, 51, 52, 53, 54, 55, 56 },
                  { 57, 58, 59, 60, 61, 62, 63, 64 }
                  };


        // Initialize first 8 X 8 Array
    long int Y[SIZE][SIZE] = {
                  { 73, 74, 75, 76, 77, 78, 79, 80 },
                  { 81, 82, 83, 84, 85, 86, 87, 88 },
                  { 89, 90, 91, 92, 93, 94, 95, 96 },
                  { 97, 98, 99, 10,  1, 12, 13, 04 },
                  {  5,  6,  7, 18,  9, 10, 11, 12 },
                  { 13, 14, 15,  6, 17, 18, 19, 20 },
                  { 21, 22, 23, 14, 25, 16, 17, 28 },
                  { 29,  0, 31, 12, 33, 14, 35, 36 }
                  };

        // Declare New 8 x 8 Array to store result.
    long int z[SIZE][SIZE] = { 0 };


    int i, j, k;

        // Output Matrix X
    printf("\n\t MATRIX X: \n\n");

    for(i = 0; i < SIZE; i++)
    {
        printf(" |\t");

        for(j = 0; j < SIZE - 1; j++)
        {
            printf("%d\t", X[i][j]);
        }

        printf("%d\t|\n", X[i][j]);
    }
    printf("\n\n\n");


        // Output Matrix Y
    printf("\t MATRIX Y: \n\n");

    for(i = 0; i < SIZE; i++)
        {
            printf(" |\t");

            for(j = 0; j < SIZE - 1; j++)
            {
                printf("%d\t", Y[i][j]);
            }

            printf("%d\t|\n", Y[i][j]);
        }
    printf("\n\n\n");




        // Multiply the Matrix ( Row * Column)

        // Start on Row 0
    for(i = 0; i < SIZE; i++)
    {
            // Start on Column 0
        for(j = 0; j < SIZE; j++)
        {
                // 3rd for loop allows you to traverse
                //
            for(k = 0; k < SIZE; k++)
            {
                z[i][j] = X[i][k] * Y[k][j] + z[i][j];
            }
        }
    }


    // Output Matrix Z
        printf("\t MATRIX Z = XY: \n\n");

        for(i = 0; i < SIZE; i++)
            {
                printf(" |\t");

                for(j = 0; j < SIZE - 1; j++)
                {
                    printf("%d\t", z[i][j]);
                }

                printf("%d\t|\n", z[i][j]);
            }

    return 0;
}
