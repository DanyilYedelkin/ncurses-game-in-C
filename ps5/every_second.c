#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Wrong number of parameters.\n");  //printf("");
        return 1;  //exit (0);
    }
    FILE *fp = fopen(argv[1], "r");
    
    if(fp == NULL){
        printf("Error opening file.\n");  //printf("");
        return 1;  //exit(0);
    }
    FILE *fs = fopen(argv[2], "w");
    
    if(fs == NULL){
        printf("Error opening file.\n");  //printf("");
        return 1;  //exit(0);
    }

    char ch = fgetc(fp);
    while(ch != EOF){
        if(ch == 'S'){
            ch = fgetc(fp);
            if(ch == 'T'){
                ch = fgetc(fp);
                if(ch == 'A'){
                    ch = fgetc(fp);
                    if(ch == 'R'){
                        ch = fgetc(fp);
                        if(ch == 'T'){
                            ch = fgetc(fp);
                            char chr = ch;
                            char r = ch;
                            while(ch != EOF){                                
                                ch = fgetc(fp);
                                
                                if(ch == 'S'){
                                    ch = fgetc(fp);
                                    if(ch == 'T'){
                                        ch = fgetc(fp);
                                        if(ch == 'O'){
                                            ch = fgetc(fp);
                                            if(ch == 'P'){
                                                break;
                                            }
                                        }
                                    }
                                }
                                if(ch == ' '){
                                    ch = fgetc(fp);
                                    chr = ch;
                                    r = ch;
                                    fputc(chr, fs);

                                    while(ch != ' '){
                                        ch = fgetc(fp);
                                        chr = ch;
                                        r = ch;
                                        if(r == ' '){
                                            r = fgetc(fp);
                                            if(r == 'S'){
                                                break;
                                            }
                                        }
                                        fputc(chr, fs);
                                    }
                                }
                            }
                        } 
                    }
                }
            }
        }
        ch = fgetc(fp);
    }

    fclose(fp);
    fclose(fs);

    return 0;
}