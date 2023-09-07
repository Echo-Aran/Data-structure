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

void Init(ST* p);
void Destroy(ST* p);

int Size(ST* p);
bool Empty(ST* p);
STDatatype Top(ST* p);

void Push(ST* p,STDatatype x);
void Pop(ST* p);




