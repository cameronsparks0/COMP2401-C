#!/bin/sh
#Assignment5-CameronSparks
echo Saving Pokemon Data To Directories...
POKEMON_ALL=`cat pokemon.csv | tr ' ' @` #Replacing empty spaces with @ to make sure POKEMON_ALL saves each line correctly
for TEMP_POKEMON in $POKEMON_ALL
do
    TYPE=`echo $TEMP_POKEMON | cut -d "," -f 3` #Grabbing the pokemon type from each line
    if [ $TYPE != Type@1 ]; then #Excluding the header type
        if [ ! -d $TYPE ]; then #Making sure the directory does not exist before trying to create it
            mkdir $TYPE
        fi
        if [ ! -f "${TYPE}/${TYPE}.csv" ]; then #Making sure the csv file does not exist before trying to create it
            touch "${TYPE}/${TYPE}.csv"
            FINAL_POKEMON=`echo $TEMP_POKEMON | tr @ ' '` #Adding back the empty spaces
            echo "$FINAL_POKEMON" >> "${TYPE}/${TYPE}.csv"
        else
            FINAL_POKEMON=`echo $TEMP_POKEMON | tr @ ' '`
            echo "$FINAL_POKEMON" >> "${TYPE}/${TYPE}.csv"
        fi
    fi
done
echo DONE!