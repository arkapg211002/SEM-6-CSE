// Checksum Generation from Dataword

#include <stdio.h>
#include <string.h>

// Function to find the One's complement
// of the given binary string
void Ones_complement(char *data) {
    while (*data != '\0') {
        if (*data == '0')
            *data = '1';
        else
            *data = '0';
        data++;
    }
}

// Function to return the checksum value of
// the given string when divided in K size blocks
void checkSum(char *data, int block_size, char *result) {
    // Check data size is divisible by block_size
    // Otherwise add '0' front of the data
    int n = strlen(data);
    if (n % block_size != 0) {
        int pad_size = block_size - (n % block_size);
        char padded_data[1000];
        for (int i = 0; i < pad_size; i++) {
            padded_data[i] = '0';
        }
        strcpy(padded_data + pad_size, data);
        strcpy(data, padded_data);
    }

    // Binary addition of all blocks with carry

    // First block of data stored in result variable
    strncpy(result, data, block_size);
    result[block_size] = '\0';

    // Loop to calculate the block
    // wise addition of data
    for (int i = block_size; i < n; i += block_size) {
        // Stores the data of the next block
        char next_block[1000];
        strncpy(next_block, data + i, block_size);
        next_block[block_size] = '\0';

        // Stores the binary addition of two blocks
        char additions[1000];
        int sum = 0, carry = 0;

        // Loop to calculate the binary addition of
        // the current two blocks of k size
        for (int k = block_size - 1; k >= 0; k--) {
            sum += (next_block[k] - '0') + (result[k] - '0');
            carry = sum / 2;
            if (sum == 0) {
                additions[k] = '0';
                sum = carry;
            } else if (sum == 1) {
                additions[k] = '1';
                sum = carry;
            } else if (sum == 2) {
                additions[k] = '0';
                sum = carry;
            } else {
                additions[k] = '1';
                sum = carry;
            }
        }

        // After binary add of two blocks with carry,
        // if carry is 1 then apply binary addition
        char final[1000];

        if (carry == 1) {
            for (int l = block_size - 1; l >= 0; l--) {
                if (carry == 0) {
                    final[l] = additions[l];
                } else if (((additions[l] - '0') + carry) % 2 == 0) {
                    final[l] = '0';
                    carry = 1;
                } else {
                    final[l] = '1';
                    carry = 0;
                }
            }
            strncpy(result, final, block_size);
            result[block_size] = '\0';
        } else {
            strncpy(result, additions, block_size);
            result[block_size] = '\0';
        }
    }

    // Return One's complements of result value
    // which represents the required checksum value
    Ones_complement(result);
}

// Driver Code
int main() {
    char message[1000];
    int block_size;

    printf("Enter the message (a string of 0s and 1s): ");
    scanf("%s", message);

    printf("Enter the block size: ");
    scanf("%d", &block_size);

    char checksum[1000];
    checkSum(message, block_size, checksum);

    // Print the checksum
    printf("Checksum: %s\n", checksum);

    return 0;
}

