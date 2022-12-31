#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, char* argv[])
{
    long double summation = 0.0;


    for(long double i = 500; i <= (1577); i++){
        summation += 497004/(i*(i-1)*(i-2));
    }


printf("%.20Lf",summation);

}