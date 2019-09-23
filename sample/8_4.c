#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define M 100
/*
note:
1
2
3
*/
void f1()
{
	int i;
	i = 5;
}
void f2()
{
	int i = 1;
	f1();
}
int f3()
{
	int i = 6;
	f2();
	f1();
	return i;
}
int f4()
{
	int j = f3();
	f1();
	f2();
}
void f5()
{
	unsigned int i = -1;
	int j = i;
	short k = 6;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			k += i * j;
		}
	}
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
int f33()
{
	int i = 6;
	f1();
	f2();
	f3();
	return i;
}
int main()
{
	f4();
	f2();
	int i, j = f3();
	int a = 5;
	long long c = 6;
	a = a + c;
	unsigned int b;
	b = a * c;
	char s[M], v[105];
	char* m;
	m = (char*)malloc(100 * sizeof(char));
	b = a + c;
	strncpy(s, v, b);
	strcat(m, s);
	printf("%s%n", j);
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
	int result = weekday(1999, 2, 16);
	printf("%d", result);
	f1();
	return 0;
}