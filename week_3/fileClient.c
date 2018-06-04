#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/

int main(int argc, char **argv) 
{
 int sockfd;
 struct sockaddr_in servaddr;
 char sendline[MAXLINE], recvline[MAXLINE];
	
 //basic check of the arguments
 //additional checks can be inserted
 if (argc != 3) {
  perror("Usage: TCPClient <IP address of the server>"); 
  exit(1);
 }
	
 //Create a socket for the client
 //If sockfd<0 there was an error in the creation of the socket
 if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
  perror("Problem in creating the socket");
  exit(2);
 }
	
 //Creation of the socket
 memset(&servaddr, 0, sizeof(servaddr));
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr= inet_addr(argv[1]);
 servaddr.sin_port =  htons(SERV_PORT); //convert to big-endian order
	
 //Connection of the client to the socket 
 if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
  perror("Problem in connecting to the server");
  exit(3);
 }
 
  //Get Picture Size
  printf("Getting Picture Size\n");
  FILE *picture;
  picture = fopen(argv[2], "r");
  int size;
  fseek(picture, 0, SEEK_END);
  size = ftell(picture);
  fseek(picture, 0, SEEK_SET);

  //Send Picture Size
  printf("Sending Picture Size\n");
  write(sockfd, &size, sizeof(size));

  //Send Picture as Byte Array
  printf("Sending Picture as Byte Array\n");
  char send_buffer[size];
  while(!feof(picture)) {
      fread(send_buffer, 1, sizeof(send_buffer), picture);
      write(sockfd, send_buffer, sizeof(send_buffer));
      bzero(send_buffer, sizeof(send_buffer));
  }	
 exit(0);
}

