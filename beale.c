#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>
#include <getopt.h>
#include "functions.h"
#include "file.h"

void file_fail() { perror("Error opening the file!"); exit(1); }

int main(int argc, char **argv) {
    setlocale(LC_ALL, "");  // UTF-8
    srand(time(NULL));  // Random() functions

    FILE *TEXT_file;
    FILE *ArquivoDeChaves_file;
    FILE *mensagemOriginal_file;
    FILE *mensagemCodificada_file;

    int option;
    int eflag = 0;
    int dflag = 0;
    while ((option = getopt(argc, argv, "edb:m:o:c:i:")) != -1) {
        switch(option) {
            case 'e':
                eflag = 1;
                break;
            case 'd':
                dflag = 1;
                break;
            case 'b':
                TEXT_file = fopen(optarg, "r");
                if (TEXT_file == NULL) file_fail();
                break;
            case 'm':
                mensagemOriginal_file = fopen(optarg, "r");
                if (mensagemOriginal_file == NULL) file_fail();
                break;
            case 'o':
                mensagemCodificada_file = fopen(optarg, "w");
                if (mensagemCodificada_file == NULL) file_fail();
                break;
            case 'c':
                ArquivoDeChaves_file = fopen(optarg, "w");
                if (!ArquivoDeChaves_file) file_fail();
                break;
            case 'i':
                printf("i is enabled\n");
                break;
            
            default:
                break;
            
        }
    }

    // Check encoding or decoding command line arguments
    if (dflag == 1) {
        printf("Infelizmente a opção de decodificação não foi desenvolvida nesta versão do programa. Tente a codificação! :)\n");
        exit(1);
    }
    
    if (eflag == 0 && dflag == 0) {
        printf("You need to specify at least one command argument for encoding or decoding (-e or -d) for the program to work.\n");
        exit(1);
    }
    else if (eflag == 1 && dflag == 1) {
            printf("You cannot decode and encode at the same time, choose only one option (-e or -d)\n");
            exit(1);
    }
    
    LETTER_t **keys;
    keys = malloc(sizeof(LETTER_t *) * BUFFSIZE);
    if (keys == NULL) { perror("Error allocating memory!"); exit(1); }
    int keys_pos = 0;

    char c;
    int text_pos = 0;
    while(!feof(TEXT_file)) {
        char word[BUFFSIZE];
        fscanf(TEXT_file, "%s", word);
        c = tolower(word[0]);

        InsertCharacterPos(c, text_pos, keys, &keys_pos);

        text_pos++;
    }

    // Create ArquivoDeChaves file
    createArquivoDeChaves(ArquivoDeChaves_file, keys, keys_pos);

    // Encode original message stored in file "mensagemOriginal_file" and outputs to "mensagemCodificada_file"
    encodeMensagemOriginal(mensagemCodificada_file, mensagemOriginal_file, keys, keys_pos);

    // Free memory and close files
    for(int i = 0 ; i < keys_pos ; i++) { free(keys[i]); }
    free(keys);
    fclose(mensagemCodificada_file);
    fclose(mensagemOriginal_file);
    fclose(ArquivoDeChaves_file);
    fclose(TEXT_file);
    return 0;
}