#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include <float.h>

#define EXP_SZ 11
#define FRAC_SZ 52

int main(int argc, char *argv[]) {


    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }


    double value;
    fscanf(fp, "%lf", &value);


    bool sign = value<0.0;
    printf("%d_",sign);


    double fraction = sign ? -value : value;


    signed short trial_exp=(1<<(EXP_SZ-1))-1;
    for(int i = trial_exp; i >= -1023; i--){
        trial_exp = i;
        if(fraction/(pow(2,i)) >= 1.0){
            break;
        }
    }
    

    unsigned short bias = (1<<(EXP_SZ-1))-1;
    signed short exp = trial_exp + bias;


    bool normal = true;
    if(fraction != 0 && trial_exp == -1023){
        normal = false;
        fraction = fraction*(pow(2,1022));
    }
    else{
        fraction = fraction/(pow(2,trial_exp));
    }


    for ( int exp_index=EXP_SZ-1; 0<=exp_index; exp_index-- ) {
        bool exp_bit = 1&exp>>exp_index;
        printf("%d",exp_bit);
    }
    printf("_");

    if(normal){fraction = fraction - 1;}


    bool frac_array[FRAC_SZ+1];
    for ( int frac_index=FRAC_SZ; 0<=frac_index; frac_index-- ) {
        fraction = fraction*2;
        if(fraction >= 1.0){
            frac_array[frac_index] = true;
            fraction -= 1.0;
        }
        else{
            frac_array[frac_index] = false;
        }
    }


    for ( int frac_index=FRAC_SZ; 1<=frac_index; frac_index-- ) {
        bool frac_bit = frac_array[frac_index];
        printf("%d", frac_bit);
    }

}
