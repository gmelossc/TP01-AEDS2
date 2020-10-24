#ifndef __TST_H__
#define __TST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../test/test.h"

#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))

typedef struct t_node{
	char c;
	struct t_node *left, *mid, *right;
	bool end;
} tNode;

typedef tNode* TST;

void initTST(TST *tst); //incializa a trie TST
void addTST(TST *tst, char s[], int len, Test *teste, bool text); //adiciona uma nova palavra a TST
void addtxtTST(TST *tst, Test *teste);
bool tstFind(TST tst, char s[]); // procura uma palavra na TST
void tstPrint(TST tst);//printa todo o conteúdo da TST
int tstCountWord(TST tst); //conta quantas palavras foram inseridas na árvore
int tHeight(TST *tst); // retorna a profundidade da árvore
void freeTST(TST *tst); //remove todo o conteúdo da TST
#endif
