#include "pokemon.h"

void enterCsv(Shared *sharedData){ // Function that prompts the user to enter a csv file. 
    while(1){
        printf("Please enter the name of the pokemon CSV file (q to Quit): ");
        scanf("%s",sharedData->fileDir); //The CSV filename is stored in sharedData because the threads will all use it.
        if(strcmp(sharedData->fileDir,"q")==0){
            exit(EXIT_SUCCESS);
        }
        if(access(sharedData->fileDir,F_OK)==0){ // Checking if the filename exists.
            system("clear");
            break;
        }
        else{
            printf("Pokemon file is not found. Please enter the name of the file again.\n");
        }
    }
}

void *saveAll(void *tempData){ // Function that writes all the queried data to a user specified file.
    Shared *sharedData = (Shared*)tempData;
    char *saveFile=(char*) malloc(strlen(sharedData->threadInfo)*sizeof(char)+1); // When the thread is created it creates a copy of threadInfo due to threadInfo being possibly overwritten if the user decides to query or save.
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

void *typeSearch(void *tempData){ // Function that searches a file for pokemon with a matching type1 and adds it's data to memory.
    Shared *sharedData = (Shared*)tempData;
    char *pokeType = (char*) malloc(strlen(sharedData->threadInfo)*sizeof(char)+1);
    strcpy(pokeType,sharedData->threadInfo);

    sem_wait(&sharedData->mutex);
    Pokemon tempPokemon; // Used to store a temporary pokemon and then possibly add it to memory.
    char charTemp;
    int isSuccess=0;

    FILE *file;
    file = fopen(sharedData->fileDir,"r");
    fseek(file,sizeof(char)*88,SEEK_SET); // Skipping the initial part of the CSV file as it does not need to be parsed.


    while(!feof(file)){ // Scanning each line of the file and parsing pokemon based on type.
        fscanf(file,"%d",&tempPokemon.number); // Storing a line of information in a temp pokemon.
        if(feof(file)){
            break;
        }
        fscanf(file,"%c",&charTemp); // Storing a line of information in a temp pokemon.
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

        if(strcmp(tempPokemon.type1,pokeType)==0){ // Checking if the temp pokemon has the correct type1.
            isSuccess++;
            pokemonAssign(sharedData,tempPokemon); // Adding the temp pokemon to the query data (Shared between threads).
        }
        emptyTempPokemon(&tempPokemon);
    }
    if(isSuccess!=0){ // Only updating the total succesful queries if the type actually exists.
        sharedData->totalQueries++;
    }
    fclose(file);
    free(pokeType);
    sem_post(&sharedData->mutex);

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

void pokemonAssign(Shared *sharedData, Pokemon pokemon){ // Function that copies the data from the tempPokemon over to the final query array.
    sharedData->queriedPokemon[sharedData->totalPokemon].number=pokemon.number;
    strcpy(sharedData->queriedPokemon[sharedData->totalPokemon].name,pokemon.name);
    strcpy(sharedData->queriedPokemon[sharedData->totalPokemon].type1,pokemon.type1);
    strcpy(sharedData->queriedPokemon[sharedData->totalPokemon].type2,pokemon.type2);
    sharedData->queriedPokemon[sharedData->totalPokemon].total = pokemon.total;
    sharedData->queriedPokemon[sharedData->totalPokemon].hp = pokemon.hp;
    sharedData->queriedPokemon[sharedData->totalPokemon].atk = pokemon.atk;
    sharedData->queriedPokemon[sharedData->totalPokemon].def = pokemon.def;
    sharedData->queriedPokemon[sharedData->totalPokemon].spAtk = pokemon.spAtk;
    sharedData->queriedPokemon[sharedData->totalPokemon].spDef = pokemon.spDef;
    sharedData->queriedPokemon[sharedData->totalPokemon].spd = pokemon.spd;
    sharedData->queriedPokemon[sharedData->totalPokemon].gen = pokemon.gen;
    strcpy(sharedData->queriedPokemon[sharedData->totalPokemon].legendary,pokemon.legendary);
    sharedData->queriedPokemon = realloc(sharedData->queriedPokemon,(sharedData->totalPokemon+2)*sizeof(Pokemon));
    sharedData->totalPokemon = sharedData->totalPokemon + 1;
}