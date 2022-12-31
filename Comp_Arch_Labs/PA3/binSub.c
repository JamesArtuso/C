#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
//bool char_val = 0b1 & input>>digit; // shift and mask


void addition(bool* num1, bool* num2, bool* store){
    bool carry = false;
    for(int i = 0; i < 8; i++){
        bool val = num1[i]^num2[i];
        val = val^carry;

        carry = ((num1[i]&&num2[i])
              || (num1[i]&&carry)
              || (num2[i]&&carry));

        store[i] = val;
    }
}


int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }


    char buff;
    bool minuend[8];
    for (int i=7; 0<=i; i--) {
        fscanf(fp, "%c", &buff);
        minuend[i] = (buff-48);
    }


    bool subtrahend[8];
    fscanf(fp, "%c", &buff);
    for (int i=7; 0<=i; i--) {
        fscanf(fp, "%c", &buff);
       subtrahend[i] = 0b1^(buff-48);
    }
    bool one[8] = {1,0,0,0,0,0,0,0};
    addition(subtrahend, one, subtrahend);


    bool difference[8];
    addition(minuend, subtrahend, difference);


    for (int i=7; 0<=i; i--)
        printf("%d",difference[i]);


    return EXIT_SUCCESS;

}
