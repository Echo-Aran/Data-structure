#include"Stack.h"

void Init(ST* p)
{
	assert(p);

	p->a = (STDatatype*)malloc(sizeof(STDatatype) * 4);//在堆区开辟了一块空间
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

STDatatype Top(ST* p)//打印栈顶元素
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
		//用一个新的tmp来接收，因为在新的地址？
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

	//申请的是顺序表 不能单个删除 连续的内存空间
	/*free(p->a[p->top - 1]);*/
	p->top--;
}