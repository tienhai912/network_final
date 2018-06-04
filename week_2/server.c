#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8 /*maximum number of client connections */

int main (int argc, char **argv){
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

  /* bind socket to server */
  bind (listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

  listen (listenfd, LISTENQ);

  printf("%s\n","Server running...waiting for connections.");

  /* new */
  char signal[100] = "Start sending image";
  char endSignal[100] = "Finish sending image";
  int m =0;
  FILE* f1= fopen("receive.jpg", "w+");;
  /* new */

  for ( ; ; ) {

    clilen = sizeof(cliaddr);
    connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);
    //
    //struct sockaddr_in clientaddr;
    //clientaddr = inet_pton(connfd);
    //printf("%d\n", inet_pton(clientaddr.sin_addr.s_addr));
    //printf("%d\n", ntohs(clientaddr.sin_port));

    printf ("%d\n", connfd);

    //
    printf("%s\n","Received request...");
    
    while ( (n = recv(connfd, buf, MAXLINE,0)) > 0)  {
      /* new */
      if (strcmp(buf, signal)==0) {
        printf("%s\n", "Start!!");
        f1 = fopen("receive.jpg", "w+");
        send(connfd, "Next", strlen("Next"), 0);
      } else if (strcmp(buf, endSignal)==0) {
        printf("%s\n", "Finished!!");
        fclose(f1);
        break;
      } else {
        printf("%s: %d\n", "Continue!!", m);
        m++;
        fprintf(f1, buf);
        printf("%s\n", "Not core dumped here");
        send(connfd, "Next", strlen("Next"), 0);
      }
      /* new */
    }

    printf("%s\n", "wrong!!");
        
    if (n < 0) {
      perror("Read error"); 
      exit(1);
    }
    close(connfd);

  }
  //close listening socket
  close (listenfd); 
}
