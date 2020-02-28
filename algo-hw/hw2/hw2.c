/*Homework 2
������ �.�.
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
			printf("��������� ��������� ���� ����������.\n");
			break;
		default:
			printf("������������ ������, ������� �������� �� ������ ����.\n");
		}
	} while (select != 0);
	system("pause");
	return 0;
}

void menu()
{
	printf("���� ������ ������� �������:\n\n");

	printf("1. ������� ������ 1\n");
	printf("2. ������� ������ 2\n");
	printf("3. ������� ������ 3\n");
	printf("0. ���������� ���������� ���������\n");
}

void descriptionTask(char* task)
{
	printf("\n##########################################\n");
	printf("\n������� ������:\n");
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

// ������� 1: ����������� ������� �������� �� ���������� ������� � ��������, ��������� ��������.
void solution00()
{
	descriptionTask("����������� ������� �������� �� ���������� ������� � ��������, ��������� ��������.\n");
	// ���� ������

	// ����� �������� ������� ��������, ����� �������� ���������
	int bin[ARR_SIZE] = { 0 };
	int N = 0;
	int size = 0;
	int pos = 0;
	printf("������� ����� � ���������� ������� ��� �������� � ��������: ");
	scanf("%d", &N);

	// �������
	printf("���������: ");
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

// ������� 2: ����������� ������� ���������� ����� a � ������� b:
//				a.��� ��������;
//				b.����������;
//				c. *����������, ��������� �������� �������� �������.
void solution01()
{
	descriptionTask("����������� ������� ���������� ����� a � ������� b:\n\ta.��� ��������;\n\tb.����������;\n\tc. *����������, ��������� �������� �������� �������.\n");
	// ���� ������
	int N = 0;
	int P = 0;
	printf("������� �����: ");
	scanf("%d", &N);
	printf("������� �������: ");
	scanf("%d", &P);
	// �������
	printf("���������: ");

	long res = power(N, P);
	printf("��� ��������: %d^%d = %d\n", N, P, res);

	res = 1;
	powerRec(N, P, &res);
	printf("� ���������: %d^%d = %d\n", N, P, res);

	res = 1;
	powerSpeedRec(N, P, &res);
	printf("���������� ����������: %d^%d = %d\n", N, P, res);
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

// ������� 3: ����������� ����������� ����������� ����� �����, ���������� �� ������. � ����������� ��� �������, ������ ������� �������� �����:
//				������� 1
//				������ �� 2
//				������ ������� ����������� ����� �� ������ �� 1, ������ ����������� ��� ����� � 2 ����.������� ���������� ��������, ������� ����� 3 ����������� � ����� 20 ?
//				�) � �������������� �������;
//				�) � �������������� ��������.
//				����������� ���� � ������� ������� ���������� ������� : �� �����, ���������� �������, � ����������.
void solution02()
{
	descriptionTask("����������� ����������� ����������� ����� �����, ���������� �� ������. � ����������� ��� �������, ������ ������� �������� �����:\n\t������� 1\n\t������ �� 2\n\t������ ������� ����������� ����� �� ������ �� 1, ������ ����������� ��� ����� � 2 ����.������� ���������� ��������, ������� ����� 3 ����������� � ����� 20 ?\n\t�) � �������������� �������;\n\t�) � �������������� ��������.\n\t����������� ���� � ������� ������� ���������� ������� : �� �����, ���������� �������, � ����������.\n");
	// ���� ������

	// �������
	printf("���������: \n");
	int count = 0;
	Node startNode = { START_VALUE, 0, NULL };
	getCountProgram(startNode, &count);
	printf("%d �������� ������� � ���������.\n", count);
	printf("%d �������� ������� ��� ��������.\n", getCount());
	endTask();
}