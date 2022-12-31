#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23

int main(int argc, char *argv[]) {
    

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }


    char buff;
    unsigned int binary = 0;
    bool multiplierSign = false;


    fscanf(fp, "%c", &buff);
    if((buff-48)==1){ multiplierSign = true; }


    for (int i=(EXP_SZ-1); 0<=i; i--) {
        fscanf(fp, "%c", &buff);
        buff = buff-48;
        binary += buff*(1<<i);
    }
    int multiplierE = binary;
    multiplierE -= 127;


    float multiplierM = 0;
    // M
    for (int i=1; i <= FRAC_SZ; i++) {
        fscanf(fp, "%c", &buff);
        buff = buff-48;
        multiplierM += buff*(1.0/(1<<i));
    }
    multiplierM += 1;



    fscanf(fp, "%c", &buff);



    bool multiplicandSign = false;
    fscanf(fp, "%c", &buff);
    if((buff-48)==1){ multiplicandSign = true; }


    binary = 0;
    for (int i=(EXP_SZ-1); 0<=i; i--) { // read MSB first as that is what comes first in the file
        fscanf(fp, "%c", &buff);
        buff = buff-48;
        binary += buff*(1<<i);
    }
    int multiplicandE = binary;
    multiplicandE -= 127;


    float multiplicandM = 0;
    // M
    for (int i=1; i <= FRAC_SZ; i++) { // read MSB first as that is what comes first in the file
        fscanf(fp, "%c", &buff);
        buff = buff-48;
        multiplicandM += buff*(1.0/(1<<i));
    }
    multiplicandM += 1;



    bool sign = multiplierSign^multiplicandSign;
    printf("%d_",sign);


    int exp = multiplierE+multiplicandE+127;


    float mantissa = multiplierM*multiplicandM;
    while(mantissa > 2){
        mantissa = mantissa/2;
        exp += 1;
    }
    mantissa = mantissa-1;


    bool frac_array[FRAC_SZ+1];
    for ( int frac_index=FRAC_SZ; 0<=frac_index; frac_index-- ) {
        mantissa = mantissa*2;
        if(mantissa >= 1.0){
            frac_array[frac_index] = true;
            mantissa -= 1.0;
        }
        else{
            frac_array[frac_index] = false;
        }
    }



    for ( int bit_index=EXP_SZ-1; 0<=bit_index; bit_index-- ) {
        bool trial_bit = 1&exp>>bit_index;
        printf("%d",trial_bit);
    }
    printf("_");


    for ( int frac_index=FRAC_SZ; 1<=frac_index; frac_index-- ) {
        bool frac_bit = frac_array[frac_index];
        printf("%d", frac_bit);
    }

    return(EXIT_SUCCESS);

}
