#include "server.h"

//Functions that are used within server.c
void enterCsv(QueryServer *queryData){ // Function that prompts the user to enter a csv file. 
    while(1){
        printf("Please enter the name of the pokemon CSV file (q to Quit): ");
        scanf("%s",queryData->fileDir); // Storing the filename in queryData to organize all the data that will be used in the Query process.
        if(strcmp(queryData->fileDir,"q")==0){
            exit(EXIT_SUCCESS);
        }
        if(access(queryData->fileDir,F_OK)==0){ // Checking if the filename exists.
            system("clear");
            break;
        }
        else{
            printf("Pokemon file is not found. Please enter the name of the file again.\n");
        }
    }
}

void typeSearch(QueryServer *queryData){ // Function that searches a file for pokemon with a matching type1 and adds it's data to memory.
    Pokemon tempPokemon; // Used to store a temporary pokemon and then possibly add it to memory.
    char charTemp;
    int isSuccess=0;

    FILE *file;
    file = fopen(queryData->fileDir,"r");
    fseek(file,sizeof(char)*88,SEEK_SET); // Skipping the initial part of the CSV file as it does not need to be parsed.


    while(!feof(file)){ // Scanning each line of the file and parsing pokemon based on type.
        fscanf(file,"%d",&tempPokemon.number); // Storing a line of information in a temp pokemon.
        if(feof(file)){
            break;
        }
        fscanf(file,"%c",&charTemp);
        stringAssign(tempPokemon.name,file);
        stringAssign(tempPokemon.type1,file);
        stringAssign(tempPokemon.type2,file);
        fscanf(file,"%d%c",&tempPokemon.total,&charTemp);
        fscanf(file,"%hhd%c",&tempPokemon.hp,&charTemp);
        fscanf(file,"%hhd%c",&tempPokemon.atk,&charTemp);
        fscanf(file,"%hhd%c",&tempPokemon.def,&charTemp);
        fscanf(file,"%hhd%c",&tempPokemon.spAtk,&charTemp);
        fscanf(file,"%hhd%c",&tempPokemon.spDef,&charTemp);
        fscanf(file,"%hhd%c",&tempPokemon.spd,&charTemp);
        fscanf(file,"%hhd%c",&tempPokemon.gen,&charTemp);
        stringAssign(tempPokemon.legendary,file);

        if(strcmp(tempPokemon.type1,queryData->queryInfo)==0){ // Checking if the temp pokemon has the correct type1.
            isSuccess++;
            pokemonAssign(queryData,tempPokemon); // Adding the temp pokemon to the query data.
        }
        emptyTempPokemon(&tempPokemon);
    }
    if(isSuccess!=0){ // Only updating the total succesful queries if the type actually exists.
        queryData->totalQueries++;
    }
    fclose(file);

}

void stringAssign(char *str, FILE *file){ // Function that copies a string from a file into a character array.
    char charTemp;
    fscanf(file,"%c",&charTemp); // To get rid of the initial (,).
    while(charTemp != 44 && charTemp!= '\n') { // Adding each character to the character array if it is not a (,) or (\n).
        *str = charTemp;
        str++;
        fscanf(file,"%c",&charTemp);
    }
    *str='\0';
}

void emptyTempPokemon(Pokemon *pokemon){ // Function that resets the memory of the tempPokemon.
    memset(pokemon->name,0,strlen(pokemon->name));
    memset(pokemon->type1,0,strlen(pokemon->type1));
    memset(pokemon->type2,0,strlen(pokemon->type2));
    memset(pokemon->legendary,0,strlen(pokemon->legendary));
}

void pokemonAssign(QueryServer *queryData, Pokemon pokemon){ // Function that copies the data from the tempPokemon over to the final pokemon array.
    if(queryData->totalPokemon==0){
        queryData->queriedPokemon = (Pokemon*) malloc(sizeof(Pokemon)); // Dynamically allocating starting memory to the pointer (reallocated if more then 1 pokemon)
    }
    else{
        queryData->queriedPokemon = realloc(queryData->queriedPokemon,(queryData->totalPokemon+2)*sizeof(Pokemon));
    }

    memset(&(queryData->queriedPokemon[queryData->totalPokemon]),0,sizeof(Pokemon)); //Making sure all memory is initialized before sending back to client.

    queryData->queriedPokemon[queryData->totalPokemon].number=pokemon.number;
    strcpy(queryData->queriedPokemon[queryData->totalPokemon].name,pokemon.name);
    strcpy(queryData->queriedPokemon[queryData->totalPokemon].type1,pokemon.type1);
    strcpy(queryData->queriedPokemon[queryData->totalPokemon].type2,pokemon.type2);
    queryData->queriedPokemon[queryData->totalPokemon].total = pokemon.total;
    queryData->queriedPokemon[queryData->totalPokemon].hp = pokemon.hp;
    queryData->queriedPokemon[queryData->totalPokemon].atk = pokemon.atk;
    queryData->queriedPokemon[queryData->totalPokemon].def = pokemon.def;
    queryData->queriedPokemon[queryData->totalPokemon].spAtk = pokemon.spAtk;
    queryData->queriedPokemon[queryData->totalPokemon].spDef = pokemon.spDef;
    queryData->queriedPokemon[queryData->totalPokemon].spd = pokemon.spd;
    queryData->queriedPokemon[queryData->totalPokemon].gen = pokemon.gen;
    strcpy(queryData->queriedPokemon[queryData->totalPokemon].legendary,pokemon.legendary);
    queryData->totalPokemon = queryData->totalPokemon + 1;
}