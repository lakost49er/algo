/*Homework 1
Крылов К.В.
*/

#include <stdio.h>
#include <math.h>

/*Задача1
Ввести вес и рост человека.
Рассчитать и вывести индекс массы тела по формуле I=m/(h*h); где m-масса тела в килограммах, h - рост в метрах.
*/

int main(int argc, const char* argv[])
{
    printf("Calc index mass by weight and height\n");

    double weight, height;

    printf("Input weight(kg.) and height(m.) people: ");
    scanf_s("%lf %lf", &weight, &height);

    double index = weight / (height * height);

    printf("index mass (индекс массы тела) = %.2lf\n", index);

    return 0;
}


