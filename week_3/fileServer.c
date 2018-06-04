#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

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
	
 for ( ; ; ) {
		
  clilen = sizeof(cliaddr);
  connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);
  printf("%s\n","Received request...");

  //Read Picture Size
  printf("Reading Picture Size\n");
  int size;
  read(connfd, &size, sizeof(int));

  //Read Picture Byte Array
  printf("Reading Picture Byte Array\n");
  char p_array[size];
  read(connfd, p_array, size);

  //Convert it Back into Picture
  printf("Converting Byte Array to Picture\n");
  FILE *image;
  image = fopen("c1.jpeg", "w");
  fwrite(p_array, 1, sizeof(p_array), image);
  fclose(image);

 close(connfd);	
 }
 //close listening socket
 close (listenfd); 
}

