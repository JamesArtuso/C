#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    signed short int input;
    fscanf(fp, "%hd", &input);


    for(int hexNum=3; hexNum >= 0; hexNum--){
        int val = 0;
        for(int digit = 3; digit >= 0; digit--){
            val += (0b1 & input>>(digit+4*hexNum))*(1<<(digit));
        }
        if(val > 9) val+=7;
        printf("%c", 48+val);
    }
    fclose(fp); 
    return EXIT_SUCCESS;

}
