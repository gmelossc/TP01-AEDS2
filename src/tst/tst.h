/* TRABALHO PRÁTICO I:
*  GRUPO ^&|:
*             ÉLIDA EMELLY ANTUNES - 3012
*             GUILHERME CORRÊA MELOS - 3882
*             VINICIUS TOMÉ M. G. SILVA - 3874
*/

#ifndef __TST_H__
#define __TST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../stats/stats.h"

#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))

/*
Definição de um nó da trie TST como tNode

@param c: caractere do nó
@param left: apontador para o filho à esquerda
@param mid: apontador para o filho do meio
@param right: apontador para o filho à direita
@param end: indica se o nó é um fim de palavra ou não
*/

typedef struct t_node{
	char c;
	struct t_node *left, *mid, *right;
	bool end;
} tNode;

//Definição da trie TST: um ponteiro para tNode
typedef tNode* TST;

/*
Incializa a trie TST

@param tst: ponteiro para a trie TST
*/
void initTST(TST *tst);

/*
Adiciona de modo iterativo uma nova palavra na trie TST e executa testes de uso de memória, de tempo de execução e de comparação
(a função não fornece um resultado de inserção individual de palavras caso a palavra pertencer a um texto)

@param tst: ponteiro para a trie TST
@param s: palavra a ser adicionada
@param len: comprimento da palavra a ser adicionada
@param stats: ponteiro para "contador" utilizado nos testes
@text: booleano que indica se a palavra que está sendo inserida pertence a um texto ou não
*/
void addTST(TST *tst, char s[], int len, Stats *stats, bool text);

/*
Modulariza a função addTST para inserir um texto por arquivo na trie TST

@param tst: ponteiro para a trie TST
@param stats: ponteiro para "contador" utilizado nos testes
@param filename: string que representa o nome do arquivo de texto a ser inserido na trie TST
*/
void addtxtTST(TST *tst, Stats *stats, char filename[]);

/*
Procura de modo iterativo se a palavra está ou não inserida na trie TST, tal resultado é retornado como booleano;
realiza internamente testes de comparação e de tempo de execução.

@param tst: cópia da trie TST
@param s: palavra a ser procurada
*/
bool tstFind(TST tst, char s[]);

/*
Printa, recursivamente, todas as palavras da trie TST

@param tst: cópia da trie TST
*/
void tstPrint(TST tst);

/*
Retona um inteiro que representa quantas palavras existem na trie TST, recursivamente

@param tst: cópia da trie TST
*/
int tstCountWord(TST tst);

/*
Utiliza de uma DFS para contar a altura da trie TST, retornado como inteiro

@param tst: cópia da trie TST
*/
int tHeight(TST *tst);

/*
Desaloca, de modo recursivo, todo o conteúdo da trie TST

@param tst: Ponteiro para a trie TST
*/
void freeTST(TST *tst);
#endif
