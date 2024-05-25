#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char* word;

void GenerateAllPassword(char* pwd, int pos, int size){
    if (pos<size){
        for(int i=0; i<strlen(word); i++){
            char *temp =malloc(sizeof(char)*size+1);
            sprintf(temp, "%s%c", pwd, word[i]);
            GenerateAllPassword(temp, pos+1, size);
        }
    }else{
        printf("%s\n", pwd);
    }
}

void main(int argc, char  *argv[]){
    int tam_max = atoi(argv[1]);
    word = argv[2];

    for(int i=1; i<=tam_max; i++){
        GenerateAllPassword("", 0, i);
    }
}

