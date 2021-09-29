#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SERVER_PORT 6000
#define SERVER_IP "127.0.0.1"

typedef struct Pokemon{ // A structure containing the variables needed to store a pokemons information.
    char name[30], type1[9], type2[9], legendary[6]; //Fixed char arrays due to each variable having max string lengths (In reference to pokemon.csv).
    unsigned char hp, atk, def, spAtk, spDef, spd, gen; // stored in unsigned chars due to max value being under 255.
    unsigned int number, total;
}Pokemon;

typedef struct QueryServer{ // A structure containing the variables needed to during the query process.
    char fileDir[50], queryInfo[50]; //Fixed char arrays to account for reasonably lengthed file-paths to be entered. queryInfo is used to store pokemon type1.
    Pokemon *queriedPokemon; // Dynamic pokemon array that will hold all queried pokemon.
    int totalPokemon, totalQueries;
}QueryServer;

void typeSearch(QueryServer *queryData); // Server functions
void stringAssign(char *str, FILE *file);
void pokemonAssign(QueryServer *queryData, Pokemon pokemon);
void emptyTempPokemon(Pokemon *pokemon);
void enterCsv(QueryServer *queryData);