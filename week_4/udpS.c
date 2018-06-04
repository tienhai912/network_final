#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#define SERV_PORT 1255
#define MAXLINE 255
int main()
{
   int sockfd, n;
   socklen_t len;
   char mesg[MAXLINE]; 
   struct sockaddr_in servaddr, cliaddr;
 
   sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
   bzero(&servaddr, sizeof(servaddr)); 
   servaddr.sin_family = AF_INET; 
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
   servaddr.sin_port = htons(SERV_PORT); 
   if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))>=0)
  {
    printf("Server is running at port %d\n", SERV_PORT);
  }
  else
    {
    perror("bind failed");
    return 0;
    }

   for ( ; ; ) { 
  len = sizeof(cliaddr); 
  printf("Receiving data ...\n");
  n = recvfrom(sockfd, mesg, MAXLINE, 0, (struct sockaddr *) &cliaddr, &len); 
  recvline[n] = 0;
  printf(mesg);
  printf("From Client: %s %d %s\n", inet_ntoa(cliaddr.sin_addr), htons(cliaddr.sin_port), mesg);
  printf("Sending data : %s\n",mesg );
  sendto(sockfd, mesg, n, 0, (struct sockaddr *) &cliaddr, len); 
   }
  close(sockfd);
    
  }