#include "patricia.h"

static bool isExt(PAT pat){
	return pat->pos == EXT ? 1 : 0;
}

static void initNode(Node **node, Word *word, int pos, Node *left, Node *right, char c){
	*node = (Node*) malloc(sizeof(Node));

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

int height(PAT pat){
	return (pat == NULL ? -1 : 1 + max(height(pat->left), height(pat->right)));
}

void patriciaPrint(PAT pat){
    if(pat == NULL) return;
    patriciaPrintWords(pat->left);
    if(isExt(pat)) printf("%s\n", pat->word->str);
    patriciaPrintWords(pat->right);
}
