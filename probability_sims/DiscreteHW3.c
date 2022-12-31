#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>

int main(int argc, char* argv[])
{
    srand ( time(NULL) );
    const int N = 3;
    long double total = 1000000.0;
    long double numPerfect = 0.0;

    for(unsigned int i = 0; i < total; i++){

        bool** E = malloc(N * sizeof( bool* ));
        for(unsigned int j = 0; j < N; j++){
            E[j] = malloc(N * sizeof( bool ));
        }
        for(unsigned int j = 0; j<N; j++){
            for(unsigned int k = 0; k<N; k++){
                E[j][k] = false;
            }
        }


        for(unsigned int j = 0; j < N; j++){
            int a = rand() % N;
            //printf("a: %d", a);
            int b = rand() % N;
            //printf(" b: %d\n", b);
            //printf("%d %d\n", a, b);

            while(E[a][b]){
                a = rand() % N;
                b = rand() % N;
            }
            E[a][b] = true;
        }

        bool perfect = true;

        for(unsigned int j = 0; j < N; j++){

            int numEdgesr = 0;
            int numEdgesc = 0;

            for(unsigned int k = 0; k < N; k++){
                //printf("%d ", E[j][k]);
                if(E[j][k]){
                    numEdgesr += 1;
                }
                if(E[k][j]){
                    numEdgesc += 1;
                }

            }
            if((numEdgesr != 1) || (numEdgesc != 1)){
                perfect = false;
                //break;
            }
            //printf("\n");
        }
        if(perfect){
            numPerfect += 1;
        }
        for(int j = 0; j < N; j++){
            free(E[j]);
        }
        free(E);
    
    }


    long double value = numPerfect/total;

    printf("%.20Lf", value);
}