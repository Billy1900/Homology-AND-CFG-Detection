#include<stdio.h> //include
#include<string.h>
#include<stdlib.h>
//define
#define MAX 10
#define x1 (n*n)
typedef int I;
#define x2(a,b) ((a-b)*(a+b))
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
int f4()
{
	int j = f3();
	f1();
	f2();
	return j;
}
void g1()
{
	short i;
	int l = 6;
	unsigned int r = 7;
	l=r;
	long long m=2;
	l = m;
	i = m;
	char s[90],c[100];
	strncpy(s,c,i);
	
	return;
}
void cover(int x, int y)
{
	int i=1, j=1, k=1, a = x, b = y;
	printf("%d%d", i);
	for (j = 0, y = b; j < 7; j++, y++)
	{
		i = j * k;
		for (k = 0; k < 5; k++)
		{
			k = k + 1;
		}
	}
	char s[90],c[100];
	strncat(s,c,k);
}
int main()
{
	int i = 100, j = 5;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			i = i / j;
		}
	}
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			i = i / j;
		}
	}
	scanf("%d%d", &i, &j);
	char c[100], d[100], e[105];
	char *str = (char*)malloc(105 * sizeof(char));
	char *k;
	f1();
	f2();
	f4();
	f3();
	k = (char*)malloc(i * sizeof(char));
	scanf("%s", c);
	strncat(str, d);
	strcpy(d, e);

	g1();
	cover(1,2);
	printf("%d%d%s%s\\1234", j, i);
	return 0;
}
