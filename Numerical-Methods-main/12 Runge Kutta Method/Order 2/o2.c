#include <stdio.h>

// Function representing the differential equation dy/dx = f(x, y)
float f(float x, float y)
{
    return ((x * x) + (y * y));
}

// Second-order Runge-Kutta method (Midpoint method) implementation
void rungeKutta2(float x0, float y0, float h, int n)
{
    float x = x0;
    float y = y0;

    printf("Step\t\t x\t\t y\n");

    for (int i = 0; i <= n; i++)
    {
        printf("%d\t\t %f\t %f\n", i, x, y);

        // Runge-Kutta formulas (Order 2)
        float k1 = h * f(x, y);
        float k2 = h * f(x + h, y + k1);

        y = y + (k1 + k2) / 2;
        x = x + h;
    }
}

int main()
{
    float x0, y0, h;
    int n;

    printf("Enter initial values (x0, y0): ");
    scanf("%f %f", &x0, &y0);

    printf("Enter step size (h): ");
    scanf("%f", &h);

    printf("Enter the number of steps (n): ");
    scanf("%d", &n);

    rungeKutta2(x0, y0, h, n);

    return 0;
}
