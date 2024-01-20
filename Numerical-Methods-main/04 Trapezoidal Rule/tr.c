#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ∫[0 to 1] (1/(1+x^2)) dx
float f(float x)
{
    return (1 / (1 + (x * x)));
}

void main()
{
    int i, n;
    float l, u, h, s = 0, t;

    // Input: Lower limit
    printf("Enter the lower limit: ");
    scanf("%f", &l);

    // Input: Upper limit
    printf("Enter the upper limit: ");
    scanf("%f", &u);

    // Input: Number of subintervals
    printf("Enter the number of subintervals: ");
    scanf("%d", &n);

    h = (u - l) / n;

    // Calculating the integral using the Trapezoidal Rule
    for (i = 1; i < n; i++)
    {
        s += f(l + (i * h));
    }

    t = (h / 2) * (f(l) + 2 * s + f(u));

    // Output: Result of the integration
    printf("The result is: %f\n", t);
}
