#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUF_SIZE 60
#define MAXSIZE 300
#define PORT 1234

int main(int argc, char *argv[])
{
  int socket_fd;
  int result_value; // Holds return value
  unsigned int fsize; // Holds from size
  struct sockaddr_in s_in, from; // Socket variables
  char buf [BUF_SIZE+1];// Holds data from socket
  char user_input[MAXSIZE]; 

  socket_fd = socket (AF_INET, SOCK_DGRAM, 0); // Create socket

  bzero((char *) &s_in, sizeof(s_in)); // Clearing the struct
  s_in.sin_family = (short)AF_INET; // Setting IPv4
  s_in.sin_addr.s_addr = htonl(INADDR_ANY); // Setting IP address
  s_in.sin_port = htons((u_short)PORT); // Setting port

  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in)); // Bind the socket to IP+PORT
  fsize = sizeof(from);

  printf("Connected successfully\n");

  result_value = recvfrom(socket_fd, user_input, MAXSIZE, 0, (struct sockaddr *)&from, &fsize);
  if (result_value < 0)
  {
    perror("Error");
    exit(1);
  }

  char * user = strtok(user_input, "/");
  char * password = strtok(NULL, "/");
  char * massage = strtok(NULL, "/");

  char * expected_user = "Idan";
  char * expected_password = "Shoshana";

  if(strcmp(user, expected_user) == 0 && strcmp(password, expected_password) == 0)
  {
    printf("OK\n");
    result_value = sendto(socket_fd, "OK", BUF_SIZE, 0, (struct sockaddr *)&from, sizeof(from));
  } 
  else 
  {
    printf("NO\n");
    result_value = sendto(socket_fd, "NO", BUF_SIZE, 0, (struct sockaddr *)&from, sizeof(from));
  }


  if(result_value < 0)
  {
    perror("A server error occurred");
    exit(2);
  }

  return 0;
}

	

