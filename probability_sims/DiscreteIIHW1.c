#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

double correct = 0.0;
int flips = 20;
int total = 100000000;


int main(int argc, char* argv[])
{
    for(unsigned int i = 0; i < total; i++){
        int coin = rand() % 2;
        int heads = 0;
        for(unsigned int j = 0; j < flips; j++){
            if(coin == 0){
                if(rand() % 2 != 0){
                    heads += 1;
                }
            }
            if(coin == 1){
                if(rand() % 4 != 0){
                    heads += 1;
                }
            }
        }
        if(heads >= (flips/2)+1){
            if(coin == 1){ correct += 1; }
        }
        else{
            if(coin == 0) { correct += 1; }
        }
    }

    double percentage = correct/((double)total);
    printf("%lf",percentage);
}