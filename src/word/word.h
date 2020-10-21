#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef __WORD_H__
#define __WORD_H__

typedef struct word{
    char *str;
    int len;
} Word;


void initWord(Word **word, char str[]);
void allocWord(Word **word);
void freeWord(Word **word);

#endif
