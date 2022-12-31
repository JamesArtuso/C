#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the binary number representation of float point number
    /*char buff;
    unsigned int binary = 0;
    for (int i=EXP_SZ+FRAC_SZ; 0<=i; i--) { // read MSB first as that is what comes first in the file
        fscanf(fp, "%c", &buff);
        buff = buff-48;
        binary += buff*(1<<i);
    }
    printf("Bineary: %d: \n", binary);
    float num = *(float *)&binary; // you are not allowed to do this.
    printf("NNumber: %f \n", num);*/
        /* ... */
    char buff;
    unsigned int binary = 0;
    bool sign = false;
    fscanf(fp, "%c", &buff);
    if((buff-48)==1){ sign = true; }

    // E
    for (int i=(EXP_SZ-1); 0<=i; i--) { // read MSB first as that is what comes first in the file
        fscanf(fp, "%c", &buff);
        buff = buff-48;
        binary += buff*(1<<i);
    }
    int e = binary;
    e -= 127;

    bool normalized = true;
    if(e == -127){
        normalized =false;
        e = -126;
    }

    float m = 0;
    // M
    for (int i=1; i <= FRAC_SZ; i++) { // read MSB first as that is what comes first in the file
        fscanf(fp, "%c", &buff);
        buff = buff-48;
        m += buff*(1.0/(1<<i));
    }
    if(normalized){m += 1;}

    // https://www.tutorialspoint.com/c_standard_library/c_function_ldexp.htm
    double number = ldexp ( m, e );
    number = sign ? -number : number;
    printf("%e\n", number);

    return EXIT_SUCCESS;

}
