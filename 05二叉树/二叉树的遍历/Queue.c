#include"Queue.h"
void QueueInit(Queue* p)
{
	assert(p);
	p->head = p->tail = NULL;
	p->size = 0;
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
void QueuePush(Queue* p,QDataType x)
{
	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	if (newnode == NULL)
	{
		perror("malloc fail");
		return;
	}
	newnode->data = x;
	newnode->next = NULL;

	if (p->head==NULL)
	{
		assert(p->tail == NULL);
		p->head = p->tail = newnode;
	}
	else
	{
		p->tail->next = newnode;
		p->tail=newnode;
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
	return p->size == 0;//是空返回1，不是空返回0
}
QDataType QueueFront(Queue* p)
{
	assert(p);
	assert(!QueueEmpty(p));

	return p->head->data;
}
QDataType QueueBlack(Queue* p)
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