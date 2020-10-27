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
#include <limits.h>
#include <float.h>

    // Prototype for function to repeat print a character
void RepeatChar(char c, int count);

int main(void) {

        // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;

        // Output chart using the constants defined in the limtis and float header file.
    RepeatChar('-', 88);
    printf("| Data Type             | Size (in bytes) | Minimum              | Maximum             |\n");
    RepeatChar('-', 88);
    printf("|character              | %d               | %d                    | %d                 |\n", sizeof(char), CHAR_MIN, CHAR_MAX);
    printf("|short int              | %d               | %d               | %d               |\n", sizeof(short int), SHRT_MIN, SHRT_MAX);
    printf("|int                    | %d               | %d               | %d               |\n", sizeof(int), INT_MIN, INT_MAX);
    printf("|long int               | %d               | %ld          | %ld          |\n", sizeof(long), LONG_MIN, LONG_MAX);
    printf("|long long int          | %d               | %lld | %lld |\n", sizeof(long long), LLONG_MIN, LLONG_MAX);
    printf("|unsigned character     | %d               | 0                    | %d                 |\n", sizeof(unsigned char), UCHAR_MAX);
    printf("|unsigned short int     | %d               | 0                    | %hu               |\n", sizeof(unsigned short int), USHRT_MAX);
    printf("|unsigned int           | %d               | 0                    | %u               |\n", sizeof(unsigned int), UINT_MAX);
    printf("|unsigned long int      | %d               | 0                    | %lu          |\n", sizeof(unsigned long int), ULONG_MAX);
    printf("|unsigned long long int | %d               | 0                    | %llu|\n", sizeof(unsigned long long int), ULLONG_MAX);
    printf("|float                  | %d               | %e         | %e        |\n", sizeof(float), FLT_MIN, FLT_MAX);
    printf("|double                 | %d               | %e        | %e       |\n", sizeof(double), DBL_MIN, DBL_MAX);
    RepeatChar('-', 88);

    return 0;
}

    // Function that takes a character and a count of how
    // many times to print that char.
void RepeatChar(char c, int count)
{
    int i;
    for( i= 0; i < count; i++)
    {
        putchar(c);
    }

    putchar('\n');
}
