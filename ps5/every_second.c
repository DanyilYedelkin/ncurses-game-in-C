#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Wrong number of parameters.\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    
    if(fp == NULL){
        printf("Error opening file.\n");
        fclose(fp);
        return 1;
    }
    FILE *fs = fopen(argv[2], "w");
    
    if(fs == NULL){
        printf("Error opening file.\n"); 
        fclose(fs);
        return 1;
    }
    
    char input[1000];
    char between[1000];
    int input_length = 0;
    int between_length = 0;
    
    for(int i = 0; i < 1000; i++){
        input[i] = fgetc(fp);
        input_length++;
        if(input[i] == EOF){
            input[i] = '\0';
            break;
        }
    }

    for(int i = 0; i < input_length; i++){
        if(input[i] == 'S' && input[i+1] == 'T' && input[i+2] == 'A' && input[i+3] == 'R' && input[i+4] == 'T'){
            for(int j = i+6; j < input_length; j++){
                if(input[j] == 'S' && input[j+1] == 'T' && input[j+2] == 'O' && input[j+3] == 'P'){
                    between[between_length - 1] = '\0';
                    break;
                }
                between[between_length] = input[j];
                between_length++;
            }
        }
    }
    
    int i = 0;
    int value = 0;
    int k = 0;
    char output[1000];

    while(between[i] != '\0'){
        while(between[i] != ' '){
            if(between[i+1] != '\0'){
                i++;
                k++;
            } else{
                break;
            }
        }
        i++;
        k++;
        while(between[i] != ' '){
            if(between[i+1] != '\0'){
                output[value] = between[i];
                i++;
                k++;
                value++;
            } else{
                break;
            }
        }
        if(between[i+1] != '\0'){
            if(between[k] == ' '){
                k++;
                while(between[k] != ' '){
                    k++;
                }
                if(between[k] == '\0'){
                    output[value - 1] = '\0';
                    break;
                }
            }
            output[value] = between[i];
            i++;
            k++;
            value++;
        }
    }

    int j = 0;
    while(output[j] != '\0'){
        if(output[j] == ' '){
            if(output[j+1] != '\0'){
                fputc(output[j], fs);
            }
        } else{
            fputc(output[j], fs);
        }
        
        j++;
    }

    fclose(fp);
    fclose(fs);

    return 0;
}