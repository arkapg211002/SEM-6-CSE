#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 10

void main()
{
    int n, i, j;
    float *x, *y, **f;
    float s = 0, p = 1, X = 0, h = 0, u = 0;

    // Input: Number of data points
    printf("Enter the value of n: ");
    scanf("%d", &n);

    // Dynamic memory allocation for arrays
    x = (float *)malloc(MAX * sizeof(float));
    y = (float *)malloc(MAX * sizeof(float));
    f = (float **)malloc(MAX * sizeof(float *));

    for (i = 0; i < MAX; i++)
    {
        f[i] = (float *)malloc(MAX * sizeof(float));
    }

    // Input: Values of xi and yi
    printf("Enter the values of xi, yi (i=0, 1, 2, ..., n):\n");
    for (i = 0; i <= n; i++)
    {
        printf("Enter x[%d], y[%d]: ", i, i);
        scanf("%f %f", &x[i], &y[i]);
    }

    // Input: Interpolating point X
    printf("Enter the interpolating point X: ");
    scanf("%f", &X);

    // Calculating step size and normalized variable
    h = x[1] - x[0];
    u = (X - x[n]) / h;
    s = y[n];

    // Initializing the first column of the backward difference table
    for (j = 0; j <= n; j++)
    {
        f[0][j] = y[j];
    }

    // Constructing the backward difference table
    for (i = 1; i <= n; i++)
    {
        for (j = i; j <= n; j++)
        {
            f[i][j] = f[i - 1][j] - f[i - 1][j - 1];
        }
    }

    // Calculating the interpolation using Newton's backward difference formula
    for (i = 1; i <= n; i++)
    {
        p = p * (u + i - 1) / i;
        s = s + p * f[i][n];
    }

    // Output: Interpolated value at X
    printf("y(%f): %f\n", X, s);
}
