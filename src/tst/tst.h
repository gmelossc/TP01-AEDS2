#ifndef __TST_H__
#define __TST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
	char c;
	struct node *left, *mid, *right;
	bool end;
} Node;

typedef Node* TST;

void initTST(TST *tst); //incializa a trie TST
void addTST(TST *tst, char s[], int len); //adiciona uma nova palavra a TST
void freeTST(TST *tst); //remove todo o conteúdo da TST

#endif
