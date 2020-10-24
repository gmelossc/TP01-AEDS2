#include "../word/word.h"
#include <stdbool.h>

#ifndef __PATRICIA_H__
#define __PATRICIA_H__


#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))
#define EXT -1

typedef struct p_node{
	Word *word;
	int pos;
	char c;
	struct p_node *left, *right;
} pNode;

typedef pNode * PAT;

void initPat(PAT *pat);
void addPat(PAT *pat, Word word);
void addtxtPat(PAT *pat);
void patPrint(PAT pat);
bool patFind(PAT pat, Word word);
int patCountWord(PAT pat);
int height(PAT pat);
void freePat(PAT *pat);

#endif
