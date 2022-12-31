#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>



//Code for Discrete HW 2 question 2. This program should 
//Calculate the expected cost of an attack with given values of
//q and p. In order to use, you can put "chips" into your sites.
//IE, if i give site0 2 chips and site1 3 chips, the probabliity 
//of site0 being defended is 2/5 and the probabliity of site1 being
//defended is 3/5. This program is expandable in that to add more sites,
//Simply change the value of SITES and add more entries to the 3
//arrays at the begining of the main method. The rest of the program
//should scale appropriately
int weightedRandom(int size, int sum_of_weights, int* weights){

    int rnd = rand() % sum_of_weights;


    for(int i =0; i < size ; i++){
        if(rnd < weights[i])
            return i;
        rnd -= weights[i];
    }
    return -1;
}




int main(int argc, char* argv[])
{
    const int SITES = 4;

    int* qweights = malloc(SITES * sizeof( int ));
    *(qweights+0) = 3;
    *(qweights+1) = 2;
    *(qweights+2) = 2;
    *(qweights+3) = 2;




    int* pweights = malloc(SITES * sizeof( int ));
    *(pweights+0) = 0;
    *(pweights+1) = 0;
    *(pweights+2) = 0;
    *(pweights+3) = 10;




    float* costs = malloc(4 * sizeof( float ));
    *(costs+0) = 100;
    *(costs+1) = 200;
    *(costs+2) = 200;
    *(costs+3) = 400;

    double predicted = 0.0;
    int sum_of_q = 0;
    int sum_of_p = 0;
    int sum_of_c = 0;
    for(int i = 0; i < SITES; i++){
        sum_of_q += qweights[i];
        sum_of_p += pweights[i];
        sum_of_c += costs[i];
    }

    for(int i = 0; i < SITES; i++){
        double cost = (double)costs[i];
        double q = ((double)qweights[i])/sum_of_q;
        double p = 1- ((double)pweights[i])/sum_of_p;
        predicted += cost*q*p;
    }
    printf("Predicted: %f \n", predicted);


    int total = 100000000;
    long double amount = 0;

    double* numqs = malloc(SITES*sizeof( double ));
    double* numps = malloc(SITES*sizeof( double ));

    for(int i = 0; i < total; i++){
        int q = weightedRandom(SITES, sum_of_q, qweights);
        int p = weightedRandom(SITES, sum_of_p, pweights);
        numqs[q] += 1;
        numps[p] += 1;

        if((p == -1) | (q == -1)){
            printf("-1");
        }

        if(q != p){
            amount += costs[q];
        }
    }
    printf("Actual: %.20Lf \n",amount/total);

    printf("\n\nQ percentage:\n");
    for(int i =0; i < SITES; i++){
        printf("q = %d, %lf \n", i, numqs[i]/total);
    }

    printf("\nP percentage:\n");
    for(int i =0; i < SITES; i++){
        printf("p = %d, %lf \n", i, numps[i]/total);
    }



    printf("\n\n\n");
    for(int i = 0; i < SITES; i++){
        double value = 1.0;
        for(int j = 0; j < SITES; j++){
                value += ((double) costs[i])/((double)costs[j]);
        }
        value = 1.0/value;
        printf("q%d = %lf\n", i, value);
    }

    free(qweights);
    free(pweights);
    free(costs);
    free(numps);
    free(numqs);
}

