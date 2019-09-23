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
long long cmp(long long a, char c, long long b)
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
void f3()
{
	int x;
	unsigned int y;
	x = 5;
	y = 6;
	x = y - 10;
	for (int i = 0; i < 10; i++)
	{
		x = y * i;
	}
	long long k;
	for (int i = 0; i < 10; i++)
	{
		k = x * i;
	}
	x = k;
}
unsigned long long input()
{
	char c = getchar();
	unsigned long long x = 0;
	while (c >= '0'&&c <= '9')
	{
		x = x * 10 + c - '0';
		c = getchar();
		if (c == '\r') c = getchar();
	}
	return x;
}
int main()
{
	int n = input();
	int k, m, sum, j;
	scanf("%d", &k);
	int next;
	m = k + 1;
	while (1)
	{
		sum = 0;
		next = 0;
		while (1)
		{
			next = (next + m - 1) % (2 * k - sum);
			if (next < k) break;
			else sum++;
			if (sum == k)
			{
				printf("%d\n", m);
				return 0;
			}
		}
		m++;
		j = m % (2 * k);
		if (j <= k && j >= 1)
		{
			m = m + k - j + 1;
		}
	}
	char s[1000], *str;
	str = (char*)malloc(M * sizeof(char));
	scanf("%s", s);
	printf("%s", s);
	strcat(str, s);
	int i;
	scanf("%d", &i);
	switch (i)
	{
	case 0:
		n = input();
		break;
	case 1:
		i = input();
		break;
	case 2:
		f3();
		break;
	default:
		printf("%d%n");
		break;
	}
	return 0;
}