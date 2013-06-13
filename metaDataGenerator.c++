/*program that generates a series of maximum cycle length of a certain range of integers, from 1 to 1000000*/

#include <iostream>
#include <string>
#include <fstream>
#include <stack>

using namespace std;

int cycle_table[1000001] = {0, 1};

void generates(int);
void get_max_length(int, int, ofstream&);
int cycle_length(unsigned int);

void generates(int range) //note that 1000000 % range must be 0
{

	ofstream file;
	file.open("meta.txt");

	for(int i = 1; i <= 1000000; i += range)
	{
		get_max_length(i, i + range, file);
	}

	file << endl;

	file.close();
}

void get_max_length(int start, int end, ofstream& file)
{
    int v = 1;
    int len; //holding the result for each invocation of cycle_length

    for(; start < end; start++)
    {
    	if((len = cycle_length(start)) > v)
    	{
    		v = len;
    	}
    }

    file << v << ", ";
}

int cycle_length(unsigned int x)
{
	stack<int> numbers; //stores any numbers that are on the path of finding the cycle length
	numbers.push(x);

	int len;
	bool done = false;

	//cout << "the number is " << x << endl;
	while(!done)
	{
		if(x <= 1000000 && x > 0 && cycle_table[x])
		{
			done = true;
			len = cycle_table[x];
			//cout << len << endl;
		}
		else
		{
			x = (x % 2) ? (x + (x << 1) + 1) : (x >> 1);

			numbers.push(x);
		}
	}

	//fill the cache
    while(numbers.size() != 1)
    {
    	if(numbers.top() <= 1000000 && numbers.top() > 0)
    	{
    		cycle_table[numbers.top()] = len;
    	}
    	len++;
    	numbers.pop();
    }

    cycle_table[numbers.top()] = len;
    return len;
}

int main()
{
	generates(250);
}
