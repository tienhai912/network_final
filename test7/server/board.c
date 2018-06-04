#include "board.h"

horse* newHorse(int id, int playerID){
  horse* newHorse = (horse*) malloc(sizeof(horse));
  newHorse->id = id + playerID * 4;
  newHorse->location = 0;
  newHorse->stepMoved = 0;
  return newHorse;
}

player* newPlayer(int id, int connfd, char name[20]){
  player* newPlayer = (player*) malloc(sizeof(player));
  newPlayer->id = id;
  newPlayer->connfd = connfd;
  strcpy(newPlayer->name, name);
  newPlayer->playerHorse = (horse*)malloc(4 * sizeof(horse));
  for(int i=0;i<4;i++){
    *(newPlayer->playerHorse+i) = *newHorse(i, id);
  }
  return newPlayer;
}

board* newBoard(int id, int connfd[4], char name[4][20]){
  int i,j;
  board* newBoard = (board*) malloc(sizeof(board*));
  newBoard->id = id;
  newBoard->currentTurn = 0;
  newBoard->tile = (int*)malloc(73 * sizeof(int));
  for(j=0;j<73;j++){
    *(newBoard->tile + j) = -1;
  }
  newBoard->boardPlayer = (player*)malloc(8 * sizeof(player));///// wtf tai sao no bat 8* size @@
  for(i=0;i<4;i++){
    *(newBoard->boardPlayer + i) = *newPlayer(i, connfd[i], name[i]);
  }
  return newBoard;
}

int toss(void){
  return rand() % 6 + 1;
}

horse* findHorseOnBoard(board *curBoard, int horseID){
  if (horseID == -1){
    printf("Empty title\n");
    return NULL;
  }
  if (horseID < -1 || horseID > 15){
    printf("Invalid horseID %d\n", horseID);
    return NULL;
  }
  horse* tempHorse = ((curBoard->boardPlayer + horseID/4)->playerHorse + horseID%4);
  return tempHorse;
}

int moveHorse(board *curBoard, int horseID, int move){
  horse* tempHorse = findHorseOnBoard(curBoard, horseID);
  int playerNum = horseID/4;
  printf("Move %d: %d\n", horseID, move);
  if (tempHorse == NULL){
    printf("No horse number %d found\n", horseID);
    return 0;
  }

  if (tempHorse->stepMoved < 0 || tempHorse->stepMoved > 54){
    printf("Error, the horse moved %d steps\n", tempHorse->stepMoved);
    return 0;
  }

  if (tempHorse->stepMoved == 54){
    printf("Error, the horse has reached the end of the stable\n");
    return 0;
  }

  if (move < 1 || move > 6){
    printf("Error, Move %d is invalid\n", move);
    return 0;
  }
  /////////////////////////////////////////////////////////////////////////
  if (tempHorse->stepMoved == 0){
    if (move != 6){
      printf("The horse is not out yet\n");
      return 0;
    } else {
      if (checkKickHorse(curBoard, tempHorse, 1 + playerNum * 12) == -1){
        printf("Your another horse is standing at the start\n");
        return 0;
      }
      tempHorse->location = 1 + playerNum*12;
      tempHorse->stepMoved = 1;
      return 1;
    }
  } else if (tempHorse->stepMoved < 48){
    if (tempHorse->stepMoved + move <=48){
      if (checkKickHorse(curBoard, tempHorse, tempHorse->location + move) == -1){
        printf("Cannot kick your own horse\n");
        return 0;
      }
      tempHorse->location += move;
      tempHorse->stepMoved += move;
      return 1;
    } else {
      printf("The horse cannot move %d more steps or pass the stable\n", move);
      return 0;
    }
  } else if (tempHorse->stepMoved == 48){
    if (checkKickHorse(curBoard, tempHorse, tempHorse->location + move) == -1){
      printf("Your another horse is standing at that place\n");
      return 0;
    }
    tempHorse->location += move + playerNum * 6;
    tempHorse->stepMoved += move;
    return 1;
  } else {
    int stablePos = tempHorse->stepMoved-48;

    if (move - stablePos == 1){
      if (checkKickHorse(curBoard, tempHorse, tempHorse->location + 1) == -1){
        printf("Your another horse is standing at that place\n");
        return 0;
      }
      tempHorse->location += 1;
      tempHorse->stepMoved += 1;
      return 1;
    } else {
      printf("Cannot jump to %d in stable, can only move 1 tile at a time\n", move);
      return 0;
    }
  }
  return 1;
}

int checkKickHorse(board *curBoard, horse* tempHorse, int newPos){
  if (checkJumpOver(curBoard, tempHorse, newPos) == -1){
    return -1;
  }
  horse* tileHorse = findHorseOnBoard(curBoard, *(curBoard->tile + newPos));
  if (tileHorse == NULL){
    *(curBoard->tile + newPos) = tempHorse->id;
    *(curBoard->tile + tempHorse->location) = -1;
    return 0;
  } else if ((tileHorse->id /4) == (tempHorse->id /4)){
    return -1;
  } else {
    *(curBoard->tile + newPos) = tempHorse->id;
    *(curBoard->tile + tempHorse->location) = -1;;
    tileHorse->location = 0;
    tileHorse->stepMoved = 0;
    return 1;
  }
}

int checkJumpOver(board *curBoard, horse* tempHorse, int newPos){
  int i;
  for (i=(tempHorse->location + 1);i<newPos;i++){
    if (*(curBoard->tile +i) !=-1){
      printf("Cannot jump over tile %d\n", i);
      return -1;
    }
  }
  return 1;
}

void printBoard(board *curBoard){
  printf("Board:\n");
  int i,j;
  for(i=0;i<4;i++){
    for(j=0;j<4;j++){
      horse* tempHorse = findHorseOnBoard(curBoard, i*4+j);
      printf("%d.%d: %d\n", i, j, tempHorse->location);
    }
  }
  printf("On board:\n");
  for (i=0;i<73;i++){
    if (*(curBoard->tile + i) != -1){
      printf("Tile %d: %d\n", i, *(curBoard->tile + i));
    }
  }
}
