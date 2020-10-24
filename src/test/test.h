#ifndef __TEST_H__
#define __TEST_H__

#include <time.h>

typedef struct test{
	int comp;
	long long mem;
} Test;

void initTest(Test *test);
void computeMemory(Test *teste, long long mem);
void computeComparison(Test *test, int comp);

#endif
