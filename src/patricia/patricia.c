#include "patricia.h"

static bool isExt(PAT pat){
	return pat->pos == EXT ? 1 : 0;
}

static void initNode(pNode **node, Word *word, int pos, pNode *left, pNode *right, char c){
	*node = (pNode*) malloc(sizeof(pNode));

	if(pos == EXT) initWord(&(*node)->word, word->str);
	else ((*node)->word) = NULL;

	(*node)->c = (pos == EXT ? '\0' : c);
	(*node)->pos = pos;
	(*node)->left = left;
	(*node)->right = right;
}

void initPat(PAT *pat){
	*pat = NULL;
}

void addPat(PAT *pat, Word word){
	PAT *at, external, internal;
	int diff = 0;

	if(!*pat) initNode(pat, &word, EXT, NULL, NULL, '\0');
	else{
		at = pat;
		while(!isExt(*at)){
			if(word.str[(*at)->pos] <= (*at)->c) at = &(*at)->left;
			else at = &(*at)->right;
		}

		while(diff <= min(word.len, (*at)->word->len) && word.str[diff] == (*at)->word->str[diff]) ++diff;

		if(diff > word.len || diff > (*at)->word->len) return;

		initNode(&external, &word, -1, NULL, NULL, '\0');

		if(word.str[diff] <= (*at)->word->str[diff])
			initNode(&internal, NULL, diff, external, NULL, word.str[diff]);
		else
			initNode(&internal, NULL, diff, NULL, external, (*at)->word->str[diff]);

		at = pat;

		while((*at)->pos <= diff && !isExt(*at)){
			if(word.str[(*at)->pos] <= (*at)->c) at = &(*at)->left;
			else at = &(*at)->right;
		}
		if(internal->left) internal->right = *at;
		else internal->left = *at;

		*at = internal;
	}
}

void addtxtPat(PAT *pat){
	Word *word;
    	FILE  *file;
    	file = fopen("texto.txt", "r");
    	char s[200];

    	while(fscanf(file, "%s", s) != EOF ){
        	initWord(&word, s);
		addPat(pat, *word);
		free(word);
    	}
    	fclose(file);
}

int patCountWord(PAT pat){
	if(!pat) return 0;
	int ans = isExt(pat);
	ans += patCountWord(pat->left);
	ans += patCountWord(pat->right);
	return ans;
}

int height(PAT pat){
	return (pat == NULL ? -1 : 1 + max(height(pat->left), height(pat->right)));
}

void patPrint(PAT pat){
    if(pat == NULL) return;
    patPrint(pat->left);
    if(isExt(pat)) printf("%s\n", pat->word->str);
    patPrint(pat->right);
}

bool patFind(PAT pat, Word word){
	pNode *at;
	if(pat == NULL) return 0;
	at = pat;
	while(at->pos != EXT){
		if(word.str[at->pos] <= at->c) at = at->left;
		else at = at->right;
	}
	return !strcmp(word.str, at->word->str);
}

void freePat(PAT *pat){
	if(*pat == NULL) return;
	freePat(&(*pat)->left);
	freePat(&(*pat)->right);
	free(*pat);
	*pat = NULL;
}
