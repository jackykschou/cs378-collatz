// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream

#include "Collatz.h"

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
    int i;
    int j;
    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}

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
