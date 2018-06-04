#ifndef BOARD_H_   /* Include guard */
#define BOARD_H_

#include "horsedll.h"
#include <time.h>

typedef struct{
  int tile[72];
  int numPlayer;
  int currentTurn;
  horseList* hl;
}board;

board* newBoard(horseList* hl);

int toss(void);

horse* findHorseOnBoard(board *curBoard, int horseID);

int moveHorse(board *curBoard, int horseID, int move);

#endif
