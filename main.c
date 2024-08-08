#include <stdio.h>
#include <string.h>

void printAllMeanings(FILE* filePointer){
    char buffer[256];
    while(fgets(buffer, sizeof(buffer), filePointer) != NULL){
        printf("%s", buffer);
    }
}

void getMeaning(char *inputWord, FILE* filePointer){
    char buffer[256];
    while(fgets(buffer, sizeof(buffer), filePointer) != NULL){
        char *word = strtok(buffer, "-");
        char *meaning = strtok(NULL, "-");

        if(strcmp(word, inputWord) == 0){
            printf(meaning);
            break;
        }
    }
}

int AddWordToDictioanry(char *word, char *meaning, FILE* filePointer){
    
}

int DeleteWordFromDictionary(char *word, FILE *filePointer){

}

int UpdateMeaningOfAWord(char *word, FILE* filePointer){

}

int main(int agrc, char *argv[]){
    FILE *filePointer;

    //opens the file
    filePointer = fopen("dict.txt", "r");
    if(filePointer == NULL){
        printf("Error: Could not open file\n");
        return 1;
    }

    getMeaning("hi", filePointer);
    //close the file
    fclose(filePointer);

    return 0;
}