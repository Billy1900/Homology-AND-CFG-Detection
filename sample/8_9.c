#include<stdio.h>
#include<stdlib.h>
void f3()
{
	int x,j;
	unsigned int y;
	x = 5;
	y = 6;
	x = y - 10;
	for (int i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			x = y * i;
		}
	}
	long long k;

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
unsigned long long C(int m,int n)
{
	unsigned long long k,i,molecule=1;
	for(i=n,k=1;i>=n-m+1;i--,k++)
	{
		molecule*=i;
		molecule/=k;
	}
	return molecule;
}

int f1()
{
	unsigned long long n,a,b,i,j,sum;
	n=input();
	sum=0;
	for(i=1;i<=50;i++)
	{
		sum=0;
		long long k=i/2;
		if(i%2==0) j=i/2;
		else j=i/2+1;
		for(;k>=0;j++,k--)
			sum+=C(k,j);
	}
	for(i=0;i<n;i++)
	{
		a=input();
		b=input();
		printf("%s", sum);
	}
	return 0;
}
/*
1
23
3
*/
int main()
{
	int k, m, sum, j;
	scanf("%d", &k);
	char s[100],*str;
	sprintf(s, "1111111111111111111111111111111111111%d", k);
    str=(char*)malloc(100*sizeof(char));
    strcpy(str,s);
	int next;
	m = k + 1;
	f1();
	gets(s);
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
				printf("%n%d%n\n", m);
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
	return 0;
}
