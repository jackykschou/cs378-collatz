/*this program is used to randomly generate 1000 lines of input for Collatz*/

#include <iostream>
#include <string>
#include <cstdio> //for NULL
#include <cstdlib> //for rand
#include <fstream>
#include <ctime>

using namespace std;

void generate_lines(string, int);

int main()
{
	srand(time(NULL));

	generate_lines("testing.txt", 1200);
}

void generate_lines(string name, int lines)
{
	ofstream file;
	file.open(name.c_str());

	for(;lines > 0; lines--)
	{
		file << "" << (rand() % 1000000 + 1) << " " << (rand() % 1000000 + 1) << endl;  
	}

	file.close();
}

