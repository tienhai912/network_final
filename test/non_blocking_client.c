#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

int client_sock_fd;

void signio_handler(int signo)
{
  char buff[1024];
  int n = recv(client_sock_fd, buff, sizeof buff, 0);
  if (n>0) // if SIGIO is generated by a data arrival
    printf("Received from server (%d bytes), content: %s\n",n, buff);
}
int main()
{
  struct sockaddr_in client_socket;
  struct sockaddr_in server_socket;
  client_sock_fd = socket(AF_INET, SOCK_STREAM,0);
  
  server_socket.sin_family=AF_INET;
  server_socket.sin_port = htons(3000);
  server_socket.sin_addr.s_addr=inet_addr("172.17.0.2");
  printf("server IP = %s ", inet_ntoa(server_socket.sin_addr));
 
  if (connect(client_sock_fd, (struct sockaddr *) &server_socket, sizeof(server_socket)) <0)
    printf("Error in connecting to server\n");
  else
    printf("connected to server\n");
 
  // Signal driven I/O mode and NONBlOCK mode so that recv will not block 
  if(fcntl(client_sock_fd, F_SETFL, O_NONBLOCK|O_ASYNC))
      printf("Error in setting socket to async, nonblock mode");  
  
  signal(SIGIO, signio_handler); // assign SIGIO to the handler

  //set this process to be the process owner for SIGIO signal 
  if (fcntl(client_sock_fd, F_SETOWN, getpid()) <0)
      printf("Error in setting own to socket");
    
  char str[50];
  while (1)
      {
  printf("Client: ");
  gets(str);  
  send(client_sock_fd, str, sizeof(str),0);
      }

}
