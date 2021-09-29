#include "pokemon.h"

int main(int argc, char *argv[]){
    int userOption, numThreads=0, numNames=0;
    Shared sharedData; 
    sharedData.totalPokemon=0, sharedData.totalQueries=0;
    char **saveFileNames; // A string array to hold all saved file names.
    sem_init(&sharedData.mutex,0,1); // Initializing a mutex to regulate threads.

    printf("Welcome to the pokemon program!\n");
    enterCsv(&sharedData);
    
    sharedData.queriedPokemon = (Pokemon*) malloc(sizeof(Pokemon)); // Dynamically allocating starting memory to each pointer (potentially reallocated after).
    pthread_t *threads = (pthread_t*) malloc(sizeof(pthread_t));
    saveFileNames = (char**) malloc(sizeof(char*));

    while(1){ // User menu loop.
        printf("Option 1: Type search\nOption 2: Save results\nOption 3: Exit the program\n");
        printf("Select an option (1,2 or 3): ");
        scanf("%d",&userOption);

        if(userOption==1){ // Type search.
            printf("Please enter a type to search: ");
            scanf("%s",sharedData.threadInfo); //threadInfo being used for pokemon type1 in this case.
            pthread_create(&threads[numThreads++],NULL,typeSearch,&sharedData); //Creating a new thread and passing in a Shared variable to be used by all threads.
            threads = realloc(threads,(numThreads+1)*sizeof(pthread_t)); //The variable "threads" is dynamic due to an infinite amount of possible queries. 
        }

        else if(userOption==2){ // Save Results.
            while(1){
                int flag;
                printf("Please enter the name of a file to save the results in (q to Quit): ");
                scanf("%s",sharedData.threadInfo); //threadInfo being used for file-paths in this case.
                if(strcmp(sharedData.threadInfo,"q")==0){
                    break;
                }
                flag = access(sharedData.threadInfo,F_OK);
                FILE *file = fopen(sharedData.threadInfo,"a");
                if(flag!=0 && file!=NULL){ // Only writing to the file if it is NEW (Would be dangerous if the user could write to any file).
                    fclose(file);
                    pthread_create(&threads[numThreads++],NULL,saveAll,&sharedData);
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
            system("clear");
            break;
        }
    }

    for(int x=0; x<numThreads; x++){ // Stopping the threads even during possible queries.
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

