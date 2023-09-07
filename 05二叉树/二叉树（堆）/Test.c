#include"Heap.h"

int main()
{
	HP hp;
	HeapInit(&hp);
	HeapPush(&hp, 12);
	HeapPush(&hp, 31);
	HeapPush(&hp, 7);
	HeapPush(&hp, 65);
	HeapPush(&hp, 1);
	HeapPush(&hp, 2);
	HeapPush(&hp, 1);
	HeapPush(&hp, 24);
	HeapPush(&hp, 3);
	HeapPush(&hp, 5);

	int k = 0;
	scanf_s("%d", &k);
	while (!HeapEmpty(&hp)&&k--)
	{
		printf("%d ", HeapTop(&hp));
		HeapPop(&hp);
	}
	printf("\n");
	
	int a[9] = { 12,6,45,98,1,3,64,5,31 };
	PrintTopK(a, 9, 5);

	return 0;
}