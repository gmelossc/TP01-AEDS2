#include "tst.h"

static void alloctNode(tNode **node){
	*node = (tNode*) malloc(sizeof(tNode));
}

static void inittNode(tNode **node, char c, Test *teste){ //inicializa um node
	alloctNode(node);
	(*node)-> end = false;
	(*node)->left = NULL;
	(*node)->mid = NULL;
	(*node)->right = NULL;
	(*node)->c = c;
	computeMemory(teste, (long long) sizeof(tNode));
}

static void freetNode(tNode *node){ //desaloca um tNode
	free(node);
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

static void addTSTUtil(TST *tst, char s[], int len, Test *teste){
	int i = 0; // defino um auxiliar para iterar nas posições do caractere da string a ser inserido
	tNode **at;
	at = tst; //defino um auxiliar para interar na tst

	while(i < len){
		computeComparison(teste, 2);
		if(!*at){
			computeComparison(teste, 1);
			inittNode(at, s[i], teste); // se a raíz é nula, então se inicializa um novo nó com o atributo s[i]
			if(i == len - 1){
				(*at)->end = 1;
				computeComparison(teste, 1);
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

static bool tstFindUtil(TST tst, char s[], Test *teste){
    tNode *at;
	at = tst;
	int len = strlen(s);
	int i = 0;

    while(i < len - 1){
		computeComparison(teste, 2);
		if(!at){
			computeComparison(teste, 1);
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

void initTST(TST *tst){
	*tst = NULL;
}

void addtxtTST(TST *tst, Test *teste){
	int len;
	FILE  *file;
	double ans = 0.0;
	clock_t t;


	file = fopen("inputs/texto.txt", "r");
	char s[200];

	while(fscanf(file, "%s", s) != EOF){
    	len = 1;
    	while(s[len] != '\0') ++len;
		t = clock();
		addTST(tst, s, len, teste, 1);
		t = clock() - t;
		ans += (double) t/CLOCKS_PER_SEC;
	}
	fclose(file);
	printf("Tempo de execução: %.7lf segundos\n", ans);
	printf("Contagem de comparações: %d\n", teste->comp);
	printf("Memória utilizada: %lld\n", teste->mem);
}

void addTST(TST *tst, char s[], int len, Test *teste, bool text){
	clock_t t;
	int cur_comp = teste->comp;
	int cur_mem = teste->mem;

	if(text) addTSTUtil(tst, s, len, teste);
	else{
		t = clock();
		addTSTUtil(tst, s, len, teste);
		t = clock() - t;

		printf("Tempo de execução: %.7lf segundos\n", (double) t/CLOCKS_PER_SEC);
		printf("Contagem de comparações: %d\n", teste->comp - cur_comp);
		printf("Memória utilizada: %lld bytes\n\n", teste->mem - cur_mem);
	}
}

bool tstFind(TST tst, char s[]){
	clock_t t;
	bool found;
	Test teste;
	initTest(&teste);

	t = clock();
	found = tstFindUtil(tst, s, &teste);
	t = clock() - t;
	printf("Tempo de execução: %.7lf segundos\n", (double) t/CLOCKS_PER_SEC);
	printf("Contagem de comparações: %d\n", teste.comp);
	return found;
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

int tHeight(TST *tst){
	return (!*tst? -1 : 1 + max(tHeight(&(*tst)->left), max(tHeight(&(*tst)->mid), tHeight(&(*tst)->right))));
}

void freeTST(TST *tst){
	if(!*tst) return;
	freeTST(&(*tst)->left);
	freeTST(&(*tst)->mid);
	freeTST(&(*tst)->right);
	free(*tst);
	*tst = NULL;
}
