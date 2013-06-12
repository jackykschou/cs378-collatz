// -------------------------------
// projects/collatz/RunCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// -------------------------------

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
#define NDEBUG
#endif

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // cin, cout, ios_base, endl, istream, ostream
#include <stack>

using namespace std;

int cycle_table[1000001] = {}; //stores the calculated cycle length of any possible number inputed (the first element is not used)

// ------------
// collatz_read
// ------------

bool collatz_read (std::istream& r, int& i, int& j) {
    r >> i;
    if (!r)
        return false;
    r >> j;
    assert(i > 0);
    assert(j > 0);
    return true;}

//----------
//cycle_length
//----------

int cycle_length(int x)
{
    stack<int> numbers; //stores any numbers that are on the path of finding the cycle length
    numbers.push(x);

    int len;
    bool done = false;

    while(!done)
    {
        if(x <= 1000000 && x > 0 && cycle_table[x])
        {
            done = true;
            len = cycle_table[x];
        }
        else
        {
            x = (x % 2) ? (x + (x << 1) + 1) : (x >> 1);
            if(x <= 1000000 && x > 0)
            {
                numbers.push(x);
            }
        }
    }

    //fill the cache
    while(numbers.size() != 1)
    {
        cycle_table[numbers.top()] = len++;
        numbers.pop();
    }
    cycle_table[numbers.top()] = len;
    return len;
}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    assert(i > 0);
    assert(j > 0);
    
    int v = 1;
    int len; //holding the result for each invocation of cycle_length
    int x, y;

    if(i > j)
    {
        x = j;
        y = i;
    }
    else
    {
       y = j;
       x = i;
    }

    for(; x <= y; x++)
    {
        if((len = cycle_length(x)) > v)
        {
            v = len;
        }
    }

    assert(v > 0);
    return v;}

// -------------
// collatz_print
// -------------

void collatz_print (std::ostream& w, int i, int j, int v) {
    assert(i > 0);
    assert(j > 0);
    assert(v > 0);
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (std::istream& r, std::ostream& w) {

    cycle_table[1] = 1;

    int i;
    int j;
    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}


// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    collatz_solve(cin, cout);
    return 0;}

