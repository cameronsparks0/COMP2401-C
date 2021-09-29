#include "client.h"

//Functions that are used within client.c
void *saveAll(void *tempData){ // Function that writes all the queried data to a user specified file.
    QueryClient *sharedData = (QueryClient*)tempData;
    char *saveFile=(char*) malloc(strlen(sharedData->threadInfo)*sizeof(char)+1); // When the thread is created it creates a copy of threadInfo due to threadInfo being possibly overwritten if the user decides to save.
    strcpy(saveFile,sharedData->threadInfo);
    sem_wait(&sharedData->mutex); // A mutex is used to stop threads from proceding before another thread finishes (To stop memory read/write issues).
    FILE *file = fopen(saveFile,"w");
    fprintf(file,"%s","#,Name,Type 1,Type 2,Total,HP,Attack,Defense,Sp. Atk,Sp. Def,Speed,Generation,Legendary\n"); // Printing the header information to the file (As was in pokemon.csv).
    for(int x=0; x<sharedData->totalPokemon;x++){ // Writing each queried pokemon to a file.
        fprintf(file,"%d%c",sharedData->queriedPokemon[x].number,44);
        fprintf(file,"%s%c",sharedData->queriedPokemon[x].name,44);
        fprintf(file,"%s%c",sharedData->queriedPokemon[x].type1,44);
        fprintf(file,"%s%c",sharedData->queriedPokemon[x].type2,44);
        fprintf(file,"%d%c",sharedData->queriedPokemon[x].total,44);
        fprintf(file,"%d%c",sharedData->queriedPokemon[x].hp,44);
        fprintf(file,"%d%c",sharedData->queriedPokemon[x].atk,44);
        fprintf(file,"%d%c",sharedData->queriedPokemon[x].def,44);
        fprintf(file,"%d%c",sharedData->queriedPokemon[x].spAtk,44);
        fprintf(file,"%d%c",sharedData->queriedPokemon[x].spDef,44);
        fprintf(file,"%d%c",sharedData->queriedPokemon[x].spd,44);
        fprintf(file,"%d%c",sharedData->queriedPokemon[x].gen,44);
        fprintf(file,"%s\n",sharedData->queriedPokemon[x].legendary);
    }
    fclose(file);
    free(saveFile);
    sem_post(&sharedData->mutex);
}