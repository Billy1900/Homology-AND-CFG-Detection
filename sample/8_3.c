#include<stdio.h> //include
#include<string.h>
#include<stdlib.h>
//define
#define MAX 10
#define f1 (n*n)
typedef int I;
#define f2(a,b) ((a-b)*(a+b))
typedef char C;
/*
a sourcefile for testing
try to pretreat the sourcefile
*/
char result[600];
int a[55];
char var[6];
//x = Maxheight - 1 - 2 * (m - 1 - i) - 3 * k; y = 4 * j + 2 * (m - 1 - i);
//3+2*(m-1-i)+3*a
void cover(int x, int y)
{
	int i = 1, j = 6, a = x, b = y, k = 1;
	printf("%d%s", i);
	a = 5 + j;
	for (j = 0, y = b; j < 7; j++, y++)
	{
		i = j * k;
		for (k = 0; k < 5; k++)
		{
			k = k + 1;
		}
	}
}
void x1()
{
	int i;
	i = 5;
}
void g2()
{
	int i = 1;
	x1();
}
int f3()
{
	I i = 6;
	g2();
	x1();
	return i;
}
int f4()
{
	int j = f3();
	x1();
	g2();
	return f2(6, 5);
}

void g1()
{
	I l = 6, i, j;
	unsigned int r = 7;
	long long k = 3;
	r = l + k;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; i < 10; j++)
		{
			for (k = 0; k < 10; k++)
			{
				r += (l + k)*f2(6, r);
			}
		}
	}
	return;
}
int weekday(int year, int month, int day)
{
	if (month == 1 || month == 2) {
		month += 12;
		year--;
	}
	int c = year / 100;
	int y = year % 100;
	int m = month;
	int d = day;
	int w = c / 4 - 2 * c + y + y / 4 + 26 * (m + 1) / 10 + d - 1;
	if (w < 0)
		return (w + (-w / 7 + 1) * 7) % 7;
	return w % 7;
}
int main()
{
	int i = 100, j = 5;
	char str[10];
	scanf("%d%s", &i, &str);
	char c[100], d[100], e[105];
	char *str1 = (char*)malloc(105 * sizeof(char));
	char *k;
	k = (char*)malloc(i * sizeof(char));
	strncat(str1, d, 10);
	strcpy(d, e);
	g1();
	cover(1, 2);
	printf("%d%n\\1234", j, i);
	return 0;
}