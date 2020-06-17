#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>


int main(int argc, char** argv){

  int clientSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  clientSocket = socket(PF_INET, SOCK_STREAM, 0);

  serverAddr.sin_family = AF_INET;

  int port_no = atoi(argv[1]);


// initlize the port and IP address


  serverAddr.sin_port = htons(port_no);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);


  addr_size = sizeof serverAddr;
//Make connection to the port and set up socket to that port

  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

//check to see if the server is recieving the message to connect
  recv(clientSocket, buffer, 1024, 0);
  printf (" The server has accepeted connection request and sent acknowledgement message as : %s", buffer);

  label:

  fgets (buffer, 1024, stdin);


  if(buffer[0] == 'p')
  {

    send(clientSocket,buffer,sizeof(buffer),0);
    printf("Please enter your hiss: \n");

    fgets (buffer, 1024, stdin);
    send(clientSocket,buffer,sizeof(buffer),0);
    goto label;
  }
  else if (buffer[0] == 'g')
  {
    send(clientSocket,buffer,sizeof(buffer),0);
    goto label;
  }
  else
  {
    send(clientSocket,buffer,sizeof(buffer),0);
    recv(clientSocket, buffer, 1024, 0);
    printf("Message from server %s ", buffer);
}

  return 0;

}
