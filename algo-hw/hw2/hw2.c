/*Homework 2
Крылов К.В.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

void solution00();
void solution01();
void solution02();

void menu();
 
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Rus");
	int select = 0;

	do
	{
		menu();
		scanf("%i", &select);
		switch (select)
		{
		case 1:
			solution00();
			break;
		case 2:
			solution01();
			break;
		case 3:
			solution02();
			break;
		case 0:
			printf("Программа закончила свое выполнение.\n");
			break;
		default:
			printf("Некорректный символ, введите значения из списка меню.\n");
		}
	} while (select != 0);
	system("pause");
	return 0;
}

void menu()
{
	printf("Меню выбора решения задания:\n\n");

	printf("1. Решение задачи 1\n");
	printf("2. Решение задачи 2\n");
	printf("3. Решение задачи 3\n");
	printf("0. Завершение выполнения программы\n");
}

void descriptionTask(char* task)
{
	printf("\n##########################################\n");
	printf("\nУсловие задачи:\n");
	printf(task);
}

void endTask()
{
	printf("\n##########################################\n\n");
}

#define ARR_SIZE 100

void convertToBin(long n, int* bin, int* size)
{
	int i = 0;
	while (n > 0)
	{
		bin[i++] = n % 2;
		n /= 2;
	}
	*size = i;
}

void convertToBinRec(long n, int* bin, int* pos, int* size)
{
	if (n <= 0)
		return;
	bin[*pos] = n % 2;
	*size += 1;
	*pos += 1;
	convertToBinRec(n / 2, bin, pos, size);
}


void binPrint(int* bin, int size)
{
	int i;
	for (i = size - 1; i > 0; i--)
		printf("%d", bin[i]);
	printf("\n");
}

// Задание 1: Реализовать функцию перевода из десятичной системы в двоичную, используя рекурсию.
void solution00()
{
	descriptionTask("Реализовать функцию перевода из десятичной системы в двоичную, используя рекурсию.\n");
	// Ввод данных

	// Задаём значение первого элемента, чтобы обнулить остальные
	int bin[ARR_SIZE] = { 0 };
	int N = 0;
	int size = 0;
	int pos = 0;
	printf("Введите число в десятичной системе для перевода в двоичную: ");
	scanf("%d", &N);

	// Решение
	printf("Результат: ");
	convertToBinRec(N, &bin, &pos, &size);
	binPrint(bin, size);

	endTask();
}

long power(int a, int b)
{
	long p = 1;
	while (b)
	{
		p = p * a;
		b--;
	}
	return p;
}

void powerRec(int a, int b, long* p)
{
	if (b == 0)
		return;
	*p *= a;
	powerRec(a, --b, p);
}

void powerSpeedRec(int a, int b, long* p)
{
	if (!b)
		return;
	if (b % 2 == 0)
	{
		b /= 2;
		a *= a;
	}
	else
	{
		b--;
		*p *= a;
	}
	powerSpeedRec(a, b, p);
}

// Задание 2: Реализовать функцию возведения числа a в степень b:
//				a.без рекурсии;
//				b.рекурсивно;
//				c. *рекурсивно, используя свойство четности степени.
void solution01()
{
	descriptionTask("Реализовать функцию возведения числа a в степень b:\n\ta.без рекурсии;\n\tb.рекурсивно;\n\tc. *рекурсивно, используя свойство четности степени.\n");
	// Ввод данных
	int N = 0;
	int P = 0;
	printf("Введите число: ");
	scanf("%d", &N);
	printf("Введите степень: ");
	scanf("%d", &P);
	// Решение
	printf("Результат: ");

	long res = power(N, P);
	printf("Без рекурсии: %d^%d = %d\n", N, P, res);

	res = 1;
	powerRec(N, P, &res);
	printf("С рекурсией: %d^%d = %d\n", N, P, res);

	res = 1;
	powerSpeedRec(N, P, &res);
	printf("Ускоренное возведение: %d^%d = %d\n", N, P, res);
	endTask();
}

#define FIRST_PROGRAM(X) X+1
#define SECOND_PROGRAM(X) X*2

#define START_VALUE 3
#define END_VALUE 20

typedef struct node {
	int value;
	int nProgram;
	struct node* prev;
} Node;

void getCountProgram(Node prevNode, int* count)
{
	int next1 = FIRST_PROGRAM(prevNode.value);
	if (next1 == END_VALUE)
	{
		*count += 1;
		Node node = prevNode;
		printf("%d(%d)->", END_VALUE, 1);
		while (node.prev != NULL)
		{
			printf("%d(%d)->", node.value, node.nProgram);
			node = *node.prev;
		}
		printf("%d\n", START_VALUE);
	}
	if (next1 < END_VALUE) {
		Node nextNode1 = { next1, 1, &prevNode };
		getCountProgram(nextNode1, count);
	}

	int next2 = SECOND_PROGRAM(prevNode.value);
	if (next2 == END_VALUE)
	{
		*count += 1;
		Node node = prevNode;
		printf("%d(%d)->", END_VALUE, 2);
		while (node.prev != NULL)
		{
			printf("%d(%d)->", node.value, node.nProgram);
			node = *node.prev;
		}
		printf("%d\n", START_VALUE);
	}
	if (next2 < END_VALUE) {
		Node nextNode2 = { next2, 2, &prevNode };
		getCountProgram(nextNode2, count);
	}
}

int getCount()
{
	int size = 1;
	int count = 0;
	int* temp[10000] = { START_VALUE };

	while (size > 0)
	{
		int* subArray[10000];
		int pos = 0;

		for (int i = 0; i < size; i++)
		{
			int value = temp[i];
			int next1 = FIRST_PROGRAM(value);
			if (next1 == END_VALUE)
			{
				count += 1;
			}
			if (next1 < END_VALUE)
			{
				subArray[pos++] = next1;
			}

			int next2 = SECOND_PROGRAM(value);
			if (next2 == END_VALUE)
			{
				count += 1;
			}
			if (next2 < END_VALUE)
			{
				subArray[pos++] = next2;
			}
		}

		size = pos;
		for (int i = 0; i < size; i++)
		{
			temp[i] = subArray[i];
		}
	}
	return count;
}

// Задание 3: Исполнитель Калькулятор преобразует целое число, записанное на экране. У исполнителя две команды, каждой команде присвоен номер:
//				Прибавь 1
//				Умножь на 2
//				Первая команда увеличивает число на экране на 1, вторая увеличивает это число в 2 раза.Сколько существует программ, которые число 3 преобразуют в число 20 ?
//				а) с использованием массива;
//				б) с использованием рекурсии.
//				Реализовать меню с выбором способа заполнения массива : из файла, случайными числами, с клавиатуры.
void solution02()
{
	descriptionTask("Исполнитель Калькулятор преобразует целое число, записанное на экране. У исполнителя две команды, каждой команде присвоен номер:\n\tПрибавь 1\n\tУмножь на 2\n\tПервая команда увеличивает число на экране на 1, вторая увеличивает это число в 2 раза.Сколько существует программ, которые число 3 преобразуют в число 20 ?\n\tа) с использованием массива;\n\tб) с использованием рекурсии.\n\tРеализовать меню с выбором способа заполнения массива : из файла, случайными числами, с клавиатуры.\n");
	// Ввод данных

	// Решение
	printf("Результат: \n");
	int count = 0;
	Node startNode = { START_VALUE, 0, NULL };
	getCountProgram(startNode, &count);
	printf("%d программ методом с рекурсией.\n", count);
	printf("%d программ методом без рекурсии.\n", getCount());
	endTask();
}