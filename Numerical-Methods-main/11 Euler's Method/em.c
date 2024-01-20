#include <stdio.h>

// Function representing the differential equation dy/dx = f(x, y)
float f(float x, float y)
{
    return x - y;
}

void eulerMethod(float x0, float y0, float h, int n)
{
    float x = x0;
    float y = y0;

    printf("Step\t\t x\t\t y\n");

    for (int i = 0; i <= n; i++)
    {
        printf("%d\t\t %f\t %f\n", i, x, y);

        // Euler's Method formula
        y = y + h * f(x, y);
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

    eulerMethod(x0, y0, h, n);

    return 0;
}
