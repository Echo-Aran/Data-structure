#include "RB_tree.h"
#include<vector>

int main()
{
	const int N = 10;
	vector<int> v;
	v.reserve(N);
	srand(time(0));

	for (size_t i = 0; i < N; i++)
	{
		v.push_back(i);
	}

	for (auto i : v)
	{
		cout << i << " ";
	}
	cout << endl;

	RBTree<int, int> rbt;
	for (auto e : v)
	{
		rbt.Insert(make_pair(e, e));
		cout << "Insert:" << e << endl;
	}
	
	cout << rbt.Height() << endl;
	if (rbt.IsBalance())
	{
		cout << "ok" << endl;

	}
	
	return 0;
}