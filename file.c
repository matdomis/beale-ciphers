#include "file.h"
#include <string.h>

void createArquivoDeChaves(FILE *ArquivoDeChaves_file, LETTER_t **keys, int keys_pos) {
    int i, j;
    for(i = 0 ; i < keys_pos ; i++) {
        fprintf(ArquivoDeChaves_file, "%c%s", keys[i]->key, ": ");
        for(j = 0 ; j < keys[i]->p_len ; j++) {
            fprintf(ArquivoDeChaves_file, "%d%c", (keys[i]->p)[j], ' ');
        }
        fprintf(ArquivoDeChaves_file, "%s", "\n");
    }
}