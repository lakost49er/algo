/*Homework 1
������ �.�.
*/

#include <stdio.h>
#include <math.h>

/*������1
������ ��� � ���� ��������.
���������� � ������� ������ ����� ���� �� ������� I=m/(h*h); ��� m-����� ���� � �����������, h - ���� � ������.
*/

int main(int argc, const char* argv[])
{
    printf("Calc index mass by weight and height\n");

    double weight, height;

    printf("Input weight(kg.) and height(m.) people: ");
    scanf_s("%lf %lf", &weight, &height);

    double index = weight / (height * height);

    printf("index mass (������ ����� ����) = %.2lf\n", index);

    return 0;
}


