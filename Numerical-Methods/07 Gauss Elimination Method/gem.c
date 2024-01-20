#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

void gaussianElimination(float matrix[MAX_SIZE][MAX_SIZE + 1], int n)
{
    int i, j, k;

    // Forward Elimination
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            float factor = matrix[j][i] / matrix[i][i];

            for (k = i; k <= n; k++)
            {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }

    // Backward Substitution
    for (i = n - 1; i >= 0; i--)
    {
        matrix[i][n] /= matrix[i][i];

        for (j = i - 1; j >= 0; j--)
        {
            matrix[j][n] -= matrix[j][i] * matrix[i][n];
        }
    }
}

void printMatrix(float matrix[MAX_SIZE][MAX_SIZE + 1], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int n;

    printf("Enter the number of equations: ");
    scanf("%d", &n);

    float matrix[MAX_SIZE][MAX_SIZE + 1];

    // Input coefficients and constants
    printf("Enter the augmented matrix coefficients:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            printf("Enter element matrix[%d][%d]: ", i, j);
            scanf("%f", &matrix[i][j]);
        }
    }

    // Apply Gaussian Elimination
    gaussianElimination(matrix, n);

    // Output the solution
    printf("The solution is:\n");
    for (int i = 0; i < n; i++)
    {
        printf("x%d = %f\n", i + 1, matrix[i][n]);
    }

    return 0;
}
