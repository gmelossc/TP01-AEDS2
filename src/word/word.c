#include "word.h"

void initWord(Word **word, char str[]){
	int len = strlen(str);
	allocWord(word);

	(*word)->str = (char*) malloc((len+1) * sizeof(char));
	strcpy((*word)->str, str);
	(*word)->len = len;
}

void allocWord(Word **word){
	*word = (Word*) malloc(sizeof(Word));
	(*word)->len = 0;
	(*word)->str = NULL;
}

void freeWord(Word **word){
	free(*word);
}
