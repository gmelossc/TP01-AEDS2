#ifndef __PATRICIA_H__
#define __PATRICIA_H__

#include "../word/word.h"
#include <stdbool.h>
#include "../test/test.h"

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
void addPat(PAT *pat, Word word, Test *teste, bool text);
void addtxtPat(PAT *pat, Test *teste);
void patPrint(PAT pat);
bool patFind(PAT pat, Word word);
int patCountWord(PAT pat);
int pHeight(PAT *pat);
void freePat(PAT *pat);

#endif
