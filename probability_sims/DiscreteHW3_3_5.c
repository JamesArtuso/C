#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

long double factorial(long double a){
    if(a <= 1) { return 1; }
    else{
        return a*factorial(a-1);
    }
}

long double combination(long double n, long double k){
    return(factorial(n)/(factorial(k)*factorial(n-k)));
}

int main(int argc, char* argv[])
{

    long double prob = 2.0;

    int N = 100;
    int k = 49;

    while(prob >= 1.0){
        k+=1;
        prob = 0.0;
        for(int i = 0; i < N; i++){
            long double internalSum = 0.0;
            for(int j = k; j < N; j++){
                internalSum += combination(N-1, j) * pow(0.5, N-1);
            }
            prob += internalSum;
        }
        printf("N = %d, k = %d, Probability = %.20Lf \n",N, k, prob);
    }
}


