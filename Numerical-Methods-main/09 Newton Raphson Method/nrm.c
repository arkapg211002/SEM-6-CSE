#include <stdio.h>
#include <math.h>

#define EPSILON 1e-6
#define MAX_ITERATIONS 100

// Function for which we want to find the root
float function(float x)
{
    return exp(x) - 3 * x;
}

// Derivative of the function
float derivative(float x)
{
    return exp(x) - 3; // Corrected derivative
}

void newtonRaphson(float initialGuess)
{
    float x = initialGuess;
    int iteration;

    for (iteration = 1; iteration <= MAX_ITERATIONS; iteration++)
    {
        float f = function(x);
        float fPrime = derivative(x);

        // Check for division by zero
        if (fPrime == 0)
        {
            printf("Division by zero. Newton-Raphson method failed.\n");
            return;
        }

        float deltaX = -f / fPrime;
        x += deltaX;

        // Check for convergence
        if (fabs(deltaX) < EPSILON)
        {
            printf("Converged to a root after %d iterations.\n", iteration);
            printf("Root: %f\n", x);
            return;
        }
    }

    printf("Newton-Raphson method did not converge after %d iterations.\n", MAX_ITERATIONS);
}

int main()
{
    float initialGuess;

    printf("Enter the initial guess: ");
    scanf("%f", &initialGuess);

    newtonRaphson(initialGuess);

    return 0;
}
