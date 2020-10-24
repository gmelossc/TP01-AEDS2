#include "menu.h"

static int len(char s[]){
	int i = 0;
	while(s[i] != '\0') ++i;
	return i;
}

void menu(){
	PAT pat;
	TST tst;
	Word *word;
	Test test_pat, test_tst;
	int arvore = 0, add = 0;
	bool flag = 1;
	char s[200];
	int op = 0;
	system("clear");
	printf("TRABALHO PRÁTICO I: Árvore PATRICIA e trie TST\n\n");
	printf("GRUPO ^&|:\nÉLIDA EMELLY ANTUNES - 3012\n");
	printf("GUILHERME CORRÊA MELOS - 3882\n");
	printf("VINICIUS TOMÉ M. G. SILVA - 3874\n");
	initPat(&pat);
	initTST(&tst);
	initTest(&test_tst);
	initTest(&test_pat);
	while(flag){
		printf("Operações disponíveis\n\n");
		printf("1 - Escolher árvore\n");
		printf("2 - Inserir palavra ou texto\n");
		printf("3 - Pesquisar palavra\n");
		printf("4 - Exibir todas as palavras em ordem alfabética\n");
		printf("5 - Contar palavras\n");
		printf("6 - Gerar relatório\n");
		printf("7 - Remover todo o conteúdo da árvore\n");
		printf("0 - Sair\n");
		if(arvore) printf("\nAVISO: esta operação será realizada na %s\n", (arvore == 1 ? "árvore PATRICIA" : "trie TST"));
		printf("Digite abaixo o número da operação que deseja executar:\n");
		scanf("%d", &op);

		switch(op){
			case 0:
				freeTST(&tst);
				freePat(&pat);
				flag = 0;
				break;
			case 1:
				system("clear");
				printf("1 - Árvore PATRICIA\n");
				printf("2 - Trie TST\n");
				printf("Digite abaixo qual árvore deseja escolher\n");
				scanf("%d", &arvore);

				if(arvore == 1)
					if(!pat) initPat(&pat);
				else
					if(!tst) initTST(&tst);
				break;
			case 2:
				system("clear");
				printf("1 - Inserir palavra\n");
				printf("2 - Inserir texto.txt\n");
				printf("Digite abaixo o número da operação que deseja executar:\n");
				scanf("%d", &add);
				if(add == 1){
    					system("clear");
    					printf("Digite abaixo palavra que deseja inserir na %s\n", (arvore == 1 ? "árvore PATRICIA" : "trie TST"));
    					scanf("%s", s);
    					if(arvore == 1){
        					initWord(&word, s);
        					addPat(&pat, *word, &test_pat, 0);
        					free(word);
    					}
    					else addTST(&tst, s, len(s), &test_tst, 0);
				}
				else{
    					system("clear");
    					if(arvore == 1){
        					addtxtPat(&pat, &test_pat);
        					printf("As palavras do arquivo texto.txt foram adicionadas na árvore PATRICIA.\n");
    					}
    					else{
        					addtxtTST(&tst, &test_tst);
        					printf("As palavras do arquivo texto.txt foram adicionadas na trie TST.\n");
    					}
				}
				break;
			case 3:
				system("clear");
				printf("Digite abaixo palavra que deseja pesquisar na %s\n", (arvore == 1 ? "árvore PATRICIA" : "trie TST"));
				scanf("%s", s);
				if(arvore == 1){
					initWord(&word, s);
					printf("A palavra %s %s\n\n", s, (patFind(pat, *word) ? "está inserida" : "não está inserida"));
					free(word);
				}
				else printf("A palavra %s %s\n\n", s, (tstFind(tst, s) ? "está inserida" : "não está inserida"));
				break;
			case 4:
				system("clear");
				if(arvore == 1){
					printf("Palavras inseridas na árvore PATRICIA em ordem alfabética:\n");
					patPrint(pat);
					printf("\n");
				}
				else{
					printf("Palavras inseridas na trie TST em ordem alfabética:\n");
					tstPrint(tst);
					printf("\n");
				}
				break;
			case 5:
				system("clear");
				if(arvore == 1) printf("%d palavras foram inseridas na %s\n", patCountWord(pat), (arvore == 1? "árvore PATRICIA" : "trie TST"));
				else printf("%d palavras foram inseridas na %s\n", tstCountWord(tst), (arvore == 1? "árvore PATRICIA" : "trie TST"));
				break;
			case 6:
				system("clear");
				if(arvore == 1){
					printf("Altura da árvore PATRICIA: %d\n", pHeight(&pat));
					printf("Contagem de comparações em todas as inserções: %d\n", test_pat.comp);
					printf("Memória utilizada em todos os nós da árvore: %lld bytes\n\n", test_pat.mem);
				}
				else{
					printf("Altura da trie TST: %d\n", tHeight(&tst));
					printf("Contagem de comparações em todas as inserções: %d\n", test_tst.comp);
					printf("Memória utilizada em toda a árvore: %lld bytes\n\n", test_tst.mem);
				}
				break;
			case 7:
				system("clear");
				if(arvore == 1) freePat(&pat), initTest(&test_pat);
				else freeTST(&tst), initTest(&test_tst);
				printf("Todo o conteúdo da %s foi removido! :D\n\n", (arvore == 1? "árvore PATRICIA": "trie TST"));
				break;
			default:
				system("clear");
				printf("Operação não permitida\n\n");
				break;
		}
	}
}
