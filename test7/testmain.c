#include "board.h"

int main(void){
  srand(time(NULL));
  int i, tResult;
  int playerConnfd[4];
  char playerName[4][20];
  for (i=0;i<4;i++){
    playerConnfd[i] = i;
    //strcpy(playerName[i], "Player ");
    sprintf(playerName[i], "Player %d", i);
  }
  board* curBoard = newBoard(1, playerConnfd, playerName);

  printBoard(curBoard);
  moveHorse(curBoard, 0, 1);
  moveHorse(curBoard, 0, 6);
  moveHorse(curBoard, 3, 6);
  moveHorse(curBoard, 1, 6);
  moveHorse(curBoard, 0, 3);
  moveHorse(curBoard, 1, 6);
  moveHorse(curBoard, 1, 3);
  moveHorse(curBoard, 1, 4);
  moveHorse(curBoard, 0, 44);
  moveHorse(curBoard, 1, 43);
  moveHorse(curBoard, 0, 4);
  moveHorse(curBoard, 1, 4);
  moveHorse(curBoard, 1, 5);
  moveHorse(curBoard, 1, 1);
  moveHorse(curBoard, 1, 3);
  tResult = toss();
  printBoard(curBoard);
}
