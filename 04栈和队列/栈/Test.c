#include"Stack.h"
void Test01()
{
	ST ps;
	Init(&ps);
	Push(&ps, 1);
	Push(&ps, 2);
	Push(&ps, 3);
	Push(&ps, 4);
	Push(&ps, 5);

	while (!Empty(&ps))
	{
		printf("%d ", Top(&ps));
		Pop(&ps);
	}

	Destroy(&ps);
}
void Test02()
{
	ST ps;
	Init(&ps);
	Push(&ps, 1);

	Push(&ps, 2);
	printf("%d ", Top(&ps));
	Pop(&ps);

	Push(&ps, 3);
	Push(&ps, 4);

	printf("%d ", Top(&ps));
	Pop(&ps);

	Push(&ps, 5);
	
	while (!Empty(&ps))
	{
		//³öÕ»+´òÓ¡
		printf("%d ", Top(&ps));
		Pop(&ps);
	}

	Destroy(&ps);
}
int main()
{
	/*Test01();*/
	Test02();
	return 0;
}