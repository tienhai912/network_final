#include "board.h"

int main(void){
  board* curBoard = (board*) malloc(sizeof(board*));
  horseList* hl = (horseList*) malloc(sizeof(horseList*));

  hl = newHorseList();
  curBoard = newBoard(hl);

  if (isEmpty(hl)){
    printf("Empty horseList\n");
  }

  horse* horse1 = newHorse(lastID(hl) + 1, 1, 0);
  insertLast(hl, horse1);
  horse1 = newHorse(lastID(hl) + 1, 1, 0);
  insertLast(hl, horse1);
  displayForward(hl);
  printf("list length: %d\n", length(hl));
  moveHorse(curBoard, 1, 4);
  moveHorse(curBoard, 2, 5);
  displayForward(hl);
}