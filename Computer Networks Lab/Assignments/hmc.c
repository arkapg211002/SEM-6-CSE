// Codeword by applying hamming code correction technique

#include <stdio.h>
#include <string.h>
#include <math.h>

// Store input bits
int input[32];

// Store hamming code
int code[32];

int ham_calc(int, int);
void solve(char *);

// Function to calculate bit for ith position
int ham_calc(int position, int c_l) {
    int count = 0, i, j;
    i = position - 1;

    // Traverse to store Hamming Code
    while (i < c_l) {
        for (j = i; j < i + position; j++) {
            // If current bit is 1
            if (code[j] == 1)
                count++;
        }
        // Update i
        i = i + 2 * position;
    }
    if (count % 2 == 0)
        return 0;
    else
        return 1;
}

// Function to calculate hamming code
void solve(char *data) {
    int n = strlen(data);
    int i, p_n = 0, c_l, j, k;
    i = 0;

    // Find msg bits having set bit
    // at x'th position of number
    while (n > (int)pow(2, i) - (i + 1)) {
        p_n++;
        i++;
    }

    c_l = p_n + n;

    j = k = 0;

    // Traverse the msgBits
    for (i = 0; i < c_l; i++) {
        // Update the code
        if (i == ((int)pow(2, k) - 1)) {
            code[i] = 0;
            k++;
        }
        // Update the code[i] to the input character at index j
        else {
            code[i] = data[j] - '0';
            j++;
        }
    }

    // Traverse and update the hamming code
    for (i = 0; i < p_n; i++) {
        // Find current position
        int position = (int)pow(2, i);
        // Find value at current position
        int value = ham_calc(position, c_l);
        // Update the code
        code[position - 1] = value;
    }

    // Print the Hamming Code
    printf("\nThe generated Code Word is: ");
    for (i = 0; i < c_l; i++) {
        printf("%d", code[i]);
    }
    printf("\n");
}

// Driver Code
int main() {
    char data[32];
    printf("Enter the data word (a string of 0s and 1s): ");
    scanf("%s", data);
    getchar(); // Clear input buffer
    solve(data);
    return 0;
}
