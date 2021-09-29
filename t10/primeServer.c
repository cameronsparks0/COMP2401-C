#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <math.h>
#define SERVER_PORT 6000

void *prime(void *n, char *response);

int main() {
    int serverSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int status, addrSize, bytesReceived;
    fd_set readfds, writefds;
    char buffer[30];
    char response[30];
    // Create the server socket
    serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (serverSocket < 0) {
        printf("*** SERVER ERROR: Could not open socket.\n");
        exit(-1);
    }
    // Setup the server address
    memset(&serverAddr, 0, sizeof(serverAddr)); // zeros the struct
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons((unsigned short) SERVER_PORT);
    // Bind the server socket
    status = bind(serverSocket,(struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (status < 0) {
        printf("*** SERVER ERROR: Could not bind socket.\n");
        exit(-1);
    }
    // Wait for clients now
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(serverSocket, &readfds);
        FD_ZERO(&writefds);
        FD_SET(serverSocket, &writefds);
        status = select(FD_SETSIZE, &readfds, &writefds, NULL, NULL);
        if (status == 0) { // Timeout occurred, no client ready
        }
        else if (status < 0) {
            printf("*** SERVER ERROR: Could not select socket.\n");
            exit(-1);
        }
        else {
            addrSize = sizeof(clientAddr);
            bytesReceived = recvfrom(serverSocket, buffer, sizeof(buffer),0, (struct sockaddr *) &clientAddr, &addrSize);
            if (bytesReceived > 0) {
                buffer[bytesReceived] = '\0';
                printf("SERVER: Received client request: %s\n", buffer);
                long int temp = atoi(buffer);
                prime(&temp, response);
            }
            // Respond with an "OK" message
            printf("SERVER: Sending \"%s\" to client\n", response);
            sendto(serverSocket, response, strlen(response), 0,
            (struct sockaddr *) &clientAddr, addrSize);
            // If the client said to stop, then I'll stop myself
            if (strcmp(buffer, "stop") == 0)
            break;
        }
    }
}

void *prime(void *n, char *response) {
  int i;
  long int num = *((long int *)n);
  int max = (int) sqrt(num);
  for (i = 2; i <= max; i++) {
    usleep(1000);
    if (num % i == 0) {
      printf("SERVER: Received Number: %ld is not prime\n", num);
      strcpy(response,"number is not prime");
      return NULL;
    }
  }
  printf("SERVER: Received Number: %ld is prime\n", num);
  strcpy(response,"number is a prime");
}