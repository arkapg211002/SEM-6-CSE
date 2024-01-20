#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 20

// Function to be integrated: ∫[a to b] (1/(1+x)) dx
float f(float x)
{
    return (1 / (1 + x));
}

void main()
{
    int i, n;
    float a, b, h, s, *y, s1 = 0, s2 = 0;

    // Dynamic memory allocation for array y
    y = (float *)malloc(MAX * sizeof(float));

    printf("Enter the lower limit: ");
    scanf("%f", &a);
    printf("Enter the upper limit: ");
    scanf("%f", &b);
    printf("Enter the number of sub intervals: ");
    scanf("%d", &n);

    h = (b - a) / n;

    // Allocate values for the function
    for (i = 0; i <= n; i++)
    {
        y[i] = f(a + i * h);
    }

    // Simpson's 1/3 Rule calculation
    for (i = 1; i < n; i += 2)
    {
        s1 += 4 * y[i];
    }

    for (i = 2; i <= n - 2; i += 2)
    {
        s2 += 2 * y[i];
    }

    s = (h / 3) * (y[0] + y[n] + s1 + s2);

    // Output: Result of the integration
    printf("The result is: %f\n", s);

    // Free allocated memory
    free(y);
}