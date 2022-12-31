#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


//variable declarations
int i,a,b,c; //Counting Indicies

//Function declerations
bool is_prime(int n);

int main(int argc, char* argv[]) {
  int number = atoi(argv[1]);
  for(a = 2; a < number; a++){
      if(is_prime(a)){
          for(b = 2; b <= number-2; b++){
              if(is_prime(b)){
                  for(c = 2; c <= number-4; c++){
                      if(is_prime(c)){
                          if(a+b+c == number){
                              printf("%d = %d + %d + %d",number,a,b,c);
                              a = number;
                              b = number;
                              c = number;
                          }
                      }
                  }
              }
          }
          
      }
      
  }
  return 0;
  
}

bool is_prime(int n){
    if(n < 2){  //Technically I dont need this bc i only enter numbers greater than 2 into this function
        return false;   
    }

    for(i=2; i <= sqrt(n); i++){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}
