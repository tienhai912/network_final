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

int readMessS(char *mess, int connfd, struct sockaddr_in cliaddr){
  char* messType, playerName, token. tokenData;
  char name[4][20];
  int curPlayer;
  curPlayer = 0;

  char tokeLine[2] = ";";
  token = strtok(mess, tokeLine);

  printf("Message Type: %s\n", token);
  if (token != NULL){
    if (strcmp(token, "FindGame"){
      tokenData = strtok(mess, tokeLine);
      strcpy(name[curPlayer], tokenData);
      curPlayer++;
    } else if (strcmp(token, "Toss"){
      tokenData = strtok(mess, tokeLine);
      if (checkClientConnfd("Toss", connfd, atoi(tokenData)) ==1){
        ///Toss
      }

    } else if (strcmp(token, "Move"){
      tokenData = strtok(mess, tokeLine);
      if (checkClientConnfd("Move", connfd, atoi(tokenData)) ==1){
        int horseID;
        tokenData = strtok(mess, tokeLine);
        horseID = atoi(tokenData);
        if (horseID == 0 && strcmp(tokenData, "0") != 0){
          printf("Wrong horseID in Move\n");
        }
      }

    } else if (strcmp(token, "Confirm"){
      token = strtok(mess, tokeLine);
      if (strcmp(token, "StartGame"){
        // Success
      } else if (strcmp(token, "StartTurn"){
        // Success
      } else if (strcmp(token, "TossResult"){
        tokenData = strtok(mess, tokeLine);
        // check tokenData and toss result

      } else if (strcmp(token, "LossTurn"){
        // Success

      } else if (strcmp(token, "EndGame"){
        // Success

      } else if (strcmp(token, "Score"){
        // Success

      } else if (strcmp(token, "UpdateHorse"){
        //Success
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

void messSConfirmFindGame(char *mess, int connfd){
  sprintf(mess, "Confirm;FindGame;%d;", connfd);
}

void messSStartGame(char *mess, int connfd[4], char name[4][20]){
  sprintf(mess, "StartGame;%d;%s;%d;%s;%d;%s;%d;%s;", connfd[0], name[0], connfd[1], name[1], connfd[2], name[2], connfd[3], name[3]);
}

void messSStartTurn(char *mess, int connfd){
  sprintf(mess, "StartTurn;%d;", connfd);
}

void messSTossResult(char *mess, int TossResult){
  sprintf(mess, "TossResult;%d;", TossResult);
}

void messSConfirmMove(char *mess){
  sprintf(mess, "Confirm;Move;%d;1;");
}

void messSLossTurn(char *mess, int connfd){
  sprintf(mess, "LossTurn;%d;", connfd);
}

void messSEndGame(char *mess, int connfd){
  sprintf(mess, "EndGame;%d;", connfd);
}

void messSScore(char *mess, int score[4]){
  sprintf(mess, "Score;%d;%d;%d;%d;", score[0], score[1], score[2], score[3]);
}

void messSUpdateHorse(char *mess, int connfd, int horseID, int newLocation, int newStepMoved){
  sprintf(mess, "UpdateHorse;%d;%d;%d;%d;", connfd, horseID, newLocation, newStepMoved);
}

