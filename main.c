#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *GetWordFromUserInput()
{
    printf("Enter the word: ");
    char *word = malloc(20);
    gets(word);

    return word;
}

char *GetMeaningFromUserInput()
{
    printf("Enter new meaning: ");
    char *meaning = malloc(20);
    gets(meaning);

    return meaning;
}

char *findWord(char *buffer)
{
    char *word = malloc(20);
    int i = 0;
    while (buffer[i] != '-')
    {
        word[i] = buffer[i];
        i++;
    }
    word[i] = '\0';
    return word;
}

char *findMeaning(char *buffer)
{
    char *meaning = malloc(20);
    int i = 0;
    while (buffer[i] != '-')
    {
        i++;
    }
    i++;
    int j = i;
    while (buffer[i] != '\n')
    {
        meaning[i - j] = buffer[i];
        i++;
    }
    meaning[i - j] = '\0';
    return meaning;
}

void AddToDictioanry(char *fileName)
{
    FILE *file = fopen(fileName, "a+");

    char *sentence = GetWordFromUserInput();
    strcat(sentence, "-");
    char *meaning = GetMeaningFromUserInput();
    strcat(sentence, meaning);

    fprintf(file, "%s\n", sentence);

    printf("Word and its Meaning saved");
}

void printAllMeanings(FILE *filePointer)
{
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), filePointer) != NULL)
    {
        printf("%s", buffer);
    }
}

void getMeaning(char *fileName)
{
    FILE *filePointer = fopen(fileName, "r");
    char *inputWord = GetWordFromUserInput();

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), filePointer) != NULL)
    {
        char *word = strtok(buffer, "-");
        char *meaning = strtok(NULL, "-");

        if (strcmp(word, inputWord) == 0)
        {
            printf(meaning);
            break;
        }
    }
}

void UpdateMeaningOfAWord(char *fileName)
{
    FILE *file = fopen(fileName, "r");

    char *word = GetWordFromUserInput();

    FILE *tempFile = fopen("tempFile.txt", "a+");
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        char *wordInFile = findWord(buffer);
        char *meaning = findMeaning(buffer);
        if (strcmp(word, wordInFile) == 0)
        {
            meaning = GetMeaningFromUserInput();
        }
        strcat(wordInFile, "-");
        strcat(wordInFile, meaning);
        fprintf(tempFile, "%s\n", wordInFile);
    }

    fclose(file);
    fclose(tempFile);

    remove(fileName);
    rename("tempFile.txt", fileName);

    return;
}

void DeleteWordFromDictionary(char *fileName)
{
    FILE *file = fopen(fileName, "r");

    char *word = GetWordFromUserInput();

    FILE *tempFile = fopen("tempFile.txt", "a+");
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        char *wordInFile = findWord(buffer);
        char *meaning = findMeaning(buffer);
        if (strcmp(word, wordInFile) != 0)
        {
            strcat(wordInFile, "-");
            strcat(wordInFile, meaning);
            fprintf(tempFile, "%s\n", wordInFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(fileName);
    rename("tempFile.txt", fileName);

    return;
}

int main(int agrc, char *argv[])
{

    char *fileName = "dict.txt";

    int userInput;
    while (1)
    {
        printf("Enter 1 to read a meaning of word: \n");
        printf("Enter 2 to add word and its meaning: \n");
        printf("Enter 3 to update a meaning of word: \n");
        printf("Enter 4 to delete a meaning of word: \n");
        printf("Enter CTRL C to exit: \n");
        scanf("%d", &userInput);
        switch (userInput)
        {
        case 1:
            getMeaning(fileName);
            break;
        case 2:
            AddToDictioanry(fileName);
        case 3:
            UpdateMeaningOfAWord(fileName);
        case 4:
            DeleteWordFromDictionary(fileName);
        default:
            break;
        }
    }
    return 0;
}