// Calculate VRC (Vertical Redundancy Check) : 2D parity checking

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define maxlength 10
#define maxmessages 10

void initialize(int arr[][maxlength], int m, int n) {
    srand(time(NULL));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            arr[i][j] = rand() % 2;
}

void print(int arr[][maxlength], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void addparbit(int arr[][maxlength], int m, int n) {
    for (int j = 0; j < n; j++) {
        int count = 0;
        for (int i = 0; i < m; i++) {
            if (arr[i][j] == 1)
                count++;
        }
        arr[m][j] = count % 2 == 0 ? 0 : 1;
    }
}

void induceerror(int arr[][maxlength], int m, int n) {
    int k1, k2;
    k1 = rand() % m;
    k2 = rand() % n;
    arr[k1][k2] = arr[k1][k2] == 0 ? 1 : 0;
    printf("Inducing error at position : (%d, %d)\n", k1, k2);
}

void checkerror(int arr[][maxlength], int m, int n) {
    for (int j = 0; j < n; j++) {
        int count = 0;
        for (int i = 0; i < m; i++) {
            if (arr[i][j] == 1)
                count++;
        }
        if ((count % 2 == 0 && arr[m][j] != 0) || (count % 2 == 1 && arr[m][j] != 1)) {
            printf("Error in column : %d\n", j);
        }
    }
}

int main() {
    int m, n;
    printf("Enter total number of messages: ");
    scanf("%d", &m);
    printf("Enter length of each message: ");
    scanf("%d", &n);

    int arr[maxmessages + 1][maxlength]; // +1 for parity bits
    printf("Enter the messages (each message as a string of 0s and 1s):\n");
    for (int i = 0; i < m; i++) {
        printf("Message %d: ", i + 1);
        char message[maxlength];
        scanf("%s", message);
        for (int j = 0; j < n; j++) {
            arr[i][j] = message[j] - '0';
        }
    }

    // Add parity bits column-wise
    addparbit(arr, m, n);

    // Print original matrix with parity bits
    printf("Matrix with Parity Bits:\n");
    print(arr, m + 1, n);

    // Induce error randomly
    induceerror(arr, m + 1, n);

    // Print matrix after inducing error
    printf("Matrix after Inducing Error:\n");
    print(arr, m + 1, n);

    // Check for errors
    checkerror(arr, m + 1, n);

    return 0;
}
