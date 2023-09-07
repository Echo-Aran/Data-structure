#include"Stack.h"

void STInit(ST* p)
{
	assert(p);

	p->a = (STDatatype*)malloc(sizeof(STDatatype) * 4);//�ڶ���������һ��ռ�
	p->top = 0;
	p->capacity = 4;
}

void STDestroy(ST* p)
{
	assert(p);

	free(p->a);
	p->a = NULL;
	p->top = 0;
	p->capacity = 0;

}
int STSize(ST* p)
{
	assert(p);
	return p->capacity;
}

bool STEmpty(ST* p)
{
	assert(p);
	return p->top == 0;
}

STDatatype STTop(ST* p)//��ӡջ��Ԫ��
{
	assert(p);
	assert(!STEmpty(p));

	STDatatype top = p->a[p->top - 1];
	return top;
}

void STPush(ST* p,STDatatype x)
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

void STPop(ST* p)
{
	assert(p);
	assert(!STEmpty(p));

	//�������˳��� ���ܵ���ɾ�� �������ڴ�ռ�
	/*free(p->a[p->top - 1]);*/
	p->top--;
}