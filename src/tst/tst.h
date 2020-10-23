#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#ifndef __TST_H__
#define __TST_H__


typedef struct t_node{
	char c;
	struct t_node *left, *mid, *right;
	bool end;
} tNode;

typedef tNode* TST;

void initTST(TST *tst); //incializa a trie TST
void addTST(TST *tst, char s[], int len); //adiciona uma nova palavra a TST
bool tstFind(TST tst, char s[]); // procura uma palavra na TST
void printTST(TST trie, char s[], int pos);//printa todo o conteúdo da TST
void freeTST(TST *tst); //remove todo o conteúdo da TST
#endif
