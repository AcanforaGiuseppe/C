#include <stdio.h>
#include "factorial.h"
#include "fibonacci.h"

int main() 
{
    unsigned int fact4 = factorial(4);
    printf("fact4: %u\n", fact4);

    printf("fib6: %u\n", fibonacci(6));

    printf("fib60: %u\n", fibonacci_optimized(60));

    printf("fibN: %u\n", fibonacci_optimized(111111111360));

    printf("fact_ite4: %u\n", factorial_ite(4));

    printf("fib_ite6: %u\n", fibonacci_ite(6));

    unsigned int MAX_UINT = -1;
    
    printf("fibN: %u\n", fibonacci_ite(MAX_UINT));

    return 0;
}