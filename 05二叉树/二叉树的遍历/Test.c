#include <stdio.h>
#include<assert.h>
#include<stdlib.h>
#include"Queue.h"

typedef int BTDataType;
typedef struct BinaryTreeNode
{
	BTDataType data;
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
}BTNode;  //左子树，右子树 根

BTNode* BuyNode(BTDataType x)
{
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	if (node == NULL)
	{
		perror("malloc fail");
		return NULL;
	}
	node->data = x;
	node->left = node->right = NULL;

	return node;//创建临时变量返回，可以减少传参，直接构建
}
BTNode* CreateTree()//创建树 并返回根
{
	BTNode* node1 = BuyNode(1);
	BTNode* node2 = BuyNode(2);
	BTNode* node3 = BuyNode(3);
	BTNode* node4 = BuyNode(4);
	BTNode* node5 = BuyNode(5);
	BTNode* node6 = BuyNode(6);

	node1->left = node2;
	node1->right = node4;
	node2->left = node3;
	node4->left = node5;
	node4->right = node6;

	return node1;

}
void PreOrder(BTNode* root)
{
	if (root==NULL)
	{
		printf("NULL ");
		return;//缺少return 则为空指针
	}
	printf("%d ", root->data);
	PreOrder(root->left);     //根全部找完
	PreOrder(root->right);

}
void InOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	InOrder(root->left);
	printf("%d ", root->data);
	InOrder(root->right);

}
void PostOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	
	PostOrder(root->left);
	PostOrder(root->right);
	printf("%d ", root->data);
}
//int TreeSize(BTNode*root)
//{
//	return root==NULL ? 0 : TreeSize(root->left) + TreeSize(root->right) + 1;
//}
int TreeSize(BTNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	return TreeSize(root->left) + TreeSize(root->right) + 1;

}
//int TreeHeight(BTNode* root)
//{
//	if (root == NULL)
//	{
//		return 0;
//	}
//	return TreeHeight(root->left) > TreeHeight(root->right) 
//		  ? TreeHeight(root->left) + 1 : TreeHeight(root->right) + 1;
//}
int TreeHeight(BTNode* root)
{
	if (root == NULL)
	{
		return 0;
	}

	int leftheight = TreeHeight(root->left);
	int rightheight = TreeHeight(root->right);
	return leftheight > rightheight ? leftheight + 1 : rightheight + 1;

}
int TreeKlevel(BTNode* root, int k)
{
	if (root == NULL)
	{
		return 0;
	}
	if (k == 1)
	{
		return 1;
	}
	int leftK = TreeKlevel(root->left, k - 1);
	int rightK = TreeKlevel(root->right, k - 1);
	return leftK + rightK;
}
//BTNode* BinaryTreeFind(BTNode* root,BTDataType x)
//{
//	if (root == NULL)
//	{
//		return NULL;
//	}
//	if (root->data == x)
//	{
//		return root;
//	}
//	BinaryTreeFind(root->left,x);
//	BinaryTreeFind(root->right, x);
//
//}
BTNode* BinaryTreeFind(BTNode* root, BTDataType x)
{
	if (root == NULL)
		return NULL;
	if (root->data == x)
		return root;
	BTNode*lret=BinaryTreeFind(root->left, x);
	if (lret)
		return lret;
	BTNode* rret=BinaryTreeFind(root->right, x);
	if (rret)
		return rret;

	return NULL;
}
void BinaryTreeLevelOrder(BTNode* root)
{
	Queue q;
	QueueInit(&q);
	if (root)
		QueuePush(&q, root);
	while (!QueueEmpty(&q))
	{
		BTNode* front = QueueFront(&q);
		QueuePop(&q);
		printf("%d ", front->data);

		if (front->left)
			QueuePush(&q, front->left);
		if (front->right)
			QueuePush(&q, front->right);
	}
		
	QueueDestroy(&q);
}

bool BinaryTreeCompete(BTNode* root)
{
	Queue q;
	QueueInit(&q);
	if (root)
		QueuePush(&q, root);
	while (!QueueEmpty(&q))
	{
		BTNode* front = QueueFront(&q);
		if (front == NULL)
			break;
		QueuePop(&q);

		QueuePush(&q, front->left);
		QueuePush(&q, front->right);
	}
	//判断空是否连续
	while (!QueueEmpty(&q))
	{
		if (QueueFront(&q) == NULL)
			QueuePop(&q);
		else
			return false;
	}
	QueueDestroy(&q);

	return true;
}


int main()
{
	BTNode* root = CreateTree();

	PreOrder(root);
	printf("\n");

	InOrder(root);
	printf("\n");

	PostOrder(root);
	printf("\n");

	printf("%d\n",TreeSize(root));
	printf("%d\n", TreeHeight(root));
	printf("%p\n", BinaryTreeFind(root, 4));

	BinaryTreeLevelOrder(root);

	if (BinaryTreeCompete(root))
		printf("\ntrue");
	printf("\nfalse");
	return 0;
}