#include "tst.h"

static void allocNode(Node **node){
	*node = (Node*) malloc(sizeof(Node));
}

static void initNode(Node **node, char c){ //inicializa um node
	allocNode(node);
	(*node)-> end = false;
	(*node)->left = NULL;
	(*node)->mid = NULL;
	(*node)->right = NULL;
	(*node)->c = c;
}

static void freeNode(Node *node){ //desaloca um Node
	free(node);
}

void initTST(TST *tst){
	*tst = NULL;
}


void addTST(TST *tst, char s[], int len){
	int i = 0; // defino um auxiliar para iterar nas posições do caractere da string a ser inserido
	Node *at;
	at = *tst; //defino um auxiliar para interar na tst

	while(i < len){
		if(!at) initNode(&at, s[i]); // se a raíz é nula, então se inicializa um novo nó com o atributo s[i]
		if(i == len - 1){
			at->end = true; //se chego na posição final da string, então marco um fim de palavra
			break;
		}
		if(at->c == s[i]){ //se o caractere da raíz é igual ao caractere da string a ser inserido, então sigo pelo meio e incremento a posição da string (pois o caractere já foi inserido)
			at = at->mid;
			++i;
		}
		else if(at->c > s[i]) at = at->left;//se o caractere a ser inserido for maior do que a raíz, então sigo pela direita
		else at = at->right;//se o caractere a ser inserido for maior do que a raíz, então sigo pela esquerda
	}
}

void freeTST(TST *tst){
	if(*tst == NULL) return;
	freeTST(&(*tst)->left);
	freeTST(&(*tst)->mid);
	freeTST(&(*tst)->right);
	free(*tst);
	*tst = NULL;
}
