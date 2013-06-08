/*
CS378 Ka Seng Chou
Projet#1 SphereCollatz.c++
this file is used to submit to Shpere for testing
*/

#include <iostream> //for using cout
#include <cstdio> //for using scanf, printf

//------------------
//function prototypes
//------------------
void process_collatz();
void process_pair(int, int);
int cycle_length(int);

//----
//main
//----

int main()
{
	process_collatz();
	return 0;
}

//----------
//process_collatz
//----------

void process_collatz()
{
	int x, y;
	while(scanf("%d %d", &x, &y) != EOF)
	{
		process_pair(x, y);
	}
}

//----------
//process_pair
//----------

void process_pair(int x, int y)
{
	int max = 1;
	int len; //holding the result for each invocation of cycle_length
	int i, j;

	if(x > y)
	{
		i = y;
		j = x;
	}
	else
	{
		i = x;
		j = y;
	}

	for(; i <= j; i++)
	{
		if((len = cycle_length(i)) > max)
		{
			max = len;
		}
	}

	printf("%d %d %d\n",x, y, max);
}

//----------
//cycle_length
//----------

int cycle_length(int x)
{
	int result = 1;

	while(x != 1)
	{
		result++;
		x = (x % 2) ? (x * 3 + 1) : (x / 2);
	}

	return result;
}