#include "patricia.h"

static bool isExt(PAT pat){
	return pat->pos == EXT ? 1 : 0;
}

static void initpNode(pNode **node, Word *word, int pos, pNode *left, pNode *right, char c, Test *teste){
	*node = (pNode*) malloc(sizeof(pNode));

	if(pos == EXT) initWord(&(*node)->word, word->str);
	else ((*node)->word) = NULL;

	(*node)->c = (pos == EXT ? '\0' : c);
	(*node)->pos = pos;
	(*node)->left = left;
	(*node)->right = right;

	if(pos == EXT) computeMemory(teste, (long long) sizeof(pNode) + (word->len + 1) * sizeof(char));
	else computeMemory(teste, (long long) sizeof(pNode));
}

static void addPatUtil(PAT *pat, Word word, Test *teste){
	PAT *at, external, internal;
	int diff = 0;

	computeComparison(teste, 1);
	if(!*pat) initpNode(pat, &word, EXT, NULL, NULL, '\0', teste);
	else{
		at = pat;
		while(!isExt(*at)){
			computeComparison(teste, 2);
			if(word.str[(*at)->pos] <= (*at)->c) at = &(*at)->left;
			else at = &(*at)->right;
		}

		while(diff <= min(word.len, (*at)->word->len) && word.str[diff] == (*at)->word->str[diff]) ++diff;
		computeComparison(teste, diff);

		if(diff > word.len || diff > (*at)->word->len){
			computeComparison(teste, 1);
			return;
		}

		initpNode(&external, &word, -1, NULL, NULL, '\0', teste);

		computeComparison(teste, 1);
		if(word.str[diff] <= (*at)->word->str[diff])
			initpNode(&internal, NULL, diff, external, NULL, word.str[diff], teste);
		else
			initpNode(&internal, NULL, diff, NULL, external, (*at)->word->str[diff], teste);

		at = pat;

		while((*at)->pos <= diff && !isExt(*at)){
			computeComparison(teste, 2);
			if(word.str[(*at)->pos] <= (*at)->c) at = &(*at)->left;
			else at = &(*at)->right;
		}
		computeComparison(teste, 1);
		if(internal->left) internal->right = *at;
		else internal->left = *at;

		*at = internal;
	}
}

static bool patFindUtil(PAT pat, Word word, Test *teste){
	pNode *at;
	if(pat == NULL){
		computeComparison(teste, 1);
		return 0;
	}
	at = pat;
	while(at->pos != EXT){
		computeComparison(teste, 2);
		if(word.str[at->pos] <= at->c) at = at->left;
		else at = at->right;
	}
	return !strcmp(word.str, at->word->str);
}

void initPat(PAT *pat){
	*pat = NULL;
}

void addPat(PAT *pat, Word word, Test *teste, bool text){
	clock_t t;
	int cur_comp = teste->comp;
	long long cur_mem = teste->mem;

	if(text) addPatUtil(pat, word, teste);
	else{
		t = clock();
		addPatUtil(pat, word, teste);
		t = clock() - t;
		printf("Tempo de exercução: %.7lf segundos\n", (double) t/CLOCKS_PER_SEC);
		printf("Contagem de comparações: %d\n", teste->comp - cur_comp);
		printf("Memória utilizada: %lld bytes\n\n", teste->mem - cur_mem);
	}
}

bool patFind(PAT pat, Word word){
	Test test;
	bool found;
	initTest(&test);

	clock_t t = clock();
	found = patFindUtil(pat, word, &test);
	t = clock() - t;
	printf("Tempo de execução: %.7lf segundos\n", (double) t/CLOCKS_PER_SEC);
	printf("Contagem de comparações: %d\n", test.comp);

	return found;
}

void addtxtPat(PAT *pat, Test *teste){
	Word *word;
	FILE  *file;
	file = fopen("inputs/texto.txt", "r");
	char s[200];
	double ans = 0.0;
	clock_t t = clock();
	while(fscanf(file, "%s", s) != EOF){
    	initWord(&word, s);

		t = clock();
		addPat(pat, *word, teste, 1);
		t = clock() - t;
		
		ans += (double) t/CLOCKS_PER_SEC;
		freeWord(&word);
	}
	fclose(file);
	printf("Tempo de execução: %.7lf segundos\n", ans);
	printf("Contagem de comparações total do texto: %d\n", teste->comp);
	printf("Memória utilizada: %lld bytes\n\n", teste->mem);
}

int patCountWord(PAT pat){
	if(!pat) return 0;
	int ans = isExt(pat);
	ans += patCountWord(pat->left);
	ans += patCountWord(pat->right);
	return ans;
}

int pHeight(PAT *pat){
	return (!*pat ? -1 : 1 + max(pHeight(&(*pat)->left), pHeight(&(*pat)->right)));
}

void patPrint(PAT pat){
    if(pat == NULL) return;
    patPrint(pat->left);
    if(isExt(pat)) printf("%s\n", pat->word->str);
    patPrint(pat->right);
}

void freePat(PAT *pat){
	if(*pat == NULL) return;
	freePat(&(*pat)->left);
	freePat(&(*pat)->right);
	if(isExt(*pat)) freeWord(&(*pat)->word);
	free(*pat);
	*pat = NULL;
}
