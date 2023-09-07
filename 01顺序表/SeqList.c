#include"SeqList.h"
void SLInit(SL* ps)
{
	ps->a = (SLDataType*)malloc(sizeof(SLDataType) * Init_Capacity);
	if (ps->a == NULL)
	{
		perror("malloc fail");
		return;
	}
	ps->size = 0;
	ps->capacity = Init_Capacity;
}

void SLDestroy(SL* ps)
{
	free(ps->a);
	ps->a = NULL;
	ps->capacity = ps->size = 0;
}

void SLPrint(SL* ps)
{
	for (int i = 0; i < ps->size; i++)
	{
		printf("%d ", ps->a[i]);
	}
	printf("\n");
}

void  SLPushBack(SL* ps,SLDataType x)
{
	if (ps->size == ps->capacity)
	{
		SLDataType*tmp = (SLDataType*)realloc(ps->a, 2 * sizeof(SLDataType) * (ps->capacity));//原地址扩容或者异地扩容（设置中间量的原因）
		if (tmp == NULL)
		{
			perror("realloc fail");
			return;
		}
		ps->a = tmp;
		ps->capacity *= 2;//
	}
	ps->a[ps->size] = x;
	ps->size++;
	
}
void SLPopBack(SL* ps, SLDataType x)
{
	assert(ps->size >0);//暴力检查
	//温柔检查
	/*if(ps->size ==0)
	{
		return;
	}*/
	ps->size--;
}
