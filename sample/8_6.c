#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define M 100
/*
note:
1
2
testfile
*/
int weekday(int year, int month, int day)//Get the number of weekday
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
void f3()
{
	int a;
	unsigned int b;
	a = 5;
	b = 6;
	a = b - 10;
	for (int i = 0; i < 10; i++)
	{
		a = b * i;
	}
	long long k;
	for (int i = 0; i < 10; i++)
	{
		k = b * i;
	}
	a = k;
}
int main()
{
	int n, m, i, j;
	scanf("%d%d", &n, &m);
	char s[M], a[100];
	long long b = 105;
	i = b;
	f3();
	for (int i = 0; i < 10; i++)
	{
		i = b * i;
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			char c = getchar();
			char *temp = (char*)malloc(2 * sizeof(char));
			temp[0] = c;
			temp[1] = 0;
			strcat(s, temp);
		}
	}
	strncpy(s, a, i);
	printf("%s%d%d", i, j);
	return 0;
}