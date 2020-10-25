/* TRABALHO PRÁTICO I:
*  GRUPO ^&|:
*             ÉLIDA EMELLY ANTUNES - 3012
*             GUILHERME CORRÊA MELOS - 3882
*             VINICIUS TOMÉ M. G. SILVA - 3874
*/

#include "stats.h"

// Inicializa um novo stats a ser executado (numa nova árvore)
void initStats(Stats *stats){
	stats->mem = 0;
	stats->comp = 0;
}

// Incrementa o contador de memória
void computeMemory(Stats *stats, long long mem){
	stats->mem += mem;
}

// Incrementa o contador de comparações
void computeComparison(Stats *stats, int comp){
	stats->comp += comp;
}
