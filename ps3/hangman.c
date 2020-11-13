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
    /*guessed_word[strlen(secret)+1] = '\0';
    for(int i = 0; i < strlen(secret); i++){
        if(letters_guessed == NULL){
            guessed_word[i] = '_';
        }
        for(int j = 0; j < strlen(letters_guessed); j++){
            if(letters_guessed[j] == secret[i]){
                guessed_word[i] = secret[i];
            } else if(letters_guessed[j] == 0x0A){
                guessed_word[i] = '_';
            } else if(letters_guessed == NULL){
                guessed_word[i] = '_';
            } else{
                guessed_word[i] = '_';
            }
        }
    }
    printf("%s", guessed_word);*/

    char *unknown;
    //guessed_word[strlen(secret)] = '\0';
            unknown = (char *) malloc(15); 
            int value = 0, i;
            for(i = 1; i < strlen(secret); i++){
                    unknown = strchr(letters_guessed, secret[value++]);
                    if(unknown != NULL){
                        guessed_word[i-1] = *unknown;
                    } else{
                        guessed_word[i-1] = '_';
                    }
            }
            guessed_word[strlen(secret)] = '\0';
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
    char *unknown;
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
    unknown = (char*)malloc(15);
    int value = 0;
    for(int i = 0; i < strlen(alphabet); i++){
        unknown = strchr(letters_guessed, alphabet[i]);

        if(unknown == NULL){
            available_letters[value++] = alphabet[i];
        } else if(unknown != NULL){
            continue;
        }
    }
    available_letters[value] = '\0';
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
    
    char secrets[30];
    for(int m = 1; m < (strlen(secret)*2); m++){
        secrets[m-1] = m % 2 == 0 ? ' ' : secret[value++];
    }
    secrets[(strlen(secrets)*2)-1] = '\0';
    value = 0;

    for(int attempt = 8; attempt != 0;){
        printf("\n-------------\n");
        printf("You have %d guesses left.\n", attempt);
        printf("Available letters: ");
        get_available_letters(letters_guessed, alphabet);
        printf("\nPlease guess a letter: ");
        scanf("%c", &letter); 
        if(letter == 0x0A){
            printf("Oops! '%c' is not a valid letter: ", letter);
            int value = 0, i;
            char *unknown;

            unknown = (char *) malloc(15);
            for(i = 1; i < (strlen(secret)*2); i++){
                if (i % 2 != 0) {
                    unknown = strchr(letters_guessed, secret[value++]);
                    if(unknown != NULL){
                        result[i-1] = *unknown;
                    } else{
                        result[i-1] = '_';
                    }
                } else{
                    result[i-1] = ' ';
                }
            }
            result[(strlen(secret)*2)-1] = '\0';
            printf("%s", result);
            continue;
        }

        while(getchar() != '\n')
        ; 
        letter = tolower(letter);

        if (!strchr(alphabet, letter)){
            if(letter < 97){
                printf("Oops! '%c' is not a valid letter: ", letter);
                //get_guessed_word(secret, letters_guessed, result);
                char *unknown;

                unknown = (char *) malloc(15);

                int value = 0, i;
                for(i = 1; i < (strlen(secret)*2); i++){
                    if (i % 2 != 0) {
                        unknown = strchr(letters_guessed, secret[value++]);
                        if(unknown != NULL){
                            result[i-1] = *unknown;
                        } else{
                            result[i-1] = '_';
                        }
                    } else{
                        result[i-1] = ' ';
                    }
                }
                result[(strlen(secret)*2)-1] = '\0';
                printf("%s", result);

                continue;
            }
            if(letter > 122){
                printf("Oops! '%c' is not a valid letter: ", letter);
                //get_guessed_word(secret, letters_guessed, result);
                char *unknown;

                unknown = (char *) malloc(15); 

                int value = 0, i;
                for(i = 1; i < (strlen(secret)*2); i++){
                    if (i % 2 != 0) {
                        unknown = strchr(letters_guessed, secret[value++]);
                        if(unknown != NULL){
                            result[i-1] = *unknown;
                        } else{
                            result[i-1] = '_';
                        }
                    } else{
                        result[i-1] = ' ';
                    }
                }
                result[(strlen(secret)*2)-1] = '\0';
                printf("%s", result);

                continue;
            }
            printf("Oops! You've already guessed that letter: ");
            ///get_guessed_word(secret, letters_guessed, result); 
            char *unknown;

            unknown = (char *) malloc(15); 

            int value = 0, i;
            for(i = 1; i < (strlen(secret)*2); i++){
                if (i % 2 != 0) {
                    unknown = strchr(letters_guessed, secret[value++]);
                    if(unknown != NULL){
                        result[i-1] = *unknown;
                    } else{
                        result[i-1] = '_';
                    }
                } else{
                    result[i-1] = ' ';
                }
            }
            result[(strlen(secret)*2)-1] = '\0';
            printf("%s", result);

            continue;
        }

        letters_guessed[value++] = letter; 
    
        if (strchr(secret, letter)){
            printf("Good guess: ");
            //get_guessed_word(secret, letters_guessed, result);
            char *unknown;
            unknown = (char *) malloc(15); 
            int value = 0, i;
            for(i = 1; i < (strlen(secret)*2); i++){
                if (i % 2 != 0) {
                    unknown = strchr(letters_guessed, secret[value++]);
                    if(unknown != NULL){
                        result[i-1] = *unknown;
                    } else{
                        result[i-1] = '_';
                    }
                } else{
                    result[i-1] = ' ';
                }
            }
            result[(strlen(secret)*2)-1] = '\0';
            printf("%s", result);
            if (strcmp(secrets, result) == 0) {
                printf("\n-------------\n");
                printf("Congratulations, you won!\n");  
                break; 
            }
            /*if(is_word_guessed(unknow_word, result) == 0){
                printf("\n-----------------------\n");
                printf("\n");
                printf("Congratulations, you won!\n"); 
                break;
            } */
        } else{
            printf("Oops! That letter is not in my word: ");
            //get_guessed_word(secret, letters_guessed, result);
            int value = 0, i;
            char *unknown;
            unknown = (char *) malloc(15); 
            for(i = 1; i < (strlen(secret)*2); i++){
                if (i % 2 != 0) {
                    unknown = strchr(letters_guessed, secret[value++]);
                    if(unknown != NULL){
                        result[i-1] = *unknown;
                    } else{
                        result[i-1] = '_';
                    }
                } else{
                    result[i-1] = ' ';
                }
            }
            result[(strlen(secret)*2)-1] = '\0';
            printf("%s", result);
            
            attempt--; 
        }
        if (strcmp(secrets, result) == 0) {
            printf("\n-------------\n");
            printf("Congratulations, you won!\n");  
            break; 
        }
        if (attempt == 0) {
            printf("\n-------------\n");
            printf("Sorry, you ran out of guesses. The word was %s.\n", secret);
            break; 
        }
    }
}