#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

typedef int QDataType;

typedef struct QueueNode
{
	QDataType data;
	struct QueueNode* next;//
}QNode;

typedef struct Queue
{
	QNode* head;
	QNode* tail;
	int size;
}Queue;

void QueueInit(Queue* p);
void QueueDestroy(Queue* p);
void QueuePush(Queue* p,QDataType x);
void QueuePop(Queue* p);
bool QueueEmpty(Queue* p);
QDataType QueueFront(Queue* p);
QDataType QueueBlack(Queue* p);
QDataType QueueSize(Queue* p);

