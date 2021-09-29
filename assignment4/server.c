#include "server.h"

int main(int argc, char *argv[]){ 
    //Pokemon related variables
    QueryServer queryData; // The queryData that is generated and sent back to the client.
    memset(&queryData,0,sizeof(QueryServer)); // Initializing the query data to avoid null pointers.

    //Server related variables
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddr;
    int status, addrSize, bytesRcv;

    enterCsv(&queryData); // For the admin to enter the pokemon file (The ONLY user input on server side)

    // Create the server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket < 0) {
        printf("*** SERVER ERROR: Could not open socket.\n");
        exit(-1);
    }

    // Setup the server address
    memset(&serverAddress, 0, sizeof(serverAddress)); // zeros the struct
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddress.sin_port = htons((unsigned short) SERVER_PORT);

    // Bind the server socket
    status = bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (status < 0) {
        printf("*** SERVER ERROR: Could not bind socket.\n");
        exit(-1);
    }

    // Set up the line-up to handle up to 1 clients in line (Doesn't really matter as no more then 1 user will be connecting at a time.)
    status = listen(serverSocket, 1);
    if (status < 0) {
        printf("*** SERVER ERROR: Could not listen on socket.\n");
        exit(-1);
    }

    while (1) { // Infinite loop that picks up new clients unless forcefully closed (CTRL-c, etc) - As per the assignment it doesn't mention the server exiting anywhere.
        addrSize = sizeof(clientAddr);
        clientSocket = accept(serverSocket,(struct sockaddr *)&clientAddr,&addrSize); // Accept the connecting client
        if (clientSocket < 0) {
            printf("*** SERVER ERROR: Could accept incoming client connection.\n");
            exit(-1);
        }

        // Go into infinite loop to talk to client
        while (1) {
            // Get the message from the client
            bytesRcv = recv(clientSocket, queryData.queryInfo, 50, 0); // Receiving the pokemon type1 that is going to be queried.
            queryData.queryInfo[bytesRcv] = 0; // put a 0 at the end so we can display the string

            if (strcmp(queryData.queryInfo,"done") == 0)
            break;

            typeSearch(&queryData); // Query the sent over type1.

            send(clientSocket, &(queryData.totalPokemon), sizeof(queryData.totalPokemon), 0); // Sending over the total pokemon (For memory allocation purposes)
            send(clientSocket, &(queryData.totalQueries), sizeof(queryData.totalQueries), 0);
            if(queryData.totalPokemon!=0){ // Only need to send the queried pokemon if at least one pokemon has actually been queried.
                send(clientSocket, queryData.queriedPokemon, sizeof(Pokemon)*queryData.totalPokemon, 0);
            }
        }

        close(clientSocket); // Close this client's socket

        if(queryData.totalPokemon!=0){
            free(queryData.queriedPokemon);
            queryData.totalPokemon=0;
            queryData.totalQueries=0;
        }
    }   

    // The code will never reach this part as the infinite loop never breaks.
    close(serverSocket); // Keeping this code as a reminder of what should happen if the server were to actually close.
    return(EXIT_SUCCESS);
}
