#include"ListNode.h"
ListNode* BuyNewnode(LTDataType x)
{
	ListNode* newnode = (struct ListNode*)malloc(sizeof(ListNode));
	if (newnode == NULL)
	{
		perror("malloc fail");
		return NULL;
	}
	newnode->data = x;
	newnode->next = NULL;
	newnode->prev = NULL;
	return newnode;
}
ListNode* Init()//创建头节点
{
	ListNode* phead = BuyNewnode(-1);
	phead->next = phead;
	phead->prev = phead;

	return phead;
}

void Print(ListNode* phead)//打印
{
	assert(phead);

	printf("<=head=>");
	ListNode* cur = phead->next;//phead后的第一个节点开始
	while (cur != phead)
	{
		printf("%d<=>", cur->data);
		cur = cur->next;
	}
	printf("\n");
}

bool Empty(ListNode* phead)//判断是否为单循环链表
{
	assert(phead);
	return phead->next == phead;//学着点  正确的时候为自身循环
}

void ListInsert(ListNode* pos, LTDataType x)//pos前位置插入
{
	assert(pos);
	ListNode* newnode = BuyNewnode(x);
	newnode->prev = pos->prev;
	newnode->next = pos;

	pos->prev->next = newnode;
	pos->prev = newnode;
	
}

void PushBack(ListNode* phead, LTDataType x)//尾插
{
	ListInsert(phead, x);
}
void PushFront(ListNode* phead, LTDataType x)//头插   头插和尾插不是一个概念吗？
{
	ListInsert(phead->next, x);
}

void ListErase(ListNode* pos)//头删pos前的节点
{
	assert(!Empty(pos));
	ListNode* newprev = pos->prev->prev;
	pos->prev = newprev;
	free(newprev->next);
	newprev->next = NULL;
	newprev->next = pos;
}
void PopBack(ListNode* phead)
{
	//assert(!Empty(phead));//非0 正确   0错误
	//ListNode*tail= phead->prev->prev;
	//tail->next = phead;
	//free(phead->prev);
	//phead->prev = NULL;
	//phead->prev = tail;

	ListErase(phead);
}
void PopFront(ListNode* phead)//头删
{
	/*assert(!Empty(phead));*/
	/*ListNode* D1 = phead->next->next;
	D1->prev = phead;
	free(phead->next);
	phead->next = NULL;
	phead->next = D1;*/

	ListErase(phead->next->next);
}

ListNode* Destroy(ListNode* p)//销毁
{
	assert(p);
	p->prev->next = NULL;
	while (p->next != NULL)
	{
		ListNode* tmp = p->next;
		free(p);
		p = tmp;
	}
	free(p);
	p = NULL;
	return NULL;
}