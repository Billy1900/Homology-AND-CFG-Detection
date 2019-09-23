#include<stdio.h> //include
#include<string.h>
#include<stdlib.h>
//define
#define MAX 10
#define x1 (n*n)
typedef int I;
#define x2(a) ((a-1)*2)
typedef char C;
/*
a sourcefile for testing
try to pretreat the sourcefile
*/
char result[600];
int a[55];
char var[6];
void f1()
{
	int i;
	int n = 5;
	i = x1 * 2;
	i = 5;
}
void f2()
{
	int i = 1;
	i = x2(5, 6);
	f1();
}
int f3()
{
	int i = 6;
	f2();
	f1();
	return i;
}
void cover(int x, int y)
{
	int i, j, a = x, b = y;
	for (i = 5; i >= 0; i--, x--)
		for (j = 0, y = b; j < 7; j++, y++)
		{
			a = i * j;
		}
}
int main()
{
	int a, m, n, i, j, k, x, y;
	scanf("%d%d", &m, &n);
	int Maxwidth = x2(m) + (n - 1) * 4 + 7; //����
	int Maxheight = x2(m) + 3;
	f3();
	f2();
	f1();
	char code[110];
	scanf("%s",code);
	j = f3();
	a = 5;
	long long c = 6;
	a = a + c;
	unsigned int b;
	b = a * c;
	char s[100], v[105];
	{
		char* m;
		m = (char*)malloc(100 * sizeof(char));
		strcat(m, s);
	}
	b = a + c;
	strncpy(s, v, b);
	printf("%s", j);
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			i = i * j;
		}
	}
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			i = i + j;
		}
	}
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
		{
			Maxheight = 3 + 2 * (m - 1 - i) + 3 * i;//�߶�
		}
	int q, w, e;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			for (k = 0; k < 10; k++)
			{
				x = Maxheight - 1 - 2 * (m - 1 - i) - 3 * k;
				y = 4 * j + 2 * (m - 1 - i);
				cover(x, y);
			}
	return 0;
}