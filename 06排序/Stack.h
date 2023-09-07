#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
typedef int STDatatype;
typedef struct Stack
{
	STDatatype* a;
	int top;
	int capacity;
}ST;

void STInit(ST* p);
void STDestroy(ST* p);

int STSize(ST* p);
bool STEmpty(ST* p);
STDatatype STTop(ST* p);

void STPush(ST* p,STDatatype x);
void STPop(ST* p);




