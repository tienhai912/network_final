#ifndef BOARD_H_   /* Include guard */
#define BOARD_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int id;
  int location;// 0 = not out;
  int stepMoved;//after 48 step, get to stable
}horse;

typedef struct {
  int id;
  char name[20];
  int connfd;
  horse* playerHorse;
}player;

typedef struct{
  int id;
  int *tile;
  int currentTurn;
  player* boardPlayer;
}board;

horse* newHorse(int id, int playerID);

player* newPlayer(int id, int connfd, char name[20]);

board* newBoard(int id, int connfd[4], char name[4][20]);

int toss(void);

horse* findHorseOnBoard(board *curBoard, int horseID);

int moveHorse(board *curBoard, int horseID, int move);

int checkKickHorse(board *curBoard, horse* tempHorse, int newPos);

int checkJumpOver(board *curBoard, horse* tempHorse, int newPos);

void printBoard(board *curBoard);
#endif
