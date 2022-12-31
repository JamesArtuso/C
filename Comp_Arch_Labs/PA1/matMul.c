#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


int dotProduct(int* a, int* b, int size);


int main(int argc, char* argv[])
{
    //Matrix A stuff
    FILE* matrix_a_fp = fopen(argv[1], "r");
    if (!matrix_a_fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    char buff[256];

    fscanf(matrix_a_fp, "%s", buff);
    char length_l = atoi(buff);
    int** matrix_a = malloc( length_l * sizeof(int*) );

    fscanf(matrix_a_fp, "%s", buff);
    char length_m = atoi(buff);
    for ( unsigned char i=0; i<length_l; i++ ) {
        matrix_a[i] = malloc( length_m * sizeof(int) );
    }

    char j[256];

    for(int i = 0; i < length_l; i++){
        for(int k = 0; k < length_m; k++){
         fscanf(matrix_a_fp, "%s", j);
         *(*(matrix_a+i)+k) = atoi(j);   
        }
    }



    fclose(matrix_a_fp);


    //Matrix B stuff
    // B IS TRANSPOSED TO MAKE IT EASIER TO DOT PRODUCT
    FILE* matrix_b_fp = fopen(argv[2], "r");
    if (!matrix_b_fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }


    fscanf(matrix_b_fp, "%s", buff);
    char length_bl = atoi(buff);
    fscanf(matrix_b_fp, "%s", buff);
    char length_bm = atoi(buff);

    int** matrix_b = malloc( length_bm * sizeof(int*) );
    for ( unsigned char i=0; i<length_bm; i++ ) {
        matrix_b[i] = malloc( length_bl * sizeof(int) );
    }


    for(unsigned int i = 0; i < length_bl; i++){
        for(unsigned int k = 0; k < length_bm; k++){
         fscanf(matrix_b_fp, "%s", j);
         *(*(matrix_b+k)+i) = atoi(j);   
        }
    }


    fclose(matrix_b_fp);


    //Matrix C is actually redundant
    //Do not need to have a Matric C
    int** matrix_c = malloc( length_l * sizeof(int*) ); //Allocates the number of rows

    for ( unsigned char i=0; i<length_l; i++ ) { //Allocates the number of columns
        matrix_c[i] = malloc( length_bm * sizeof(int) );
    }

    for(unsigned int i = 0; i < length_l; i++){
        for(unsigned int k = 0; k < length_bm; k++){
            *(*(matrix_c+i)+k) = dotProduct((*(matrix_a+i)), (*(matrix_b+k)), length_m);
        }
        printf("\n");
    }



    for ( unsigned char i=0; i<length_l; i++ ) {
        free( matrix_a[i] );
    }
    free( matrix_a );

    for ( unsigned char i=0; i<length_bm; i++ ) {
        free( matrix_b[i] );
    }
    free( matrix_b );

    for ( unsigned char i=0; i<length_l; i++ ) {
        free( matrix_c[i] );
    }
    free( matrix_c );

    return 0;

}

int dotProduct(int* a, int* b, int size){
    int sum=0;
    for(unsigned int i = 0; i < size; i++){
        sum = sum + (*(a+i)) * (*(b+i));
    }
    printf("%d ",sum);
    return sum;
}
