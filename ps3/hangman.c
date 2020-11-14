#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "hangman.h"

int get_word(char secret[]){
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);

    return 0;
}
int is_word_guessed(const char secret[], const char letters_guessed[])
{
    int letters = 0;

    for(int i = 0; i < strlen(secret); i++){
        for(int j = 0; j < strlen(letters_guessed); j++){
            if(letters_guessed[j] == secret[i]){
                letters++;
            }
        }
    }
    if (letters == strlen(secret)){
        return 1;
    } else{
        return 0;
    }
}
void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[])
{
    for(int i = 0; i < strlen(secret); i++){
        guessed_word[i] = '_';
    }
    for(int i = 0; i < strlen(secret); i++){
        for(int j = 0; j < strlen(letters_guessed); j++){
            if(letters_guessed[j] == secret[i]){
                guessed_word[i] = secret[i];
                break;
            } else{
                guessed_word[i] = '_';
            }
        }
    }
    guessed_word[strlen(secret)] = '\0';
}
void get_available_letters(const char letters_guessed[], char available_letters[]){
    /*char alphabet[26];
    for(int i = 0; i < 26; i++){
        alphabet[i] = (char)(97 + i);
        if(i == 25){
            alphabet[i+1] = '\0';
        }
    }*/
    int endline_of_letters = 27;

    for (int i = 0; i < endline_of_letters; i++)
    {
        if (strchr(letters_guessed, available_letters[i]) != NULL)  //try to find our "letters_guessed"
        {
            for (int j = i + 1; j < endline_of_letters; j++){
                available_letters[j - 1] = available_letters[j];
            }
        }
    }
    available_letters[27] = '\0';
}
void hangman(const char secret[]){
}