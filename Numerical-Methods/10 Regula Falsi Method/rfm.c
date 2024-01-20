#include <stdio.h>
#include <math.h>

#define EPSILON 1e-6
#define MAX_ITERATIONS 100

// Function for which we want to find the root
float function(float x)
{
    return pow(x, 3) - 5 * x + 1;
}

void regulaFalsi(float a, float b)
{
    float c, fa, fb, fc;
    int iteration;

    for (iteration = 1; iteration <= MAX_ITERATIONS; iteration++)
    {
        fa = function(a);
        fb = function(b);

        if (fabs(fa - fb) < EPSILON)
        {
            printf("Solution found after %d iterations.\n", iteration - 1);
            printf("Root: %f\n", c);
            return;
        }

        c = (a * fb - b * fa) / (fb - fa);
        fc = function(c);

        if (fabs(fc) < EPSILON)
        {
            printf("Solution found after %d iterations.\n", iteration);
            printf("Root: %f\n", c);
            return;
        }

        if (fa * fc < 0)
        {
            b = c;
        }
        else
        {
            a = c;
        }
    }

    printf("Regula Falsi method did not converge after %d iterations.\n", MAX_ITERATIONS);
}

int main()
{
    float a, b;

    printf("Enter the initial interval [a, b]: ");
    scanf("%f %f", &a, &b);

    regulaFalsi(a, b);

    return 0;
}
