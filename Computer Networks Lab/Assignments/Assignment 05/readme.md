#### Write C programs to implement TCP Socket. The client will takea bit-stream from the user and send it to the server. The server will implement bit stuffing and send the stream back to the client. The client will print it.

Read : https://www.geeksforgeeks.org/bit-stuffing-in-computer-network/ </br>
Read : https://www.geeksforgeeks.org/implementation-of-bit-stuffing-and-bit-destuffing/

```c
// Program to return bit stream after bitstuffing 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function for bit stuffing
char* bitStuffing(char* input)
{
    // Allocate memory for the stuffed bit stream
    char* stuffed = (char*)malloc(strlen(input) * 2 + 1); // Maximum possible length after stuffing: input length * 2
    if (stuffed == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Variables to traverse arrays
    int i = 0;
    int j = 0;

    // Loop through the input string
    while (input[i] != '\0') {

        // If the current bit is a set bit
        if (input[i] == '1') {

            // Stores the count of consecutive ones
            int count = 1;

            // Insert into array stuffed[]
            stuffed[j] = input[i];
            j++;

            // Loop to check for next 5 bits
            int k;
            for (k = i + 1; input[k] == '1' && count < 5; k++) {
                stuffed[j] = input[k];
                j++;
                count++;

                // If 5 consecutive set bits are found insert a 0 bit
                if (count == 5) {
                    stuffed[j] = '0';
                    j++;
                }
                i = k;
            }
        }

        // Otherwise insert input[i] into the array stuffed[]
        else {
            stuffed[j] = input[i];
            j++;
        }
        i++;
    }
    // Null-terminate the string
    stuffed[j] = '\0';

    // Return the stuffed bit stream
    return stuffed;
}

// Driver Code
int main()
{
    char input[] = "111111";

    // Call bitStuffing function to get the stuffed bit stream
    char* stuffed = bitStuffing(input);

    // Print the stuffed bit stream as a string
    printf("Stuffed Bit Stream: %s\n", stuffed);

    // Free dynamically allocated memory
    free(stuffed);

    return 0;
}

```
