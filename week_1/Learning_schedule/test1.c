#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
  char s1 = "1,523,526,22,25-31,33-40,TC-502";
  char *pch;

  pch = strtok (line,",");

  while (pch!=NULL){
    pch = strtok (NULL, ",");
  }
}