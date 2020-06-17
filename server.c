#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>


int main(int argc, char** argv){

  fflush(stdin);

  int welcomeSocket, newSocket;
  int j = 0;

  char buffer[1024];
  char hiss[10][140];
  for(j=0;j<10;j++)
  memset(hiss[j], '\0', sizeof(char)*140 );
  int index = 0;
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
  serverAddr.sin_family = AF_INET;

  int port_no = atoi(argv[1]);


  //port 7891
//initilize port, IP and pad the 0's;

  serverAddr.sin_port = htons(port_no);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

// bind the structure to the socked so it can accept requests

  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

//check if the socket is working

  if(listen(welcomeSocket,5)==0)
    printf("Ther sever has been set up on port number : %d \n \n", port_no);
  else
    printf("THe server could not be setup on this port");

  addr_size = sizeof serverStorage;

  //create new socket that can accept requests from client

  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

  strcpy(buffer,"Acknowledged connection request from client \n \n");
  send(newSocket,buffer,sizeof(buffer),0);


    label:
    recv(newSocket, buffer, 1024, 0);

    if(buffer[0] == 'p')
    {
      index = buffer[2] - '0';

      recv(newSocket, buffer, 1024, 0);
      fflush(stdin);
      strcpy(hiss[index], buffer);
      goto label;
    }
    else if(buffer[0] == 'g')
    {
      fflush(stdout);
      fflush(stdin);
      for(int i = 0; i < 10; i++)
      {
        printf("\n%d", i);
        printf(". %s", hiss[i]);
      }
      fflush(stdout);
      fflush(stdin);
      goto label;
    }
    else
    {

      fflush(stdout);
      fflush(stdin);
      for(int i = 0; i < 10; i++)
      {
        printf("\n%d", i);
        printf(". %s", hiss[i]);
      }
      fflush(stdout);
      fflush(stdin);



    strcpy(buffer,"Overwritng \n \n");
    send(newSocket,buffer,sizeof(buffer),0);
    return 0;
  }
  }
