#include "board.h"

board* newBoard(horseList* hl){
  board* newBoard = (board*) malloc(sizeof(board*));
  newBoard->hl = hl;
  return newBoard;
}

int toss(void){
  srand(time(NULL));
  return rand() % 6 + 1;
}

horse* findHorseOnBoard(board *curBoard, int horseID){
  return findHorseInList(curBoard->hl, horseID);
}

int moveHorse(board *curBoard, int horseID, int move){
  horse* tempHorse = findHorseOnBoard(curBoard, horseID);
  if (tempHorse == NULL){
    printf("No horse number %d found\n", horseID);
    return 0;
  }

  tempHorse->location += move;
  tempHorse->stepMoved += move;


  return 1;
}