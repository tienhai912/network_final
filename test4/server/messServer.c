#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
//**********mmap**********
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
//_________________________

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8 /*maximum number of client connections*/

typedef struct {
  int id;
  char name[20];
  struct sockaddr_in cliaddr;
} player;

player* newPlayer(player* playerList, int id, char* name, struct sockaddr_in cliaddr){
  if (id > 3){
    perror("Room is full");
  }
  (playerList + id)->id = id;
  strcpy((playerList + id)->name, name);
  (playerList + id)->cliaddr = cliaddr;
}

player* newSinglePlayer(char* name, struct sockaddr_in cliaddr){
  player* tempPlayer = (player*) malloc(sizeof(player*));
  tempPlayer->id = 1;
  strcpy(tempPlayer->name, name);
  tempPlayer->cliaddr = cliaddr;
  return tempPlayer;
}

void sendNewPlayer(player* tempPlayer, int connfd, struct sockaddr_in cliaddr){
  char mess[100];
  char idString[10];

  snprintf (idString, sizeof(idString), "%d",tempPlayer->id);
  strcpy(mess, idString);
  strcat(mess, ";");
  strcat(mess, tempPlayer->name);
  strcat(mess, ";");
  char str1[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &(cliaddr.sin_addr), str1, INET_ADDRSTRLEN );
  strcat(mess, str1);
  strcat(mess, ";");
  send(connfd, mess, strlen(mess), 0);
}

int readMess(char *mess, int connfd, struct sockaddr_in cliaddr){
  char* messType, playerName;

  char tokeLine[2] = ";";
  char tokeData[2] = ":";
  char* token, tokenKey, tokenInfo;
  token = strtok(mess, tokeLine);

  printf("before token: %s\n", token);
  if (token != NULL){
    printf("Enter token\n");
    tokenKey = strtok(token, tokeData);
    printf("token 0.1: key: %s\n", tokenKey);
    strcpy(tokenInfo, token);
    printf("token 0.5: key: %s, info: %s\n", tokenKey, tokenInfo);

    if ((tokenKey == NULL) || (tokenInfo == NULL)){
      printf("Message error\n");
      return 0;
    }
    printf("token 1: key: %s\n", tokenKey);

    if (strcmp(tokenKey, "MessageType")==0){
      if (strcmp(tokenInfo, "NewPlayer")==0){
        //MessageType:NewPlayer;PlayerName:NTHai;
        printf("token 2\n");
        token = strtok(mess, tokeLine);
        tokenKey = strtok(token, tokeData);
        strcpy(tokenInfo, token);
        if (strcmp(tokenKey, "PlayerName")==0){
          printf("token 2\n");
          if (tokenInfo == NULL){
            printf("New player message error\n");
            return 0;
          } else{
            printf("token 3\n");
            player* tempPlayer = newSinglePlayer(tokenInfo, cliaddr);
            sendNewPlayer(tempPlayer, connfd, cliaddr);
          }
        }
      }
    }

  }
  return 1;
}
