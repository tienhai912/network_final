#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
  int *a;
}num;

typedef struct {
  num* temp;
}num2;

int main(void){
  int i,j;
  num2* temp2 = (num2*)malloc(sizeof(num2));

  temp2->temp = (num*)malloc(2*sizeof(num));

  for (j=0;j<2;j++){
    (temp2->temp+j)->a = (int*) malloc(5*sizeof(int));

    for (i=0; i<5;i++){
      *((temp2->temp+j)->a + i) = i;
    }

    for (i=0; i<5;i++){
      printf("%d.%d: %d\n", j, i, *((temp2->temp+j)->a +i));
    }
  }
}
