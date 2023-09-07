#include"Queue.h"

int main()
{
	Queue p;
	QueueInit(&p);
	QueuePush(&p, 1);
	QueuePush(&p, 2);
	QueuePush(&p, 3);
	QueuePush(&p, 4);
	QueuePush(&p, 5);
	while (!QueueEmpty(&p))
	{
		printf("%d  ", QueueFront(&p));
		QueuePop(&p);
	}
	QueueDestroy(&p);
	return 0;
}