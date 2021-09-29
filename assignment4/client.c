#include "client.h"

int main() {
    //Pokemon related variables
    QueryClient sharedData; // The query data that is shared between threads and used for saving.
    memset(&sharedData,0,sizeof(QueryClient)); // Initializing the query data to avoid null pointers.
    char queryInfo[50];
    int userOption;
    int numThreads=0, numNames=0;
    char **saveFileNames; // A string array to hold all saved file names.

    // Network variables
    int clientSocket, status;
    struct sockaddr_in serverAddress;

    sharedData.queriedPokemon = (Pokemon*) malloc(sizeof(Pokemon)); // Dynamically allocating starting memory to each pointer (potentially reallocated after).
    pthread_t *threads = (pthread_t*) malloc(sizeof(pthread_t));
    saveFileNames = (char**) malloc(sizeof(char*));

    sem_init(&sharedData.mutex,0,1); // Initializing a mutex to regulate threads.

    // Create the client socket
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket < 0) {
        printf("*** CLIENT ERROR: Could not open socket.\n");
        free(saveFileNames);
        free(threads);
        free(sharedData.queriedPokemon);
        exit(-1);
    }

    // Setup address
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddress.sin_port = htons((unsigned short) SERVER_PORT);

    // Connect to server
    status = connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    if (status < 0) {
        printf("Unable to establish connection to the PPS!\n");
        free(saveFileNames);
        free(threads);
        free(sharedData.queriedPokemon);
        exit(-1);
    }

    printf("Welcome to the pokemon program!\n");
    // Go into loop to commuincate with server now
    while (1) {
        printf("Option 1: Type search\nOption 2: Save results\nOption 3: Exit the program\n");
        printf("Select an option (1,2 or 3): ");
        scanf("%d",&userOption);

        if(userOption==1){ // Type search.
            printf("Please enter a type to search: ");
            scanf("%s",queryInfo);
            send(clientSocket, queryInfo, strlen(queryInfo), 0); // Sending over the type1 to be queried
            
            recv(clientSocket,&(sharedData.totalPokemon),4,0); // Receiving the amount of pokemon queried -> Used to allocate memory for the incoming queried pokemon (pokemon array)
            recv(clientSocket,&(sharedData.totalQueries),4,0);
            if(sharedData.totalPokemon!=0){ // Making sure there was at least one pokemon queried before reallocating memory.
                sharedData.queriedPokemon = realloc(sharedData.queriedPokemon,sharedData.totalPokemon*sizeof(Pokemon));
                recv(clientSocket,sharedData.queriedPokemon,sharedData.totalPokemon*sizeof(Pokemon),0); // Receiving the queried pokemon array.
            }
            system("clear");
        }
        else if(userOption==2){ // Save results
            while(1){
                int flag;
                printf("Please enter the name of a file to save the results in (q to Quit): ");
                scanf("%s",sharedData.threadInfo); //threadInfo being used for the save file-path.
                if(strcmp(sharedData.threadInfo,"q")==0){
                    system("clear");
                    break;
                }
                flag = access(sharedData.threadInfo,F_OK);
                FILE *file = fopen(sharedData.threadInfo,"a");
                if(flag!=0 && file!=NULL){ // Only writing to the file if it is NEW (Would be dangerous if the user could write to any file).
                    fclose(file);
                    pthread_create(&threads[numThreads++],NULL,saveAll,&sharedData); // Creating a thread for each save (So the program can instantly resume).
                    threads = realloc(threads,(numThreads+1)*sizeof(pthread_t));
                    saveFileNames[numNames] = malloc(strlen(sharedData.threadInfo)+1); // Allocating data for and adding the new file name to the string array.
                    strcpy(saveFileNames[numNames++],sharedData.threadInfo);
                    saveFileNames = realloc(saveFileNames,(numNames+1)*sizeof(char*));
                    system("clear");
                    break;
                }
                else{
                    fclose(file);
                    printf("Unable to create the new file. Please enter the name of the file again\n");
                }
            }
        }

        else{// Exit the program.
            strcpy(queryInfo,"done");
            queryInfo[4]='\0';
            send(clientSocket, queryInfo, strlen(queryInfo), 0); // Sending a "done" signal to the server so the server can pick up another client.
            system("clear");
            break;
        }
    }
    close(clientSocket);

    for(int x=0; x<numThreads; x++){ // Stopping the threads.
        pthread_detach(threads[x]); // Function makes the threads resources return back to the system without needing to join.
        pthread_cancel(threads[x]); // Implicitly exits the thread.
    }

    printf("Total successful Queries: %d\n",sharedData.totalQueries);
    printf("Saved Files: ");
    for(int x=0; x<numNames; x++){ 
        printf("%s%c ",saveFileNames[x],44);
        free(saveFileNames[x]);
    }

    printf("\n~~Thanks for using the pokemon program!~~\n");
    free(saveFileNames);
    free(threads);
    free(sharedData.queriedPokemon);
    return(EXIT_SUCCESS);
}