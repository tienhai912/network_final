#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAXLINE 409600 /*max text line length*/
#define SERV_PORT 3000 /*port*/

int main (int argc, char **argv) {
  int sockfd;
  struct sockaddr_in servaddr;
  char sendline[MAXLINE], recvline[MAXLINE];

  /* check input */
  if (argc !=2) {
    perror("Error: Usage: TCPClient <IP address of the server"); 
    exit(1);
  }

  /* create socket */
  if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
    perror("Problem in creating the socket");
    exit(2);
  }

  /* make server entity */
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr= inet_addr(argv[1]);
  servaddr.sin_port =  htons(SERV_PORT);

  /* connect socket to server */
  if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
    perror("Problem in connecting to the server");
    exit(3);
  }
  /* new */
  printf("%s\n", "Connected!!");


  char fileName[100] = "send.jpg";
  FILE* f1;
  int m =0;

  //printf("%s", "Enter file name: ");
  //scanf("%[^\n]", fileName);
  ///scanf("%*c");
  f1 = fopen(fileName, "r+");
  if (f1==NULL){
    perror("Error: Cannot read file"); 
    exit(5);
  }

  char signal[100] = "Start sending image";

  send(sockfd, signal, strlen(signal), 0);

  printf("%s\n", "Continue!!");
  recv(sockfd, recvline, MAXLINE,0);

  while ((fgets(sendline, MAXLINE, f1) != NULL) && (strcmp(recvline, "Next")==0)) {
    printf("%s: %d\n", "Continue!!", m);
    m++;
    /* send to server */
    send(sockfd, sendline, strlen(sendline), 0);
    printf("%s\n", "next1!!");
    /* receive from server */
    printf("%s\n", "next2!!");
    for(int i=0; i<=20000000; i++);
    recv(sockfd, recvline, MAXLINE,0);
  }

  printf("%s\n", "Finished!!");
  fclose(f1);

  char endSignal[100] = "Finish sending image";
  send(sockfd, endSignal, strlen(endSignal), 0);

  printf("%s\n", "Finished2!!");
  /* new */

 exit(0);

}
