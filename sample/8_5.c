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
void Insert_node(int low, int high, int parent, int &rt)
{
	if (low > high) return;
	int mid = (low + high) / 2;
	int data = mid;
	int num = high - low + 1;
	int paren = parent;
	rt = mid;
	Insert_node(low, mid - 1, mid, data);
	Insert_node(mid + 1, high, mid, mid);
}
long long compute(long long a, char c, long long b)
{
	int i;
	long long x;
	switch (c)
	{
	case '+':
		x = a + b; break;
	case '-':
		x = a - b; break;
	case '*':
		x = a * b; break;
	case '^':
		x = a;
		for (i = 1; i < b; i++)
			x = x * a;
		break;
	}
	return x;
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
int f33()
{
	int i = 6;
	f33();
	return i;
}
int main()
{
	int i, j = f33();
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
	return 0;
}