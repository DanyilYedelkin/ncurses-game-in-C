#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Wrong number of parameters.\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    
    if(fp == NULL){
        printf("Error opening file.\n");
        fclose(fp);
        return 1;
    }

    int counter = 48;
    char ch = fgetc(fp);
    while(ch != EOF){
        if(ch == 'a' || ch == 'A'){
            ch = fgetc(fp);
            if(ch == 'n' || ch == 'N'){
                ch = fgetc(fp);
                if(ch == 'a' || ch == 'A'){
                    ch = fgetc(fp);
                    if(ch == 'n' || ch == 'N'){
                        ch = fgetc(fp);
                        if(ch == 'a' || ch == 'A'){
                            ch = fgetc(fp);
                            if(ch == 's' || ch == 'S'){
                                counter++;
                            }
                        } 
                    }
                }
            }
        }
        ch = fgetc(fp);
    }
    fclose(fp);
    
    char zero = 48;
    char one = 49;
    char two = 50;
    char three = 51;
    char four = 52;
    char five = 53;
    char six = 54;
    char seven = 55;
    char eight = 56;
    char nine = 57;
    
    fp = fopen(argv[1], "w");
    if(counter < 58){
        fputc(counter, fp);
    } else{
        if(counter == 58){
            fputc(one, fp);
            fputc(zero, fp);
        }
        if(counter == 59){
            fputc(one, fp);
            fputc(one, fp);
        }
        if(counter == 60){
            fputc(one, fp);
            fputc(two, fp);
        }
        if(counter == 61){
            fputc(one, fp);
            fputc(three, fp);
        }
        if(counter == 62){
            fputc(one, fp);
            fputc(four, fp);
        }
        if(counter == 63){
            fputc(one, fp);
            fputc(five, fp);
        }
        if(counter == 64){
            fputc(one, fp);
            fputc(six, fp);
        }
        if(counter == 65){
            fputc(one, fp);
            fputc(seven, fp);
        }
        if(counter == 66){
            fputc(one, fp);
            fputc(eight, fp);
        }
        if(counter == 67){
            fputc(one, fp);
            fputc(nine, fp);
        }
    }

    fclose(fp);

    return 0;
}