#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8 /*maximum number of client connections*/

int main (int argc, char **argv){
  int listenfd, connfd, n;
  pid_t childpid;
  socklen_t clilen;
  char buf[MAXLINE];
  struct sockaddr_in cliaddr, servaddr;

  //Create a socket for the soclet
  //If sockfd<0 there was an error in the creation of the socket
  if ((listenfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
    perror("Problem in creating the socket");
    exit(2);
  }


  //preparation of the socket address
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);

  //bind the socket
  bind (listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

  //listen to the socket by creating a connection queue, then wait for clients
  listen (listenfd, LISTENQ);

  printf("%s\n","Server running...waiting for connections.");

  int maxPlayer=2;
  int temp[maxPlayer], i, countPlayer;
  countPlayer=0;

  for ( ; ; ) {

    clilen = sizeof(cliaddr);
    //accept a connection
    connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);

    printf("%s\n","Received request...");

    if ( (n = recv(connfd, buf, MAXLINE,0)) > 0)  {
      printf("%s","String received from and resent to the client:");
      puts(buf);
      send(connfd, buf, n, 0);
      temp[countPlayer] = connfd;

      if(countPlayer<maxPlayer-1){
        countPlayer++;
      } else {
        //Noti
        printf("New game!\n");
        for(i=0 ; i<maxPlayer ; i++){
          printf("Player %d: connfd:\"%d\"\n", i+1, temp[i]);
        }
        countPlayer = 0;

        // Fork new room
        if ( (childpid = fork ()) == 0 ) {

          printf ("%s\n","Room created!\n");

          close (listenfd);
          countPlayer = 0;
          connfd = temp[countPlayer];

          while ( (n = recv(connfd, buf, MAXLINE,0)) > 0)  {
            printf("String received from and resent to the clien %d: ", connfd);
            puts(buf);
            send(connfd, buf, n, 0);
            if(countPlayer<maxPlayer-1){
              countPlayer++;
              connfd = temp[countPlayer];
            } else {
              countPlayer=0;
              connfd = temp[countPlayer];
            }
            printf("End a connection\n");
          }

          if (n < 0)
            printf("%s\n", "Read error");
          exit(0);
        }
      }
    }

    if (n < 0) {
      perror("Read error");
      exit(1);
    }
  }
}
