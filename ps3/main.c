#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hangman.h"
#include "hangman.c"
#include <time.h>
#include <string.h>
#include <ctype.h>

int main(){
    srand(time(NULL));
    char secret[15];
    get_word(secret);
    hangman(secret);

    return 0;
}