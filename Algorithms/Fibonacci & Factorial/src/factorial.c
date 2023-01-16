#include "factorial.h"

//4! = 4 * 3 * 2 * 1 * 1 => 4! = 4 * 3!
//1! = 1
//0! = 1

//Compl Time: O(N)
unsigned int factorial(unsigned int n) 
{
    if (n == 0)
    return 1;  //1

    if (n == 1)
    return 1;  //1

    return n * factorial(n - 1);
}

//Compl. Time: 1 + (N*1) + 1 => 2 + N => O(N)
unsigned int factorial_ite(unsigned int n)
{
    unsigned int result = 1;              //1

    for(unsigned int i = 1; i <= n; ++i)  //N
        result *= i;                         //1
        
    return result;                        //1
}