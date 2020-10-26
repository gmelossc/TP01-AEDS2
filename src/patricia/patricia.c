/* TRABALHO PRÁTICO I:
*  GRUPO ^&|:
*             ÉLIDA EMELLY ANTUNES - 3012
*             GUILHERME CORRÊA MELOS - 3882
*             VINICIUS TOMÉ M. G. SILVA - 3874
*/

#include "patricia.h"

// Verifica se um nó da árvore PATRICIA é externo ou não
static bool isExt(PAT pat){
	return pat->pos == EXT ? 1 : 0;
}

// Inicializa tanto um nó interno quanto externo, alocando memória e apontando os dados passados
static void initpNode(pNode **node, Word *word, int pos, pNode *left, pNode *right, char c, Stats *stats){
	*node = (pNode*) malloc(sizeof(pNode));

	if(pos == EXT) initWord(&(*node)->word, word->str);
	else ((*node)->word) = NULL;

	(*node)->c = (pos == EXT ? '\0' : c);
	(*node)->pos = pos;
	(*node)->left = left;
	(*node)->right = right;

	if(pos == EXT) computeMemory(stats, (long long) sizeof(pNode) + (word->len + 1) * sizeof(char));
	else computeMemory(stats, (long long) sizeof(pNode));
}

/*
Adiciona uma nova palavra à árvore PATRICIA.

Esta função foi adaptada do livro Algorithms in C, do professor Robert Sedgewick e também contém adaptações do livro do professor Ziviani.
*/
static void addPatUtil(PAT *pat, Word word, Stats *stats){
	PAT *at, external, internal;
	int diff = 0;

	computeComparison(stats, 1, 1);
	if(!*pat) initpNode(pat, &word, EXT, NULL, NULL, '\0', stats);
	else{
		at = pat;
		while(!isExt(*at)){
			computeComparison(stats, 2, 1);
			if(word.str[(*at)->pos] <= (*at)->c) at = &(*at)->left;
			else at = &(*at)->right;
		}

		while(diff <= min(word.len, (*at)->word->len) && word.str[diff] == (*at)->word->str[diff]) ++diff;
		computeComparison(stats, diff, 1);

		if(diff > word.len || diff > (*at)->word->len){
			computeComparison(stats, 1, 1);
			return;
		}

		initpNode(&external, &word, -1, NULL, NULL, '\0', stats);

		computeComparison(stats, 1, 1);
		if(word.str[diff] <= (*at)->word->str[diff])
			initpNode(&internal, NULL, diff, external, NULL, word.str[diff], stats);
		else
			initpNode(&internal, NULL, diff, NULL, external, (*at)->word->str[diff], stats);

		at = pat;

		while((*at)->pos <= diff && !isExt(*at)){
			computeComparison(stats, 2, 1);
			if(word.str[(*at)->pos] <= (*at)->c) at = &(*at)->left;
			else at = &(*at)->right;
		}
		computeComparison(stats, 1, 1);
		if(internal->left) internal->right = *at;
		else internal->left = *at;

		*at = internal;
	}
}

/*
Verifica se uma palavra está ou não inserida na árvore PATRICIA.

Função baseada no trio que executa este trabalho
*/
static bool patFindUtil(PAT pat, Word word, Stats *stats){
	pNode *at;
	if(pat == NULL){
		computeComparison(stats, 1, 0);
		return 0;
	}
	at = pat;
	while(at->pos != EXT){
		computeComparison(stats, 2, 0);
		if(word.str[at->pos] <= at->c) at = at->left;
		else at = at->right;
	}
	return !strcmp(word.str, at->word->str);
}

// Inicializa a árvore PATRICIA
void initPat(PAT *pat){
	*pat = NULL;
}

// Modulariza a adicão de uma palavra na árvore PATRICIA, executa testes de comparação, tempo de execução e de uso de memória
void addPat(PAT *pat, Word word, Stats *stats, bool text){
	clock_t t;
	int cur_comp = stats->compI;
	long long cur_mem = stats->mem;

	if(text) addPatUtil(pat, word, stats);
	else{
		t = clock();
		addPatUtil(pat, word, stats);
		t = clock() - t;
		printf("Tempo de exercução: %.7lf segundos\n", (double) t/CLOCKS_PER_SEC);
		printf("Contagem de comparações: %d\n", stats->compI - cur_comp);
		printf("Memória utilizada: %lld bytes\n\n", stats->mem - cur_mem);
	}
}

// Modulariza a procura de uma palavra na árvore PATRICIA, executa testes de comparação e de tempo de execução
bool patFind(PAT pat, Word word, Stats *stats, bool text){
	bool found = 0;
	clock_t t;
	int cur_comp = stats->compP;

	if(text) found = patFindUtil(pat, word, stats);
	else{
	t = clock();
	found = patFindUtil(pat, word, stats);
	t = clock() - t;
	printf("Tempo de execução: %.7lf segundos\n", (double) t/CLOCKS_PER_SEC);
	printf("Contagem de comparações: %d\n", stats->compP - cur_comp);
	}
	return found;
}

// Conta quantas palavras existem na árvore PATRICIA (também serve para contar quantos nós externos existem)
int patCountWord(PAT pat){
	if(!pat) return 0;
	int ans = isExt(pat);
	ans += patCountWord(pat->left);
	ans += patCountWord(pat->right);
	return ans;
}

// Percorre a árvore PATRICIA com uma DFS para encontrar a sua altura
int pHeight(PAT *pat){
	return (!*pat ? -1 : 1 + max(pHeight(&(*pat)->left), pHeight(&(*pat)->right)));
}

// Percorre a árvore PATRICIA com um percurso in-order para printar as palavras inseridas em ordem lexicográfica
void patPrint(PAT pat){
    if(pat == NULL) return;
    patPrint(pat->left);
    if(isExt(pat)) printf("%s\n", pat->word->str);
    patPrint(pat->right);
}

// Desaloca todo o conteúdo da árvore PATRICIA
void freePat(PAT *pat){
	if(*pat == NULL) return;
	freePat(&(*pat)->left);
	freePat(&(*pat)->right);
	if(isExt(*pat)) freeWord(&(*pat)->word);
	free(*pat);
	*pat = NULL;
}
