/* TRABALHO PRÁTICO I:
*  GRUPO ^&|:
*             ÉLIDA EMELLY ANTUNES - 3012
*             GUILHERME CORRÊA MELOS - 3882
*             VINICIUS TOMÉ M. G. SILVA - 3874
*/

#include "tst.h"

// Aloca um tNode na memória
static void alloctNode(tNode **node){
	*node = (tNode*) malloc(sizeof(tNode));
}

// Inicializa um novo nó na trie TST, com os dados parâmetros
static void inittNode(tNode **node, char c, Stats *stats){
	alloctNode(node);
	(*node)-> end = false;
	(*node)->left = NULL;
	(*node)->mid = NULL;
	(*node)->right = NULL;
	(*node)->c = c;
	computeMemory(stats, (long long) sizeof(tNode));
}

// Desaloca um tNode da memória
static void freetNode(tNode *node){
	free(node);
}

// Printa as palavras que foram inseridas na trie TST, utilizando o percurso in-order e uma string auxiliar para recuperar os caracteres da recursão
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

/*
Adiciona de modo iterativo uma palavra à trie tst.

Função baseada no trio que executa este trabalho
*/
static void addTSTUtil(TST *tst, char s[], int len, Stats *stats){
	int i = 0;
	tNode **at;
	at = tst;

	while(i < len){
		computeComparison(stats, 2);
		if(!*at){
			computeComparison(stats, 1);
			inittNode(at, s[i], stats);
			if(i == len - 1){
				(*at)->end = 1;
				computeComparison(stats, 1);
				break;
			}
		}
		if((*at)->c == s[i]){
			if(i == len - 1){
				(*at)->end = 1;
				break;
			}
			at = &(*at)->mid;
			++i;
		}
		else if((*at)->c > s[i]) at = &(*at)->left;
		else at = &(*at)->right;
	}
}

/*
Procura se um palavra está inserida ou não na trie tst

O pseudocódigo desta função pode ser encontrado no Wikipedia anglófano.
*/
static bool tstFindUtil(TST tst, char s[], Stats *stats){
    tNode *at;
	at = tst;
	int len = strlen(s);
	int i = 0;

    while(i < len - 1){
		computeComparison(stats, 2);
		if(!at){
			computeComparison(stats, 1);
			return 0;
		}
		if(s[i] < at->c) at = at->left;
		else if(s[i] == at->c){
			at = at->mid;
			++i;
		}
		else at = at->right;
    }
    return at->end;
}

// Inicializa a trie TST
void initTST(TST *tst){
	*tst = NULL;
}

// Adiciona uma palavra à árvore (modularizado) e executa testes de tempo de execução, de comparação e de uso de memória
void addTST(TST *tst, char s[], int len, Stats *stats, bool text){
	clock_t t;
	int cur_comp = stats->comp;
	int cur_mem = stats->mem;

	if(text) addTSTUtil(tst, s, len, stats);
	else{
		t = clock();
		addTSTUtil(tst, s, len, stats);
		t = clock() - t;

		printf("Tempo de execução: %.7lf segundos\n", (double) t/CLOCKS_PER_SEC);
		printf("Contagem de comparações: %d\n", stats->comp - cur_comp);
		printf("Memória utilizada: %lld bytes\n\n", stats->mem - cur_mem);
	}
}

// Modulariza a função addTST com fim de adicionar textos por arquivo e executa testes globais de tempo de execução, de comparação e de uso de memória
void addtxtTST(TST *tst, Stats *stats, char filename[]){
	int len;
	FILE  *file;
	double ans = 0.0;
	clock_t t;

	file = fopen(filename, "r");
	if(file == NULL){
		printf("Arquivo não encontrado\n\n");
		return;
	}
	char s[200];

	while(fscanf(file, "%s", s) != EOF){
    	len = 1;
    	while(s[len] != '\0') ++len;
		t = clock();
		addTST(tst, s, len, stats, 1);
		t = clock() - t;
		ans += (double) t/CLOCKS_PER_SEC;
	}
	fclose(file);
	printf("\nAs palavras do arquivo \"%s\" foram adicionadas na trie TST.\n", filename);
	printf("Tempo de execução: %.7lf segundos\n", ans);
	printf("Contagem de comparações: %d\n", stats->comp);
	printf("Memória utilizada: %lld\n", stats->mem);
}

// Procura se uma palavra está inserida ou não na trie TST (de modo modularizado) e executa testes de comaparação e de tempo de execução
bool tstFind(TST tst, char s[]){
	clock_t t;
	bool found;
	Stats stats;
	initStats(&stats);

	t = clock();
	found = tstFindUtil(tst, s, &stats);
	t = clock() - t;
	printf("Tempo de execução: %.7lf segundos\n", (double) t/CLOCKS_PER_SEC);
	printf("Contagem de comparações: %d\n", stats.comp);
	return found;
}

// Modulariza a função de printar as palavras inseridas na TST, passando como parâmetro para esta uma string
void tstPrint(TST tst){
	char str[700];
	printTST(tst, str, 0);
}

// Percorre com uma DFS a trie TST contando suas palavras
int tstCountWord(TST tst){
	if(!tst) return 0;

	int ans = (tst->end ? 1 : 0);
	ans += tstCountWord(tst->left);
	ans += tstCountWord(tst->mid);
	ans += tstCountWord(tst->right);

	return ans;
}

// Percorre com uma DFS a trie TST, contando a sua altura
int tHeight(TST *tst){
	return (!*tst? -1 : 1 + max(tHeight(&(*tst)->left), max(tHeight(&(*tst)->mid), tHeight(&(*tst)->right))));
}

// Desaloca todo o conteúdo da trie TST
void freeTST(TST *tst){
	if(!*tst) return;
	freeTST(&(*tst)->left);
	freeTST(&(*tst)->mid);
	freeTST(&(*tst)->right);
	free(*tst);
	*tst = NULL;
}
