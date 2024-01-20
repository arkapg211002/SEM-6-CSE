#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 20

// Function to be integrated: 1 / (1 + x^2)
float f(float x)
{
    return 1 / (1 + (x * x));
}

void main()
{
    int i, n;
    float a, b, h, s, x, *y, s1 = 0, s2 = 0, s3 = 0, s4 = 0;

    // Dynamic memory allocation for array y
    y = (float *)malloc(MAX * sizeof(float));

    printf("Enter the lower limit: ");
    scanf("%f", &a);
    printf("Enter the upper limit: ");
    scanf("%f", &b);
    printf("Enter the number of sub-intervals: ");
    scanf("%d", &n);

    h = (b - a) / n;
    x = a;

    // Calculate function values at each sub-interval
    for (i = 0; i <= n; i++)
    {
        y[i] = f(x);
        x += h;
    }

    // Apply Weddle's Rule
    for (i = 0; i <= n - 6; i += 6)
    {
        s1 += (y[i + 2] + y[i + 4]);
        s2 += (y[i + 1] + y[i + 5]);
        s3 += y[i + 3];
    }
    for (i = 0; i <= n - 12; i += 6)
    {
        s4 += y[i + 6];
    }

    // Final result using Weddle's Rule
    s = (3 * h / 10) * (y[0] + y[n] + s1 + (5 * s2) + (6 * s3) + (2 * s4));

    // Output: Result of the integration
    printf("The result is: %f\n", s);

    // Free allocated memory
    free(y);
}
