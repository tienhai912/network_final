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

#include "messServer.c"

// typedef struct {
//   int id;
//   char name[20];
//   struct sockaddr_in cliaddr;
// } player;

// int newPlayer(player* playerList, int id, char* name, struct sockaddr_in cliaddr){
//   if (id > 3){
//     perror("Room is full");
//   }
//   (playerList + id)->id = id;
//   strcpy((playerList + id)->name, name);
//   (playerList + id)->cliaddr = cliaddr;
// }

int main (int argc, char **argv){
  int listenfd, connfd, n;
  pid_t childpid;
  socklen_t clilen;
  char buf[MAXLINE];
  struct sockaddr_in cliaddr, servaddr;


  //**********create playerList**********
  player playerList[4];
  // playerList = (*player) malloc(4*sizeof(player));
  int id = 0;

  //________________________________

  //**********Check arg**********
  //Create a socket for the soclet
  //If sockfd<0 there was an error in the creation of the socket
  if ((listenfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
  perror("Problem in creating the socket");
  exit(2);
  }
  //________________________________



  //**********Create socket**********
  //preparation of the socket address
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);

  //bind the socket
  bind (listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
  //________________________________


  //**********Listenning**********
  //listen to the socket by creating a connection queue, then wait for clients
  listen (listenfd, LISTENQ);
  printf("%s\n","Server running...waiting for connections.");
  //________________________________

  int *temp = malloc(sizeof(int));
  *temp = 0;
  temp = mmap(NULL, sizeof *temp, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  for ( ; ; ) {

    //**********Connect**********
    clilen = sizeof(cliaddr);
    //accept a connection
    connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);
    ///////////////////////////////////////////////////////////////////////////////////////////each player has a diferrent socket (connfd)
    printf("%s\n","Received request...");
    //________________________________


    //**********New player**********
    // printf("New player:\n");
    // newPlayer(&playerList, id, "new member", cliaddr);
    // printf("id: %d\nname: %s\n", playerList[id].id, playerList[id].name);
    // id++;

    //________________________________

    //**********player IP**********
    // struct sockaddr_in* pV4Addr = (struct sockaddr_in*) &cliaddr;
    // struct in_addr ipAddr = pV4Addr->sin_addr;

    // char str1[INET_ADDRSTRLEN];
    // inet_ntop(AF_INET, &(cliaddr.sin_addr), str1, INET_ADDRSTRLEN );
    // printf("IP: %s\nEnd of player info\n", str1);

    //________________________________

    //**********Child process**********
    if ( (childpid = fork ()) == 0 ) {//if it’s 0, it’s child process
      //close listening socket
      close (listenfd);

      while ( (n = recv(connfd, buf, MAXLINE,0)) > 0)  {
        ///////////////////////////////////////////////////////////change connfd in recv to change turn(change which player the server is listenning to)
        printf("String received from the client:\"");
        printf("%s\"\n",buf);
        // printf("String send to the client:");
        // send(connfd, buf, n, 0);
        readMess(buf, connfd, cliaddr);
      }

      if (n < 0)
        printf("%s\n", "Read error");
      exit(0);
    }
    //________________________________

    //close socket of the server
    close(connfd);

  }

}