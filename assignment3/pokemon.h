#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

typedef struct Pokemon{ // A structure containing the variables needed to store a pokemons information.
    char name[30], type1[9], type2[9], legendary[6]; //Fixed char arrays due to each variable having max string lengths (In reference to pokemon.csv).
    unsigned char hp, atk, def, spAtk, spDef, spd, gen; // stored in unsigned chars due to max value being under 255.
    unsigned int number, total;
}Pokemon;

typedef struct Shared{ // A structure containing the variables needed to be shared between threads.
    char fileDir[50], threadInfo[50]; //Fixed char arrays to account for reasonably lengthed file-paths to be entered. threadInfo is multipurposed and is used to store file-paths and pokemon type1 (Depends on thread).
    Pokemon *queriedPokemon; // Dynamic pokemon array that will hold all queried pokemon.
    int totalPokemon, totalQueries;
    sem_t mutex;
}Shared;

void *typeSearch(void *tempData);
void stringAssign(char *str, FILE *file);
void pokemonAssign(Shared *sharedData, Pokemon pokemon);
void emptyTempPokemon(Pokemon *pokemon);
void *saveAll(void *tempData);
void enterCsv(Shared *sharedData);