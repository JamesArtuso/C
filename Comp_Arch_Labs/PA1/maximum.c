#include <stdlib.h>
#include <stdio.h>
int length;
int returnLength;
int tempNum;

int main(int argc, char* argv[]) {

  FILE* fp = fopen(argv[1], "r");
  if (!fp) {
    perror("fopen failed");
    return EXIT_FAILURE;
  }
  
  fscanf(fp,"%d",&length);
  fscanf(fp,"%d",&returnLength);
  
  int i = 0;
  int numbers[length];
  
  while(!feof(fp)){  //I can def put this inside the sort algorithm instead
      fscanf(fp,"%d",&tempNum);
      numbers[i] = tempNum;
      i = i+1;
  }
  
  
  for(i = 1; i < length; i++){
      int temp = numbers[i];
      int j = i-1;
      
      while(numbers[j] < temp && j >= 0){
          numbers[j+1] = numbers[j];
          j = j -1;
      }
      numbers[j+1] = temp;
  }
  
  for(i = 0; i < returnLength; i++){
      printf("%d ", numbers[i]);
  }
  
  fclose(fp);
  return 0;
}