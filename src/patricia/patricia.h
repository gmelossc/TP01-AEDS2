/* TRABALHO PRÁTICO I:
*  GRUPO ^&|:
*             ÉLIDA EMELLY ANTUNES - 3012
*             GUILHERME CORRÊA MELOS - 3882
*             VINICIUS TOMÉ M. G. SILVA - 3874
*/

#ifndef __PATRICIA_H__
#define __PATRICIA_H__

#include "../word/word.h"
#include <stdbool.h>
#include "../stats/stats.h"

#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))
#define EXT -1

/* Definição de um nó da árvore PATRICIA como pNode, implementação adaptada do livro Algorithms in C, do professor Robert Sedgewick

@param word: Ponteiro para uma palavra no nó; não será alocado quando o nó for interno e será alocado quando o nó for externo
@param pos: posição de comparação quando o nó for interno; EXT quando o nó for externo
@param c: caractere de comparação quando o nó for interno, '\0' quando o nó for externo
@param left: ponteiro para o filho à esquerda
@param right: ponteiro para o filho à direita
*/
typedef struct p_node{
	Word *word;
	int pos;
	char c;
	struct p_node *left, *right;
} pNode;

// Definição da árvore PATRICIA: um ponteiro para pNode
typedef pNode * PAT;

/*
Inicializa a árvore PATRICIA

@param pat: Ponteiro para a árvore PATRICIA
*/
void initPat(PAT *pat);

/*
Adiciona de modo iterativo uma palavra à árvore PATRICIA e executa os testes de comparação, memória e tempo de execução

@param pat: Ponteiro para a árvore patricia
@param word: Palavra a ser inserida na árvore
@param stats: ponteiro para o "contador" do número de comparações e memória em bytes
@param text: boolean se a palavra que está sendo inserida faz parte de um texto ou não
*/
void addPat(PAT *pat, Word word, Stats *stats, bool text);

/*
Adiciona um texto por arquivo à árvore PATRICIA, modulariza a função addPat e executa testes de comparação, memória e tempo de execução

@param pat: Ponteiro para a árvore PATRICIA
@param stats: ponteiro para o "contador" do número de comparações e memória em bytes
@param filename: string que representa o nome do arquivo de texto a ser inserido na árvore PATRICIA
*/
void addtxtPat(PAT *pat, Stats *stats, char filename[]);

/*
Printa, recursivamente, todas as palavras da árvore PATRICIA

@param pat: cópia da árvore PATRICIA
*/
void patPrint(PAT pat);

/*
Procura de maneira iterativa se a palavra está ou não inserida na árvore PATRICIA, tal resultado é retornado como booleano;
realiza internamente testes de comparação e de tempo de execução.

@param pat: cópia da árvore PATRICIA
@param word: cópia da palavra a ser procurada
*/
bool patFind(PAT pat, Word word);

/*
Retona um inteiro que representa quantas palavras existem na árvore PATRICIA, recursivamente (também serve para contar quantos nós são externos)

@param pat: cópia da árvore PATRICIA
*/
int patCountWord(PAT pat);

/*
Retona um inteiro que representa quantos nós internos existem na árvore PATRICIA, recursivamente

@param pat: cópia da árvore PATRICIA
*/
int patCountInternals(PAT pat);

/*
Utiliza de uma dfs para contar a altura da árvore PATRICIA, retornado como inteiro

@param pat: cópia da árvore PATRICIA
*/
int pHeight(PAT *pat);

/*
Desaloca, de modo recursivo, todo o conteúdo da árvore PATRICIA

@param pat: Ponteiro para a árvore PATRICIA
*/
void freePat(PAT *pat);

#endif
