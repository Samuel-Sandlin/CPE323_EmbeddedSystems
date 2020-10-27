/*------------------------------------------------------------------------------
* Instructor:   Aleksander Milenkovic
* Program:      String Counter
* Date:         Aug 26, 2020
* Input:        None
* Output:       Number of each character type in a string
* Description:  This C program takes a string and prints out the
*               number of characters in that string along with
*               number of each type of character.
*-----------------------------------------------------------------------------*/

#include <msp430.h>
#include <stdio.h>


int main(void)
        {
        // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;

       // Max number of chars for our C-string
    const int SIZE = 100;

        // Create C string containing the phrase we want to count
    char STR[SIZE] = "Hello! Welcome to CPE325. It’s a great day, isn’t it?";

        // Create & Initialize Variable to hold string length
    int length = 0;

        // Create and initialize counter variables to hold string data
    int upper = 0;
    int lower = 0;
    int digit = 0;

        // Assign index of string to 0 so we can "scan" the string
    int i = 0;

        /*  Loops until the NULL character is found in the C-string
         *  Performs a series of Range checks on each character to
         *  determine what the character is, then increment its
         *  counter.
         */
    while(STR[i] != '\0')
    {
        length++;

        if(STR[i] >= 'a' && STR[i] <= 'z')
        {
            lower++;
        }

        else if(STR[i] >= 'A' && STR[i] <= 'Z')
        {
            upper++;
        }

        else if(STR[i] >= '0' && STR[i] <= '9')
        {
            digit++;
        }

        i++;
    }

        //  Output contents of string
    printf("String: Hello! Welcome to CPE325. It’s a great day, isn’t it?\n");
    printf("Contains: The string contains %d upper-case and %d lower-case characters and %d digits.\n", upper, lower, digit);

    return 0;
}
