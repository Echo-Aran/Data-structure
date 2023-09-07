#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
#include<stdlib.h>

typedef int QDataType;
typedef struct QueueNode
{
	QDataType data;
	struct QueueNode* next;
}QNode;
typedef struct Queue
{
	QNode* head;
	QNode* tail;
	int size;
}Queue;
typedef struct {
	Queue q1;
	Queue q2;

} MyStack;
void QueueInit(Queue* p)
{
	assert(p);
	p->head = p->tail = NULL;
	p->size = 0;
}
void QueuePush(Queue* p, QDataType x)
{
	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	if (newnode == NULL)
	{
		perror("malloc fail");
		return;
	}
	newnode->data = x;
	newnode->next = NULL;

	if (p->head == NULL)
	{
		assert(p->tail == NULL);
		p->head = p->tail = newnode;
	}
	else
	{
		p->tail->next = newnode;
		p->tail = newnode;//
	}
	p->size++;
}
void QueuePop(Queue* p)
{
	assert(p);
	assert(p->head != NULL);//判断是否有节点可以删除

	if (p->head->next == NULL)
	{
		free(p->head);//
		p->head = p->tail = NULL;
	}
	else
	{
		QNode* next = p->head->next;
		free(p->head);
		p->head = next;
	}
	p->size--;
}

bool QueueEmpty(Queue* p)
{
	assert(p);

	return p->size == 0;
}
QDataType QueueFront(Queue* p)
{
	assert(p);
	assert(!QueueEmpty(p));

	return p->head->data;
}

QDataType QueueBack(Queue* p)
{
	assert(p);
	assert(!QueueEmpty(p));

	return p->tail->data;
}
QDataType QueueSize(Queue* p)
{
	assert(p);
	return p->size;
}
void QueueDestroy(Queue* p)
{
	assert(p);
	QNode* cur = NULL;
	cur = p->head;
	while (cur)
	{
		QNode* next = cur->next;
		free(cur);
		cur = next;
	}
	p->head = p->tail = NULL; //
	p->size = 0;
}

MyStack* myStackCreate()
{
	MyStack* obj = (MyStack*)malloc(sizeof(MyStack));
	if (obj == NULL)
	{
		perror("malloc fail");
		return NULL;
	}
	QueueInit(&obj->q1);
	QueueInit(&obj->q2);
	return obj;
}
void myStackPush(MyStack* obj, int x) {
	if (!QueueEmpty(&obj->q1))
	{
		QueuePush(&obj->q1, x);
	}
	else
	{
		QueuePush(&obj->q2, x);
	}
}
int myStackPop(MyStack* obj) {
	Queue* nonEmpty = &obj->q1;
	Queue* Empty = &obj->q2;
	if (!QueueEmpty(&obj->q2))
	{
		nonEmpty = &obj->q2;//忘不了这两行了。。。
		Empty = &obj->q1;
	}
	while (QueueSize(nonEmpty) > 1)
	{
		int tmp = QueueFront(nonEmpty);
		QueuePush(Empty, tmp);
		QueuePop(nonEmpty);
	}
	int top = QueueFront(nonEmpty);
	QueuePop(nonEmpty);
	return top;
}
int myStackTop(MyStack* obj) {
	if (!QueueEmpty(&obj->q1))
	{
		return QueueBack(&obj->q1);
	}
	else
	{
		return QueueBack(&obj->q2);
	}
}
bool myStackEmpty(MyStack* obj) {
	return QueueEmpty(&obj->q1) && QueueEmpty(&obj->q2);
}
void myStackFree(MyStack* obj) {
	QueueDestroy(&obj->q1);
	QueueDestroy(&obj->q2);
	free(obj);
}


int main()
{
	MyStack* Stack=myStackCreate();

	QueuePush(&Stack->q1, 1);
	QueuePush(&Stack->q1, 2);
	QueuePush(&Stack->q1, 3);
	QueuePush(&Stack->q1, 4);
	QueuePush(&Stack->q1, 5);
	QueuePush(&Stack->q1, 6);
	QueuePush(&Stack->q1, 7);


	myStackPush(Stack, 8);
	myStackPush(Stack, 9);

	while (!myStackEmpty(Stack))
	{
		printf("%d ", myStackPop(Stack));
	}

}