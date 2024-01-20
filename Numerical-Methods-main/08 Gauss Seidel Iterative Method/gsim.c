#include <stdio.h>
#include <math.h>

#define MAX_SIZE 10
#define EPSILON 1e-6
#define MAX_ITERATIONS 100

void gaussSeidel(float matrix[MAX_SIZE][MAX_SIZE + 1], int n)
{
    int i, j, k;
    float sum, error, x[MAX_SIZE];

    // Initialize solution vector
    for (i = 0; i < n; i++)
    {
        x[i] = 0;
    }

    // Iterative process
    for (k = 0; k < MAX_ITERATIONS; k++)
    {
        error = 0;

        for (i = 0; i < n; i++)
        {
            sum = matrix[i][n];

            for (j = 0; j < n; j++)
            {
                if (i != j)
                {
                    sum -= matrix[i][j] * x[j];
                }
            }

            float temp = x[i];
            x[i] = sum / matrix[i][i];

            // Calculate the error
            error += fabs(x[i] - temp);
        }

        // Check for convergence
        if (error < EPSILON)
        {
            printf("Converged to a solution after %d iterations.\n", k + 1);
            printf("Solution:\n");
            for (i = 0; i < n; i++)
            {
                printf("x%d = %f\n", i + 1, x[i]);
            }
            return;
        }
    }

    printf("Gauss-Seidel method did not converge after %d iterations.\n", MAX_ITERATIONS);
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

    // Apply Gauss-Seidel Iterative Method
    gaussSeidel(matrix, n);

    return 0;
}
