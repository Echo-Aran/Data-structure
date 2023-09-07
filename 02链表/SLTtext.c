#include"SList.h"
void Test01()
{
	SLTNode* plist = NULL;
	SLTPushFront(&plist,1);
	SLTPushFront(&plist, 2);
	SLTPushFront(&plist, 3);
	SLTPushFront(&plist, 4);
	SLTPrint(plist);


	/*SLTpopBack(plist);
	SLTPrint(plist);
	SLTpopBack(plist);
	SLTPrint(plist);
	SLTpopBack(plist);
	SLTPrint(plist);*/

	SLTPopBack(&plist);
	SLTPrint(plist);
	SLTPopBack(&plist);
	SLTPrint(plist);
	SLTPopBack(&plist);
	SLTPrint(plist);
	SLTPopBack(&plist);
	SLTPrint(plist);

}
void Test02()
{
	SLTNode* plist = NULL;
	SLTPushFront(&plist, 1);
	SLTPushFront(&plist, 2);
	SLTPushFront(&plist, 3);
	SLTPushFront(&plist, 4);
	SLTPrint(plist);

	SLTPopFront(&plist);
	SLTPrint(plist);
	SLTPopFront(&plist);
	SLTPrint(plist);
	SLTPopFront(&plist);
	SLTPrint(plist);
	SLTPopFront(&plist);
	SLTPrint(plist);

}

void Test03()
{
	SLTNode* plist = NULL;
	SLTPushFront(&plist, 1);
	SLTPushFront(&plist, 2);
	SLTPushFront(&plist, 3);
	SLTPushFront(&plist, 4);
	SLTPrint(plist);
	/*FindSLTNode(plist, 3);*/ //使用完以后函数栈帧销毁
	/*SLTNode* pos = FindSLTNode;*/
	SLTNode* pos = FindSLTNode(plist, 3);
	SLTInsertAfter(pos, 3);
	SLTPrint(plist);
	SLTEraseAfter(pos);
	SLTPrint(plist);
	SLTDestroy(&plist);
	SLTPrint(plist);
}
int main()
{
	Test01();
	Test02();
	Test03();

	return 0;
}