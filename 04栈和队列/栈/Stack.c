#include"Stack.h"

void Init(ST* p)
{
	assert(p);

	p->a = (STDatatype*)malloc(sizeof(STDatatype) * 4);//�ڶ���������һ��ռ�
	p->top = 0;
	p->capacity = 4;
}

void Destroy(ST* p)
{
	assert(p);

	free(p->a);
	p->a = NULL;
	p->top = 0;
	p->capacity = 0;

}
int Size(ST* p)
{
	assert(p);
	return p->capacity;
}

bool Empty(ST* p)
{
	assert(p);
	return p->top == 0;
}

STDatatype Top(ST* p)//��ӡջ��Ԫ��
{
	assert(p);
	assert(!Empty(p));

	STDatatype top = p->a[p->top - 1];
	return top;
}

void Push(ST* p,STDatatype x)
{
	assert(p);
	if (p->top == p->capacity)
	{
		//��һ���µ�tmp�����գ���Ϊ���µĵ�ַ��
		STDatatype* tmp = realloc(p->a,sizeof(STDatatype) * p->capacity * 2);
		if (tmp == NULL)
		{
			perror("realloc fail");
			return NULL;
		}
		p->a = tmp;
		p->capacity *= 2;
	}
	p->a[p->top] = x;
	p->top++;
}

void Pop(ST* p)
{
	assert(p);
	assert(!Empty(p));

	//�������˳��� ���ܵ���ɾ�� �������ڴ�ռ�
	/*free(p->a[p->top - 1]);*/
	p->top--;
}