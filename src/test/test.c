#include "test.h"

void initTest(Test *test){
	test->mem = 0;
	test->comp = 0;
}

void computeMemory(Test *teste, long long mem){
	teste->mem += mem;
}

void computeComparison(Test *teste, int comp){
	teste->comp += comp;
}
