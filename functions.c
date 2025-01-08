#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "functions.h"


// Separate the text data and build the array of structs containing the position of each character inside the text
void InsertCharacterPos(char c, int text_pos, LETTER_t **keys, int *keys_pos) {
    int i, j;    
    for(i = 0 ; i < *keys_pos ; i++) {
        if (keys[i]->key == c) {

            for(j = 0 ; j < keys[i]->p_len ; j++);

            // Realloc
            if(keys[i]->p_len > BUFFSIZE) {
                keys[i]->p = realloc(keys[i]->p, 2 * BUFFSIZE * sizeof(int));
                if (keys[i]->p == NULL) {
                    perror("Error reallocating memory!");
                    exit(1);
                }
            }

            (keys[i]->p)[j] = text_pos;

            keys[i]->p_len++;
            break;
        }
    }

    if ( (*keys_pos == 0) || ( (i == *keys_pos) && (keys[i-1]->key != c)) ) {
        keys[*keys_pos] = malloc(sizeof(LETTER_t));
        keys[*keys_pos]->key = c;
        keys[*keys_pos]->p_len = 1;
        keys[*keys_pos]->p = malloc(sizeof(int) * BUFFSIZE);
        if (keys[*keys_pos]->p == NULL) {
            perror("Error allocating memory!");
            exit(1);
        }

        (keys[*keys_pos]->p)[0] = text_pos;
        (*keys_pos)++;
    }
}

// Reverse a string
char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

// Transform an integer to string
void transformToString(char *buffer, int n) {
    int i = 0;

    if (n == 0) {
        buffer[i++] = '0';
    }

    else {
        while(n > 0) {
            buffer[i++] = '0' + n%10;
            n /= 10;
        }
    }

    buffer[i] = '\0';
    strrev(buffer);
}


void encodeMensagemOriginal(FILE *fp, FILE *mensagemOriginal, LETTER_t **keys, int keys_pos) {
    int RandomNumber, predicted_key, j;
    char buffer[10];
    char c;

    while(!feof(mensagemOriginal)) {
       
        c = tolower(fgetc(mensagemOriginal));
        strcpy(buffer, "");

        
        if (c == ' ') {
            fprintf(fp, "%s", "-1 ");
        }
        else {
            for(j = 0 ; j < keys_pos ; j++) 
                if (c == keys[j]->key) {
                    RandomNumber = rand() % keys[j]->p_len;
                    predicted_key = (keys[j]->p)[RandomNumber];
                    transformToString(buffer, predicted_key);
                    fprintf(fp, "%s%s", buffer, " ");
            
                    break;
                }
                

            // Don't found the char in the keys data
            if (j == keys_pos) {
                fprintf(fp, "%s", "? ");
            }
        }
    }
}


