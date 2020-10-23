#include "tst.h"

static void allocNode(tNode **node){
	*node = (tNode*) malloc(sizeof(tNode));
}

static void initNode(tNode **node, char c){ //inicializa um node
	allocNode(node);
	(*node)-> end = false;
	(*node)->left = NULL;
	(*node)->mid = NULL;
	(*node)->right = NULL;
	(*node)->c = c;
}

static void freeNode(tNode *node){ //desaloca um tNode
	free(node);
}

void initTST(TST *tst){
	*tst = NULL;
}

void addTST(TST *tst, char s[], int len){
	int i = 0; // defino um auxiliar para iterar nas posições do caractere da string a ser inserido
	tNode **at;
	at = tst; //defino um auxiliar para interar na tst

	while(i < len){
		if(!*at){
			initNode(at, s[i]); // se a raíz é nula, então se inicializa um novo nó com o atributo s[i]
			if(i == len - 1){
				(*at)->end = 1;
				break;
			}
		}
		if((*at)->c == s[i]){ //se o caractere da raíz é igual ao caractere da string a ser inserido, então sigo pelo meio e incremento a posição da string (pois o caractere já foi inserido)
			if(i == len - 1){
				(*at)->end = 1;
				break;
			}
			at = &(*at)->mid;
			++i;
		}
		else if((*at)->c > s[i]) at = &(*at)->left;//se o caractere a ser inserido for maior do que a raíz, então sigo pela direita
		else at = &(*at)->right;//se o caractere a ser inserido for maior do que a raíz, então sigo pela esquerda
	}
}

bool tstFind(TST tst, char s[]){
    tNode *at;
	at = tst;
	int len = strlen(s);
	int i = 0;

    while(i < len - 1){
		if(!at) return 0;
		if(s[i] < at->c) at = at->left;
		else if(s[i] == at->c){
			at = at->mid;
			++i;
		}
		else at = at->right;
    }
    return at->end;
}

static void printTST(TST tst, char str[], int pos){
    if(!tst) return;

    printTST(tst->left, str, pos);
	str[pos] = tst->c;

    if(tst->end){
		str[pos + 1] = '\0';
		printf("%s\n", str);
	}

    printTST(tst->mid, str, pos + 1);
    printTST(tst->right, str, pos);
}

void tstPrint(TST tst){
	char str[700];
	printTST(tst, str, 0);
}

int tstCountWord(TST tst){
	if(!tst) return 0;

	int ans = (tst->end ? 1 : 0);
	ans += tstCountWord(tst->left);
	ans += tstCountWord(tst->mid);
	ans += tstCountWord(tst->right);

	return ans;
}

void freeTST(TST *tst){
	if(!*tst) return;
	freeTST(&(*tst)->left);
	freeTST(&(*tst)->mid);
	freeTST(&(*tst)->right);
	free(*tst);
	*tst = NULL;
}
