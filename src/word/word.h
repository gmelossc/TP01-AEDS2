/* TRABALHO PRÁTICO I:
*  GRUPO ^&|:
*             ÉLIDA EMELLY ANTUNES - 3012
*             GUILHERME CORRÊA MELOS - 3882
*             VINICIUS TOMÉ M. G. SILVA - 3874
*/

#ifndef __WORD_H__
#define __WORD_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct word{
    char *str;
    int len;
} Word;


void initWord(Word **word, char str[]);
void allocWord(Word **word);
void freeWord(Word **word);

#endif
