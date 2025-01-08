#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define BUFFSIZE 1024

typedef struct LETTER_t {
    char key;
    int p_len;
    int *p;
    
} LETTER_t;


void InsertCharacterPos(char, int, LETTER_t **, int *);
void transformToString(char *, int);
void encodeMensagemOriginal(FILE *, FILE *, LETTER_t **, int);

#endif