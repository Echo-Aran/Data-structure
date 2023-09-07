#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

typedef int HPDataType;
typedef struct Heap
{
	HPDataType* a;
	int size;
	int capacity;
}HP;

void HeapInit(HP* php);
void HeapInitArray(HP* php, int* a, int n);
void HeapDestroy(HP* php);

void HeapPush(HP* php,HPDataType x);
void HeapPop(HP* php);
HPDataType HeapTop(HP* php);
bool HeapEmpty(HP* php);
int HeapSize(HP* php);  

void AdjustUp(HPDataType* a, int child);
void AdjustDown(HPDataType* a, int n, int parent);

void Swap(HPDataType* a, HPDataType* b);
void PrintTopK(HPDataType* a, int n, int k);//找出N个数里最大或最小的前K个问题
