#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void encode_char(const char character, bool bits[8]);
char decode_byte(const bool bits[8]);
void encode_string(const char string[], bool bytes[strlen(string)+1][8]);
void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]);
void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]);
void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]);

int main(){
    bool bits1[8];
    encode_char('A', bits1);
    for(int i = 0; i < 8; i++){
        printf("%d", bits1[i]);
    }
    printf("\n");
    bool bits2[8] = {0,1,0,0,0,0,0,1};
    printf("%c\n", decode_byte(bits2));
    printf("\n--------------\n");

    //===============================

    char* text = "Hello, how are you?";
    const int len = strlen(text);
    bool bytes1[len+1][8];
    encode_string(text, bytes1);
    for(int j = 0; j <= len; j++){
        printf("%c: ", text[j]);
        for(int i = 0; i < 8; i++){
            printf("%d", bytes1[j][i]);
        }
        printf("\n");
    }
    printf("-------------------\n");
    bool bytes2[7][8] = {
        {0,1,0,0,1,0,0,0},
        {0,1,1,0,0,1,0,1},
        {0,1,1,0,1,1,0,0},
        {0,1,1,0,1,1,0,0},
        {0,1,1,0,1,1,1,1},
        {0,0,1,0,0,0,0,1},
        {0,0,0,0,0,0,0,0}
    };
    char string[7];
    decode_bytes(7, bytes2, string);
    printf("%s\n", string);
    printf("\n-------------------\n");

    //==============================

    int length = 4+1, cols = 3, offset = 2;
    bool bytes11[4+1][8] = {
        {0,1,0,0,0,0,0,1},
        {0,1,1,0,1,0,0,0},
        {0,1,1,0,1,1,1,1},
        {0,1,1,0,1,0,1,0},
        {0,0,0,0,0,0,0,0}
    };
    bool blocks11[offset*8][cols];
    bytes_to_blocks(cols, offset, blocks11, length, bytes11);
    for(int j = 0; j < offset*8; j++){
        for(int i = 0; i < cols; i++){
            printf("%d ", (blocks11[j][i] == true) ? 1 : 0);
        }
        printf("\n");
        if(j % 8 == 7){
            printf("\n");
        }
    }

    printf("----------------\n");
    bool blocks22[2*8][3] = {
        {0,0,0},
        {1,1,1},
        {0,1,1},
        {0,0,0},
        {0,1,1},
        {0,0,1},
        {0,0,1},
        {1,0,1},
        {0,0,0},
        {1,0,0},
        {1,0,0},
        {0,0,0},
        {1,0,0},
        {0,0,0},
        {1,0,0},
        {0,0,0}
    };
    bool bytes22[length][8];
    blocks_to_bytes(3, 2, blocks22, length, bytes22);
    for(int j = 0; j < length; j++){
        for(int i = 0; i < 8; i++){
            printf("%d", bytes22[j][i]);
        }
        printf("\n");
    }

    return 0;
}

void encode_char(const char character, bool bits[8]){
    int value = character;
    bool back_bits[8];
    for(int i = 0; i < 8; i++){
        if(value % 2 == 0){
            back_bits[i] = false;
        } else{
            back_bits[i] = true;
        }
        value /= 2;
    }
    int j = 7;
    for(int i = 0; i < 8; i++){
        if(j >= 0){
            bits[i] = back_bits[j];
            j--;
        }
    }
}
char decode_byte(const bool bits[8]){
    int sum;
    int value = 128;
    for(int i = 0; i < 8; i++){
        sum += (value * bits[i]);
        value /= 2;
    }
    char symbol = sum + 1;
    return symbol;
}
void encode_string(const char string[], bool bytes[strlen(string)+1][8]){
    bool back_bytes[strlen(string)+1][8];
    char character;
    int value;
    for(int i = 0; i < (strlen(string) + 1); i++){
        character = string[i];
        value = character;
        for(int j = 0; j < 8; j++){
            if(value % 2 == 0){
                back_bytes[i][j] = false;
            } else{
                back_bytes[i][j] = true;
            }
            value /= 2;
        }
    }
    
    bytes[strlen(string)+1][8] = '\0';
    int m = 7;
    for(int i = 0; i < (strlen(string) +1 ); i++){
        m = 7;
        for(int j = 0; j < 8; j++){
            if(m >= 0){
                bytes[i][j] = back_bytes[i][m];
                m--;
            }
        }
    }
}
void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]){
    int sum;
    int value = 128;
    for(int i = 0; i < rows; i++){
        sum = 0;
        value = 128;
        for(int j = 0; j < 8; j++){
            sum += (value * bytes[i][j]);
            value /= 2;
        }
        string[i] = sum;
    }
}
void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]){
    for(int i = 0; i < offset*8; i++){
        for(int j = 0; j < cols; j++){
            blocks[i][j] = bytes[j][i];
        }
    }
    if(offset > 1){
        for(int i = offset*4; i < offset*8; i++){
            for(int j = 0; j < cols; j++){
                blocks[i][j] = bytes[cols - 1 + j][i];
            }
        }
    }
}
void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]){
    for(int i = 0; i < offset*8; i++){
        for(int j = 0; j < cols; j++){
            bytes[j][i] = blocks[i][j];
        }
    }
    if(offset > 1){
        for(int i = offset*4; i < offset*8; i++){
            for(int j = 0; j < cols; j++){
                bytes[cols - 1 + j][i] = blocks[i][j];
            }
        }
    }
}