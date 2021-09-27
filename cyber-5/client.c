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
#include <arpa/inet.h>

#define BUF_SIZE 60
#define MAXSIZE 300
#define IP_ADDRESS "127.0.0.1"
#define PORT 1234

int main(int argc, char *argv[])
{
  struct sockaddr_in  dest; // Holds Destination socket (IP+PORT)
  int socket_fd; // Holds socket file descriptor
  unsigned int ssize; // Holds size of dest
  struct hostent *hostptr; // Holds host information
  char buf[BUF_SIZE+1]; // Used for writing / Reading from buffer
  int result_value=0; // Holds return Value for recvfrom() / sendto()
  char *cRetVal=NULL; // Holds return Value for fgets()
  char userpassword[MAXSIZE];
  char answer [BUF_SIZE];

  socket_fd = socket (AF_INET, SOCK_DGRAM, 0); // Create socket
  if (socket_fd==-1) // Validate the socket
  { 
    perror("Create socket"); exit(1);
  }

  if (fcntl(socket_fd, F_SETFL, O_NONBLOCK)!=0) // Set socket for non-blocking
  { 
    perror("Blocking"); exit(1);
  }

  bzero((char *) &dest, sizeof(dest)); // Clearing the structdest.sin_family = (short) AF_INET; // Setting IPv4
  dest.sin_port = htons((u_short)PORT); // Setting port
  dest.sin_addr.s_addr = inet_addr(IP_ADDRESS); // Setting IP address

  ssize = sizeof(dest); // Get dest size

  printf("Connected successfully\n");
  printf("Enter your username/password: ");
  scanf("%s",userpassword);

  result_value = sendto(socket_fd, userpassword, MAXSIZE, 0, (struct sockaddr *)&dest, sizeof(dest));
  if (result_value < 0)
  {
    perror("Write socket error");
    exit(1);
  }

  result_value = recvfrom(socket_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&dest, &ssize);
  while(result_value <= 0)
  {
    sleep(1);
    result_value = recvfrom(socket_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&dest, &ssize);
  }

  buf[result_value]='\0';
  if(strcmp(buf, "NO") == 0)
  {
    printf("User and password are incorrect\n");
  }

  close(socket_fd); // Closing socket
  return 0;
} 
