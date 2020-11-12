#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hangman.h"
#include <string.h>
#include <ctype.h>
#include <time.h>

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
int is_word_guessed(const char secret[], const char letters_guessed[]){
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
void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]){
    for(int i = 0; i < strlen(secret); i++){
        for(int j = 0; j < strlen(letters_guessed); j++){
            if(letters_guessed[j] == secret[i]){
                guessed_word[i] = letters_guessed[j];
                break;
            } else{
                guessed_word[i] = '_';
            }
        }
        if(i == (strlen(secret) + 1)){
            guessed_word[i] = '\0';
            break;
        }
    }
    guessed_word[strlen(secret) + 1] = '\0';
    printf("%s", guessed_word);
}
void get_available_letters(const char letters_guessed[], char available_letters[]){
    char alphabet[26];
    for(int i = 0; i < 26; i++){
        alphabet[i] = (char)(97 + i);
        if(i == 25){
            alphabet[i+1] = '\0';
        }
    }
    /*for(int i = 0; i < strlen(alphabet); i++){
        for(int j = 0; j < strlen(letters_guessed); j++){
            if(letters_guessed[j] == alphabet[i]){
                alphabet[i] = '_';
                break;
            }
        }
        available_letters[i] = alphabet[i];
    }
    available_letters[strlen(alphabet) + 1] = '\0';
    printf("%s", available_letters);*/
    int value = 0, number = 0;

    for(int i = 0; i < strlen(alphabet); i++){
        for(int j = 0; j < strlen(letters_guessed); j++){
            if(letters_guessed[j] == alphabet[i]){
                value++;
                number++;
            }
        }
        available_letters[i] = alphabet[value];
        value++;
    }
    available_letters[strlen(alphabet) - number] = '\0';
    printf("%s", available_letters);
}

void hangman(const char secret[]){
    char alphabet[26];
    for(int i = 0; i < 26; i++){
        alphabet[i] = (char)(97 + i);
        if(i == 25){
            alphabet[i+1] = '\0';
        }
    }
    char letter;
    char letters_guessed[strlen(alphabet)];
    char result[30];
    int value = 0;
  
    printf("Welcome to the game, Hangman!\n");
    printf("I am thinking of a word that is %ld letters long.", strlen(secret));
    printf("\n-----------------------\n");
    
    for(int attempt = 8; attempt != 0;){
        printf("\n");
        printf("You have %d guesses left.\n", attempt);
        printf("Available letters: ");
        get_available_letters(letters_guessed, alphabet);
        printf("\nPlease guess a letter: ");
        scanf("%c", &letter); 

        while(getchar() != '\n')
        ; 

        letter = tolower(letter);

        if (!strchr(alphabet, letter)){
            printf("\n");
            printf("Oops! You've already guessed that letter: ");
            get_guessed_word(secret, letters_guessed, result); 
            //printf("\n-----------------------\n");
            printf("\n");
            continue;
        }

        letters_guessed[value++] = letter; 
    
        if (strchr(secret, letter)){
            printf("\n");
            printf("Goog quess: ");
            get_guessed_word(secret, letters_guessed, result);
            printf("\n"); 
            
            /*if(is_word_guessed(unknow_word, result) == 0){
                printf("\n-----------------------\n");
                printf("\n");
                printf("Congratulations, you won!\n"); 
                break;
            } */
            if (strcmp(secret, result) == 0) {
                //printf("\n-----------------------\n");
                printf("\n");
                printf("Congratulations, you won!\n"); 
                printf("\n"); 
                break; 
            }
        } else{
            printf("\n");
            printf("Oops! That letter is not in my word: ");
            get_guessed_word(secret, letters_guessed, result);
            printf("\n"); 
            attempt--; 
        }
        
        if (attempt == 0) {
            //printf("\n-----------------------\n");
            printf("\n");
            printf("Sorry, you ran out of guesses. The word  was %s.\n", secret);
            break; 
        }
    }
}