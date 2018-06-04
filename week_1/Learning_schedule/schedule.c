#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct course{
  char* id;
  char* name;
  int day_of_week;
  bool morning;
  int period_s;
  int period_e;
  array[16] week;
  char* room;
} course;

void fixString(char* str){
  int i = strlen(str);
  while(str[i]!=';'){
    i--;
  }
  str[i+1]='\0';
}


int main( int argc, char **argv){
  FILE *f;
  char line[100];
  char* word;

  if (argc!=1){
    return 0;
    printf("Error!!!");
  } else{
    f = fopen(*(argv) , "r");
    if (f == NULL) {
      perror("Error opening file");
      return(-1);
    }
    if (fgets(line, 100, f) != NULL) {
      do{
        word = strtok (line," ,.");
      } while(word != NULL);
    }
    fclose(f);
  }

}
