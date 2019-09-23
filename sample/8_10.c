#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
unsigned long long C(int m, int n)
{
	unsigned long long k, i, molecule = 1;
	for (i = n, k = 1; i >= n - m + 1; i--, k++)
	{
		molecule *= i;
		molecule /= k;
	}
	return molecule;
}

int f1()
{
	unsigned long long n, a, b, i, j, sum;
	n = input();
	sum = 0;
	for (i = 1; i <= 50; i++)
	{
		sum = 0;
		long long k = i / 2;
		if (i % 2 == 0) j = i / 2;
		else j = i / 2 + 1;
		for (; k >= 0; j++, k--)
			sum += C(k, j);
	}
	for (i = 0; i < n; i++)
	{
		a = input();
		b = input();
		printf("%s", sum);
	}
	return 0;
}
int f2()
{
	int i = f1(), x;
	for (i = 0; i < 100; i++)
	{
		x = x * i;
	}
	return x;
}
int main()
{
	int x, nowsum, sum = 0;
	scanf("%d", &x);
	if (x == 1)
	{
		sum += 1;
		nowsum = 1;
	}
	else if (x == 2)
	{
		sum += 2;
		nowsum = 2;
	}
	while (x != 0)
	{
		scanf("%d", &x);
		if (x == 1)
		{
			sum += 1;
			nowsum = 1;
		}
		else if (x == 2)
		{
			if (nowsum == 1)
			{
				sum *= 2;
				nowsum = 2;
			}
			else
			{
				nowsum += 2;
				sum += nowsum;
			}
		}
	}
	printf("%d\n", sum);
	char *s = (char*)malloc(100 * sizeof(char));
	scanf("%s", s);
	char strstr[50];
	strcpy(strstr, s);
	printf("%d", strstr);
	return 0;
}
