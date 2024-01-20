#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 10

void main()
{
    int i, n, j;
    float *x, *y;
    float s = 0, p = 1, X = 0, h = 0, u = 0, **f;

    // Newton's Forward Difference Interpolation Formula:
    // This program implements Newton's Forward Difference Interpolation Formula,
    // a method for constructing an interpolating polynomial based on the divided
    // difference scheme. It is particularly useful for equidistant data points.

    // Input: Number of data points
    printf("Enter the value of n: ");
    scanf("%d", &n);

    // Dynamic memory allocation for arrays
    x = (float *)malloc(MAX * sizeof(float));
    y = (float *)malloc(MAX * sizeof(float));
    f = (float **)malloc(MAX * sizeof(float *));

    // Allocating memory for the forward difference table
    for (i = 0; i <= MAX; i++)
    {
        f[i] = (float *)malloc(MAX * sizeof(float));
    }

    // Input: Values of xi and yi
    printf("\nEnter the values of xi and yi (i=0, 1, 2, ..., n):\n");
    for (i = 0; i <= n; i++)
    {
        printf("Enter value for x[%d], y[%d]: ", i, i);
        scanf("%f %f", &x[i], &y[i]);
    }

    // Input: Interpolating point X
    printf("Enter the value of interpolating point X: ");
    scanf("%f", &X);

    // Calculating step size and normalized variable
    h = x[1] - x[0];
    u = (X - x[0]) / h;

    // Initializing the first column of the forward difference table
    s = y[0];
    for (j = 0; j <= n; j++)
    {
        f[0][j] = y[j];
    }

    // Constructing the forward difference table
    for (i = 1; i <= n; i++)
    {
        for (j = 0; j <= n - i; j++)
        {
            // Compute the ith order forward differences
            f[i][j] = f[i - 1][j + 1] - f[i - 1][j];
        }
    }

    // Calculating the interpolation using Newton's forward difference formula
    for (i = 1; i <= n; i++)
    {
        p = p * (u - i + 1) / i;
        s = s + p * f[i][0];
    }

    // Output: Interpolated value at X
    printf("\ny(%f): %f\n", X, s);
}
