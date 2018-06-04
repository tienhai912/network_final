#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct course_{
  char* id;
  char* name;
  int day_of_week;
  bool morning;
  int period_s;
  int period_e;
  array[16] week;
  char* room;
}course;

void fixString(char* str){
  int i = strlen(str);
  while(str[i]!=';'){
    i--;
  }
  str[i+1]='\0';
}

char** splitString(char* s, int *n){
  char** info;
  info = malloc(sizeof(char*)*NUM_WORD);

}


void getInfoFromFile(FILE *f, course* course, int numcourse){
  int LINE_SIZE = 100;
  int WORD_SIZE = 100;
  int NUM_WORD = 100;
  char** info;
  char line[LINE_SIZE];
  char* pch;
  int n = 0;
  int m = 0;
  int i;
  
  while (fgets(line, LINE_SIZE, f) != NULL) {
    printf("\n-----------------\nLine: %d\n", m);
    fixString(line);
    printf("\"%s\"\n", line);
    info = malloc(sizeof(char*)*NUM_WORD);
    n=0;
    
    for (*pch = strtok(s," .;"); pch != NULL; pch = strtok(NULL, " .;")){
      *(info+n) = (char*) malloc(sizeof(char)*WORD_SIZE);
      strcpy(*(info+n), pch);
      n++;
    }
    for(i=0;i<n;i++){
      printf("\"%s\"\n", *(info+i));
    }
    course[m].id = (char*) malloc(sizeof(char)*100);
    course[m].name = (char*) malloc(sizeof(char)*100);
    strcpy(course[m].id, *info);

    strcpy(course[m].name, *(info+1));
    for (i=2;i<n-1;i++){
      strcat(course[m].name, " ");
      strcat(course[m].name, *(info+i));
    }
    *(info+n-1)

    
    m++;
  }
}

int main (void){
  FILE *f;
  course *list;
  
  f = fopen("schedule.txt" , "r");
  if (f == NULL) {
    perror("Error opening file");
    return(-1);
  }
  course = (course*) malloc(sizeof(course)*10);
  getInfoFromFile(f, list, 10);
  
  fclose(f);
}