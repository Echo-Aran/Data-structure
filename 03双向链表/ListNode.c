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
ListNode* Init()//����ͷ�ڵ�
{
	ListNode* phead = BuyNewnode(-1);
	phead->next = phead;
	phead->prev = phead;

	return phead;
}

void Print(ListNode* phead)//��ӡ
{
	assert(phead);

	printf("<=head=>");
	ListNode* cur = phead->next;//phead��ĵ�һ���ڵ㿪ʼ
	while (cur != phead)
	{
		printf("%d<=>", cur->data);
		cur = cur->next;
	}
	printf("\n");
}

bool Empty(ListNode* phead)//�ж��Ƿ�Ϊ��ѭ������
{
	assert(phead);
	return phead->next == phead;//ѧ�ŵ�  ��ȷ��ʱ��Ϊ����ѭ��
}

void ListInsert(ListNode* pos, LTDataType x)//posǰλ�ò���
{
	assert(pos);
	ListNode* newnode = BuyNewnode(x);
	newnode->prev = pos->prev;
	newnode->next = pos;

	pos->prev->next = newnode;
	pos->prev = newnode;
	
}

void PushBack(ListNode* phead, LTDataType x)//β��
{
	ListInsert(phead, x);
}
void PushFront(ListNode* phead, LTDataType x)//ͷ��   ͷ���β�岻��һ��������
{
	ListInsert(phead->next, x);
}

void ListErase(ListNode* pos)//ͷɾposǰ�Ľڵ�
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
	//assert(!Empty(phead));//��0 ��ȷ   0����
	//ListNode*tail= phead->prev->prev;
	//tail->next = phead;
	//free(phead->prev);
	//phead->prev = NULL;
	//phead->prev = tail;

	ListErase(phead);
}
void PopFront(ListNode* phead)//ͷɾ
{
	/*assert(!Empty(phead));*/
	/*ListNode* D1 = phead->next->next;
	D1->prev = phead;
	free(phead->next);
	phead->next = NULL;
	phead->next = D1;*/

	ListErase(phead->next->next);
}

ListNode* Destroy(ListNode* p)//����
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