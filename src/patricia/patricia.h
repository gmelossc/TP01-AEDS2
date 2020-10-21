#ifndef __PATRICIA_H__
#define __PATRICIA_H__

#include "../word/word.h"
#include <stdbool.h>

#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))
#define EXT -1

typedef struct node{
	Word *word;
	int pos;
	char c;
	struct node *left, *right;
} Node;

typedef Node * PAT;


void initPat(PAT *pat);
void addPat(PAT *pat, Word word);
void patriciaPrintWords(PAT pat);
int height(PAT pat);

#endif
