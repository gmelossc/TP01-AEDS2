/* TRABALHO PRÁTICO I:
*  GRUPO ^&|:
*             ÉLIDA EMELLY ANTUNES - 3012
*             GUILHERME CORRÊA MELOS - 3882
*             VINICIUS TOMÉ M. G. SILVA - 3874
*/

#ifndef __STATS_H__
#define __STATS_H__

#include <time.h>
#include <stdbool.h>

/*
Os testes de comparação e de uso de memória foram feitos com base no tipo abstrato de dados Stats

@param compI: número de comparações na inserção
@param compP: número de comparações na pesquisa
@param mem: memória em bytes
*/
typedef struct stats{
	int compI;
	int compP;
	long long mem;
} Stats;

/*
Inicializa um novo teste

@param stats: Ponteiro para um teste
*/
void initStats(Stats *test);

/*
Incrementa ou decrementa o uso de memória no teste

@param stats: Ponteiro para um teste
@param mem: Quantidade de memória em bytes a ser incrementado
*/
void computeMemory(Stats *stats, long long mem);

/*
Incrementa número de comparações no teste

@param stats: Ponteiro para um teste
@param comp: Quantidade de memória em bytes a ser incrementado
@param type: Informa o tipo se o tipo de comparação é de inserção ou de pesquisa
*/
void computeComparison(Stats *stats, int comp, bool type);

#endif
