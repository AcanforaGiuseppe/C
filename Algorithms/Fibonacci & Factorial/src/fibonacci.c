#include "fibonacci.h"
#include <stdlib.h>

//N: 0  1  2  3  4  5  6
//F: 0  1  1  2  3  5  8
//Compl. Time: O(2^N)
//Compl. Space: O(1) oppure O(2^N)
unsigned int fibonacci(unsigned int n)
{
    if (n == 0)
    return 0; //1

    if (n == 1)
    return 1; //1

    return fibonacci(n - 1) + fibonacci(n - 2);
}

static unsigned int fibonacci_optimized_internal(unsigned int n, unsigned int* cache)
{   
    if (n == 0)
    return 0;

    if (n == 1) 
    return 1;

    if (cache[n] == 0) 
        cache[n] = fibonacci_optimized_internal(n - 1, cache) + fibonacci_optimized_internal(n - 2, cache);
    
    return cache[n];
}

//Compl Time: O(N)
//Compl Space: O(N) 
unsigned int fibonacci_optimized(unsigned int n) 
{
    unsigned int* cache = (unsigned int*)calloc((n+1), sizeof(unsigned int));
    unsigned int result = fibonacci_optimized_internal(n, cache);
    free(cache);

    return result;
}

//N: 0  1  2  3  4  5  6
//F: 0  1  1  2  3  5  8
//Compl. Time: 6 + 3*(N-1) => O(N)
//Compl. Space: 5 => O(1)
unsigned int fibonacci_ite(unsigned int n)
{
    if (n == 0)
    return 0;  //1

    if (n == 1)
    return 1;  //1

    unsigned int result;    //1
    unsigned int prev2 = 0; //1
    unsigned int prev1 = 1; //1

    for(unsigned int i = 2; i <= n; ++i)    //(N-1)
    {
        result = prev2 + prev1;             //1
        prev2 = prev1;                      //1
        prev1 = result;                     //1
    }
    
    return result;                          //1
}