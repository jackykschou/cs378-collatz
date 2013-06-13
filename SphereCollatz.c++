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
#include <algorithm> //max_element

using namespace std;

#define INTERVAL 2500 //number of integers that bounds an interval of the meta cache 

int lazy_cache[1000001] = {0, 1}; //stores the calculated cycle length of any possible number inputed (lazy cache)

int meta_cache[] = {0, 209, 238, 262, 260, 268, 276, 271, 279, 269, 282, 308, 272, 285, 311, 324, 306, 288, 270, 314, 296, 309, 340, 322, 304, 335, 330, 
268, 312, 325, 325, 351, 338, 320, 320, 333, 333, 333, 315, 328, 328, 341, 310, 354, 310, 323, 305, 349, 336, 336, 331, 331, 344, 331, 331, 344, 313, 344, 
375, 357, 326, 370, 352, 383, 352, 370, 339, 352, 334, 334, 347, 334, 347, 365, 334, 347, 360, 329, 347, 360, 329, 342, 342, 373, 311, 355, 373, 386, 355, 
355, 324, 368, 355, 443, 381, 350, 350, 368, 337, 350, 350, 332, 363, 345, 345, 332, 407, 345, 345, 416, 358, 345, 389, 358, 358, 376, 398, 340, 358, 358, 
371, 371, 340, 309, 371, 384, 353, 353, 353, 371, 384, 340, 353, 353, 335, 366, 366, 335, 353, 441, 366, 379, 348, 379, 379, 419, 317, 361, 361, 392, 348, 
423, 361, 379, 330, 348, 436, 361, 405, 330, 374, 387, 343, 414, 312, 449, 374, 387, 343, 356, 418, 356, 374, 343, 396, 387, 400, 325, 356, 338, 369, 387, 
369, 356, 338, 444, 338, 369, 413, 307, 382, 382, 351, 422, 320, 391, 382, 320, 426, 320, 395, 426, 364, 382, 377, 470, 364, 395, 439, 364, 364, 408, 377, 
346, 377, 377, 346, 417, 359, 452, 377, 377, 421, 390, 315, 359, 421, 359, 359, 377, 372, 399, 359, 328, 434, 359, 328, 403, 328, 372, 372, 403, 372, 341, 
412, 354, 310, 447, 372, 372, 385, 374, 341, 385, 354, 416, 354, 425, 354, 323, 394, 354, 385, 429, 398, 323, 367, 398, 336, 367, 367, 385, 380, 336, 380, 
398, 390, 442, 367, 336, 367, 411, 380, 380, 349, 380, 411, 380, 349, 420, 380, 349, 362, 389, 349, 424, 424, 393, 318, 349, 393, 362, 424, 362, 362, 380, 
375, 331, 468, 362, 393, 437, 437, 362, 331, 375, 406, 375, 437, 468, 375, 406, 331, 406, 344, 415, 375, 357, 450, 450, 375, 375, 419, 419, 388, 344, 525, 
357, 388, 419, 357, 357, 428, 388, 370, 357, 344, 397, 388, 432, 388, 432, 357, 326, 370, 401, 401, 339, 370, 370, 370, 401, 383, 417, 370, 476, 401, 393, 
432, 339, 445, 476, 383, 370, 414, 414, 445, 383, 383, 383, 383, 414, 414, 352, 352, 423, 414, 365, 352, 458, 392, 391, 383, 427, 383, 427, 352, 321, 365, 365, 396
}; //meta cache storing pre-calculated maximum cycle length of every interval (the value of INTERVAL)

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

int cycle_length(unsigned int x)
{

    stack<int> numbers; //stores any numbers that are on the path of finding the cycle length
    numbers.push(x);
    int len;
    bool done = false;

    while(!done)
    {
        if(x <= 1000000 && x > 0 && lazy_cache[x])
        {
            done = true;
            len = lazy_cache[x];
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
            lazy_cache[numbers.top()] = len;
        }
        numbers.pop();
        len++;
    }

    lazy_cache[numbers.top()] = len;
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
    unsigned int x, y;

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

    while(x % INTERVAL && x <= y)
    {
        if((len = cycle_length(x++)) > v)
        {
            v = len;
        } 
    }

    int lower_bound = x / INTERVAL;

    while(x < y)
    {
        x += INTERVAL;
    }

    int upper_bound = x / INTERVAL;
    
    if( upper_bound != lower_bound && ((len = *max_element(meta_cache + lower_bound , meta_cache + upper_bound)) > v))
    {
        v = len;
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


// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    collatz_solve(cin, cout);
    return 0;}

