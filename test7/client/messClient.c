// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
#include "board.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
//**********mmap**********
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
//_________________________

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8 /*maximum number of client connections*/

int readMessC(char *mess, int connfd, struct sockaddr_in cliaddr){
  char* messType, playerName, token. tokenData;
  char name[4][20];
  int curPlayer;
  curPlayer = 0;

  char tokeLine[2] = ";";
  token = strtok(mess, tokeLine);

  printf("Message Type: %s\n", token);
  if (token != NULL){
    if (strcmp(token, "StartGame"){
      /// in dev
    } else if (strcmp(token, "StartTurn"){
      /// in dev
    } else if (strcmp(token, "TossResult"){
      tokenData = strtok(mess, tokeLine);
      int tossResult;
      tossResult = atoi(tokenData);

    } else if (strcmp(token, "LossTurn"){
      tokenData = strtok(mess, tokeLine);
      int tossResult;
      tossResult = atoi(tokenData);
      if (checkClientConnfd("LossTurn", connfd, atoi(tokenData)) ==1){
        // stop send mess
      }
      // in dev
    } else if (strcmp(token, "EndGame"){
      tokenData = strtok(mess, tokeLine);
      int tossResult;
      tossResult = atoi(tokenData);
      if (checkClientConnfd("EndGame", connfd, atoi(tokenData)) ==1){
        /// return to menu
      }
      // in dev
    } else if (strcmp(token, "Score"){
      int score[4];
      int i;
      for (i=0; i<4; i++){
        tokenData = strtok(mess, tokeLine);
        score[i] = atoi(tokenData);
      }
    } else if (strcmp(token, "UpdateHorse"){
      tokenData = strtok(mess, tokeLine);
      int tossResult;
      tossResult = atoi(tokenData);
      if (checkClientConnfd("EndGame", connfd, atoi(tokenData)) ==1){
        /// update horse
      }
      // in dev
    } else if (strcmp(token, "Confirm"){
      token = strtok(mess, tokeLine);
      if (strcmp(token, "FindGame"){
        int selfConnfd;
        tokenData = strtok(mess, tokeLine);
        selfConnfd = atoi(tokenData);
        // Success
      } else if (strcmp(token, "Move"){
        tokenData = strtok(mess, tokeLine);
        int status = atoi(tokenData);
        if (status != 1){
          printf("Error: Move is not confirmed\n");
        } else {
          printf("Move Confirm\n");
        }
        // in dev?
      } else {
        printf("Error confirm message from client\n");
      }
    } else {
      printf("Error message from client\n");
    }
  }
  return 1;
}

int checkClientConnfd(char *messType, int connfd, int tokenData){
  if (connfd == atoi(tokenData)){
    printf("Success read mess %s from c\n", messType);
    return 1;
  } else{
    printf("Fail read mess %s from c: %s\n", messType, tokenData);
    return 0;
  }
  return 0;
}

void messCFindGame(char *mess, char *name){
  sprintf(mess, "FindGame;%s;", name);
}

void messCConfirmStartGame(char *mess){
  sprintf(mess, "Confirm;StartGame;"]);
}

void messCConfirmStartTurn(char *mess){
  sprintf(mess, "Confirm;StartTurn;");
}

void messCToss(char *mess, int connfd){
  sprintf(mess, "Toss;%d;", connfd);
}

void messCConfirmTossResult(char *mess, int TossResult){
  sprintf(mess, "Confirm;TossResult;%d;", TossResult);
}

void messCMove(char *mess, int connfd, int horseID){
  sprintf(mess, "Move;%d;%d;", connfd, horseID);
}

void messCConfirmLossTurn(char *mess){
  sprintf(mess, "ConfirmLossTurn;");
}

void messCConfirmEndGame(char *mess){
  sprintf(mess, "Confirm;EndGame;");
}

void messCConfirmScore(char *mess){
  sprintf(mess, "Confirm;Score;");
}

void messCConfirmUpdateHorse(char *mess){
  sprintf(mess, "Confirm;UpdateHorse;");
}
