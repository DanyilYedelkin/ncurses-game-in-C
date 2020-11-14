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
    char alphabet[26];
    for(int i = 0; i < 26; i++){
        alphabet[i] = (char)(97 + i);
        if(i == 25){
            alphabet[i+1] = '\0';
        }
    }
    char *unknown;
  
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
}
void hangman(const char secret[]){
    char letters_guessed[27], alphabet[27] = "abcdefghijklmnopqrstuvwxyz", new_letter[30], guessed_word[30];
    int congratulation = 0, probel = 0, mistake_answer = 0, cuckold = 0, correct_answer = 0, mis = 0;    

    printf("Welcome to the game, Hangman!");
    printf("\n");
    printf("I am thinking of a word that is %ld letters long.", strlen(secret));
    printf("\n-------------\n");

    for(int attempt = 8; attempt != 0;){
        printf("You have %d guesses left.\n", attempt);
        printf("Available letters: %s\n", alphabet);
        printf("Please guess a letter: ");
        scanf("%s", new_letter);

        correct_answer = 0, mistake_answer = 0, cuckold = 0, mis = 0;

        for(int i = 0; i < strlen(new_letter); i++){
            new_letter[i] = tolower(new_letter[i]);
        }

        for(int i = 0; i < strlen(new_letter); i++)
        {
            if(new_letter[i] < 97){ 
                printf("Oops! '%c' is not a valid letter:", (char)new_letter[i]);
                for (int i=0; new_letter[i]; i++){ 
                    if (new_letter[i] < 123 && new_letter[i] > 96 && strchr(letters_guessed, new_letter[i]) == NULL){
                        letters_guessed[probel++] = new_letter[i];
                    }
                }
 
                get_guessed_word(secret, letters_guessed, guessed_word);
                get_available_letters(letters_guessed, alphabet);
                for (int i = 0; guessed_word[i]; i++){
                    printf("%2c", guessed_word[i]);
                } 
                printf("\n-------------\n");
                cuckold++;
                continue;

            } else if(new_letter[i] > 122){
                printf("Oops! '%c' is not a valid letter:", (char)new_letter[i]);
                for (int i = 0; new_letter[i]; i++){ 
                    if (new_letter[i] < 123 && new_letter[i] > 96 && strchr(letters_guessed, new_letter[i]) == NULL){
                        letters_guessed[probel++] = new_letter[i];
                    }
                }
 
                get_guessed_word(secret, letters_guessed, guessed_word);
                get_available_letters(letters_guessed, alphabet);
                for (int i = 0; guessed_word[i]; i++){
                    printf("%2c", guessed_word[i]);
                } 
                printf("\n-------------\n");
                cuckold++;
                continue;
            }
            if(strchr(letters_guessed, new_letter[i]) != NULL){
                mistake_answer++; 
                mis++;
            } else if(strchr(secret, new_letter[i]) != NULL){
                correct_answer++;  
            }
            mistake_answer++;
        }

        if(correct_answer == 0 && cuckold == 0 && mistake_answer == 1){
            printf("Oops! That letter is not in my word:");
            for(int i = 0; new_letter[i]; i++){  
                if (new_letter[i] < 123 && new_letter[i] > 96 && strchr(letters_guessed, new_letter[i]) == NULL){
                    letters_guessed[probel++] = new_letter[i];
                }
            }
 
            get_guessed_word(secret, letters_guessed, guessed_word);
            get_available_letters(letters_guessed, alphabet);
 
            for(int i=0; guessed_word[i]; i++){
                printf("%2c", guessed_word[i]);
            } 
            printf("\n-------------\n");
            attempt--;
        } else if(mistake_answer == 2 && mis == 1){
            printf("Oops! You've already guessed that letter:");
            for(int i = 0; new_letter[i]; i++){ 
                if(new_letter[i] < 123 && new_letter[i] > 96 && strchr(letters_guessed, new_letter[i]) == NULL){
                    letters_guessed[probel++] = new_letter[i];
                }
            }
 
            get_guessed_word(secret, letters_guessed, guessed_word);
            get_available_letters(letters_guessed, alphabet);
            for(int i = 0; guessed_word[i]; i++){
                printf("%2c", guessed_word[i]);
            }
            printf("\n-------------\n");
        } else if(correct_answer == 1 && cuckold == 0){
            printf("Good guess:");
            for(int i = 0; new_letter[i]; i++){  
                if (new_letter[i] < 123 && new_letter[i] > 96 && strchr(letters_guessed, new_letter[i]) == NULL){
                    letters_guessed[probel++] = new_letter[i];
                }
            }
 
            get_guessed_word(secret, letters_guessed, guessed_word);
            get_available_letters(letters_guessed, alphabet);
            for(int i = 0; guessed_word[i]; i++){
                printf("%2c", guessed_word[i]);
            }
            printf("\n-------------\n");
            if(is_word_guessed(secret, letters_guessed)){
                congratulation = 1;
            }
        }
        for(int i = 0; new_letter[i]; i++){  
            if (new_letter[i] < 123 && new_letter[i] > 96 && strchr(letters_guessed, new_letter[i]) == NULL){
                letters_guessed[probel++] = new_letter[i];
            }
        }
        if(is_word_guessed(secret, letters_guessed)){
            congratulation = 1;
        }
        if(congratulation > 0){
            printf("Congratulations, you won!\n");
            break;
        }
    }
    if(congratulation != 1){
        printf("Sorry, you ran out of guesses. The word was %s.\n", secret);
    }
}