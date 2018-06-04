#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8 /*maximum number of client connections */

int main (int argc, char **argv)
{
  int listenfd, connfd, n;
  pid_t childpid;
  socklen_t clilen;
  char buf[MAXLINE];
  struct sockaddr_in cliaddr, servaddr;

  //creation of the socket
  listenfd = socket (AF_INET, SOCK_STREAM, 0);

  //preparation of the socket address
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);

  bind (listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

  listen (listenfd, LISTENQ);

  printf("%s\n","Server running...waiting for connections.");

  //
  int j=2;
  int temp[j], i, k;
  i=0;
  //

  for ( ; ; ) {

    clilen = sizeof(cliaddr);
    connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);
    printf("%s\n","Received request...");

    if ( (n = recv(connfd, buf, MAXLINE,0)) > 0)  {
      printf("%s","String received from and resent to the client:");
      puts(buf);
      send(connfd, buf, n, 0);
      temp[i] = connfd;

      if(i<j-1){
        i++;
      } else {
        printf("New game!\n");
        for(k=0;k<=i;k++){
          printf("Player %d: %d\n", k+1, temp[k]);
        }
        i = 0;
      }
    }

    if (n < 0) {
      perror("Read error");
      exit(1);
    }
    //close(connfd);

  }
  //close listening socket
  close (listenfd);
}