#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 20

void main()
{
    int i, n, j;
    float *x, *y, *d, **a, u = 1.0, s = 0.0;

    // Dynamic memory allocation for arrays
    x = (float *)malloc(MAX * sizeof(float));
    y = (float *)malloc(MAX * sizeof(float));
    d = (float *)malloc(MAX * sizeof(float));
    a = (float **)malloc(MAX * sizeof(float *));

    for (i = 0; i < MAX; i++)
    {
        a[i] = (float *)malloc(MAX * sizeof(float));
    }

    // Input: Number of data points
    printf("Enter the value of n: ");
    scanf("%d", &n);

    // Input: Values of xi and yi (i=1, 2, 3, ..., n)
    printf("Enter the values of xi, yi (i=1, 2, 3, ..., n):\n");
    for (i = 1; i <= n; i++)
    {
        printf("Enter x[%d] y[%d]: ", i, i);
        scanf("%f %f", &x[i], &y[i]);
    }

    // Input: Interpolating point
    printf("Enter the interpolating point: ");
    scanf("%f", &x[0]);

    // Calculation of Lagrange interpolation polynomial
    for (i = 1; i <= n; i++)
    {
        d[i] = 1.0;

        // Building the difference array and denominator for Lagrange polynomial
        for (j = 1; j <= n; j++)
        {
            if (i == j)
                a[i][j] = x[0] - x[i];
            else
                a[i][j] = x[i] - x[j];

            // Update the product of differences for denominator
            d[i] = d[i] * a[i][j];
        }

        // Update the Lagrange polynomial term
        s = s + y[i] / d[i];
        u = u * a[i][i];
    }

    // Output: Interpolated value at the interpolating point
    printf("y(%f): %f\n", x[0], (u * s));
}
