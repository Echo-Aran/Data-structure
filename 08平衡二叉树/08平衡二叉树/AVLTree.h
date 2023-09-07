#pragma once
template<class K,class V>
struct AVLTreeNode 
{
	//存储的键值对
	pair<K, V> _kv;

	//平衡因子（balance factor）
	int _bf;

	//存储的三叉链
	AVLTreeNode<K, V>* _parent;//方便找到父节点
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;

	//构造函数
	AVLTreeNode(const pair<K, V>& kv)
		:_kv(kv)
		, _parent(nullptr)
		, _left(nullptr)
		, _right(nullptr)
		, _bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
private:
	Node* _root;

public:
	AVLTree()
		:_root(nullptr)
	{}

	bool Insert(const pair<K,V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}

		Node* cur = _root;//指向当前节点的位置
		Node* parent = nullptr;//当前节点的父节点

		//找到插入位置
		while (cur)
		{
			if (cur->_kv.first < kv.first) {
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_kv.first > kv.first) {
				parent = cur;
				cur = cur->_right;
			}
			else {
				return false;
			}
		}

		cur = new Node(kv);
		//链接并更新
		if (cur->_kv.first < parent->_kv.first) {
			parent->_left = cur;
			cur->_parent = parent;
			parent->_bf--;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
			parent->_bf++;
		}

		while (parent)//最远要更新到根节点
		{
			if (parent->_bf == 0) {
				break;
			}
			else if (abs(parent->_bf) == 1)
			{
				cur = cur->_parent;
				parent = parent->_parent;//向上查找
			}
			else if(abs(parent->_bf)==2)
			{
				//判断是哪一种旋转情况
				if (parent->_bf==2&&cur->bf==1)
				{
					rotateL(parent);
				}
				else if (parent->_bf == -2 && cur->bf == -1)
				{
					rotateR(parent);
				}
				else if (parent->_bf == -2 && cur->bf == 1)
				{
					rotateLR(parent);
				}
				else if (parent->_bf == 2 && cur->bf == -1)
				{
					rotateRL(parent);
				}
				break;

			}
			else
			{
				//如果程序走到这里，说明在此之前就有不平衡的子树
				assert(false);
			}
		}

		return true;
	}

	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < key) // key值大于该结点的值
			{
				cur = cur->_left; // 在该结点的右子树当中查找
			}
			else if (cur->_kv.first < key) // key值小于该结点的值
			{
				cur = cur->_right; // 在该结点的左子树当中查找
			}
			else // 当前节点的值等于key值
			{
				return cur; //返回该结点
			}
		}
		return nullptr; //查找失败
	}

	bool Erase(const K& key)
	{
		//用于遍历二叉树
		Node* cur = parent;
		Node* parent = nullptr;

		//用于标记实际删除的节点和父节点
		Node* deletePos = nullptr;
		Node* deleteparentPos = nullptr;

		//确定删除节点
		while (cur) {
			if (key < cur->_kv.first) {
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_kv.first) {
				parent = cur;
				cur = cur->_right;
			}
			else//遇到了待删除的节点
			{
				if (cur->_left == nullptr)//如果待删除节点的左子树为空
				{
					if (cur == _root)//如果待删除节点是根节点
					{
						_root = cur->_right;
						if (_root) {
							_root->_parent = nullptr;
						}
						delete cur;
						return true;
					}
					else
					{
						deleteparentPos = parent;
						deletePos = cur;
						break;//有祖先节点说明要更新平衡因子
					}
				}
				else if (cur->_right == nullptr)//如果待删除节点的右子树为空
				{
					if (cur == _root)//如果待删除节点是根节点
					{
						_root = cur->_left;
						if (_root) {
							_root->_parent = nullptr;
						}
						delete cur;
						return true;
					}
					else
					{
						deleteparentPos = parent;
						deletePos = cur;
						break;//有祖先节点说明要更新平衡因子
					}
				}
				else//如果待删除节点的左右子树都不为空，替换法删除
				{
					//替换法删除
					//寻找待删除节点右子树中key值最小的节点作为实际删除节点（转化为左子树为空的局面）
					Node* minparent = cur;
					Node* minright = cur->_right;
					while (minright->_left)
					{
						minparent = minright;
						minright = minright->_left;
					}
					//将待删除节点的属性更新为右子树中key值最小节点的属性
					cur->_kv.first = minright->_kv.first;
					cur->_kv.second = minright->_kv.second;

					//标记右子树中key值最小的节点为删除节点
					deleteparentPos = minparent;
					deletePos = minright;
					break;
				}
			}
		}

		//如果deletePos没有更新,说明没有找到根节点
		if (deletePos == nullptr)
		{
			return false;
		}

		//记录待删除节点及其父节点(实际删除时要用)
		cur->_kv.first = minright->_kv.first;
		Node* del = deletePos;
		Node* delparent = deleteparentPos;

		//更新平衡因子
		while (deletePos != _root)//可能要一直更新到根节点
		{
			//判断删除的是父亲的哪一边，然后更新平衡因子
			if (deletePos = deleteparentPos->_left) {
				deleteparentPos->_bf++;
			}
			else
			{
				deleteparentPos->_bf--;
			}

			//判断是否需要往上继续更新
			if (abs(deleteparentPos->_bf) == 1) {
				break;
			}
			else if (deleteparentPos->_bf == 0) //其他两种情况树的高度都会变化所以要继续往上跟新平衡因子
			{
				deletePos = deleteparentPos;
				deleteparentPos = deleteparentPos->_parent;
			}
			else if (abs(deleteparentPos->_bf) == 2)//需要进行旋转处理
			{
				//判断旋转情况
				if (deleteparentPos->_bf = -2)
				{
					if (deleteparentPos->_left->_bf == -1) {
						Node* tmp = deleteparentPos->_left;//记录右转后新的根节点
						rotateR(deleteparentPos);
						deleteparentPos = tmp;//旋转后根节点更新
					}
					else if(deleteparentPos->_left->_bf == 1) {
						Node* tmp = deleteparentPos->_left->_right;//记录右转后新的根节点
						rotateLR(deleteparentPos);
						deleteparentPos = tmp;//旋转后根节点更新
					}
					else//deleteparentPos->_left->_bf = 0
					{
						Node* tmp = deleteparentPos->_left;
						rotateR(deleteparentPos);
						deleteparentPos = tmp;
						deleteparentPos->_bf = 1;
						deleteparentPos->_right->_bf = -1;
						break;
					}
				}
				else//deleteparentPos->_bf = 2
				{
					if (deleteparentPos->_right->_bf == 1)
					{
						Node* tmp = deleteparentPos->_right->_left;
						rotateRL(deleteparentPos);
						deleteparentPos = tmp;
					}
					else if (deleteparentPos->_right->_bf == -1)
					{
						Node* tmp = deleteparentPos->_right;
						rotateL(deleteparentPos);
						deleteparentPos = tmp;
					}
					else
					{
						Node* tmp = deleteparentPos->_right;
						rotateL(deleteparentPos);
						deleteparentPos = tmp;
						deleteparentPos->_bf = -1;
						deleteparentPos->_left->_bf = 1;
						break;
					}
				}

			}
			else {
				assert(false);
			}

			//delParentPos树的高度变化，会影响其父结点的平衡因子，需要继续往上更新平衡因子
			deletePos = deleteparentPos;
			deleteparentPos = deleteparentPos->_parent;

		}

		if (del->_left == nullptr) {
			if (del = delparent->_left) {
				delparent->_left = del->_right;
				if (del->_right) {
					del->_right->_parent = delparent;
				}
			}
			else {
				delparent->_right = del->_right;
				if (del->_right) {
					del->_right->_parent = delparent;
				}
			}
		}
		else{
			if (del == delparent->_left) {
				delparent->_left = del->_left;
				if (del->_left) {
					del->_left->_parent = delparent;
				}
			}
			else {
				delparent->_right = del->_left;
				if (del->_left) {
					del->_left->_parent = delparent;
				}
			}
		}
		delete del;
		return true;

	}

	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}

	void Height()
	{
		_Height(_root);
	}

	bool IsBalancedTree()
	{
		_IsBalancedTree(_root);
	}

private:
	void rotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* pparent = parent->_parent;

		//1.建立subRL与parent之间的关系
		//左子树滑动
		parent->_right = subRL;
		if (subRL) {
			subRL->_parent = parent;
		}

		//2.建立subR和parent之间的关系
		//更新右子树的左子树
		subR->_left = parent;
		parent->_parent = subR;

		//3.建立pparent和subR之间的关系
		//与上一个节点建立连接
		if (parent == _root)
		{
			_root = subR;
			subR->_parent == nullptr;
		}
		else
		{
			subR->_parent = pparent;
			if (parent = pparent->_left) {
				pparent->_left = subR;
			}
			else{
				pparent->_right = subR;
			}
		}

		//更新平衡因子
		parent->_bf = 0;
		subR->_bf = 0;
	}


	void rotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* pparent = parent->_parent;


		//滑动
		parent->_left = subLR;
		if (subLR) {
			subLR->_parent = parent;
		}

		//更新左子树的右子树
		subL->_right = parent;
		parent->_parent = subL;

		if (parent == _root){
			_root = subL;
			subL->_parent = nullptr;
		}
		else {
			subL->_parent == pparent;
			if (parent = pparent->_left) {
				pparent->_left = subL;
			}
			else{
				pparent->_right = subL;
			}
		}
		parent->_bf = 0;
		subL->_bf = 0;
	}

	void rotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		int bf = subLR->_bf;
	
		rotateL(subL);
		//parent并不为最小不平衡子树的根，所以要在旋转以后重新赋值
		rotateR(parent);
		
		//各点的bf值由调整前subLR的bf值决定
		if (_bf == 0) {
			parent->_bf = 0;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	void rotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		rotateR(subR);
		rotateL(parent);

		if (_bf == 0) {
			parent->_bf = 0;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
		else
		{
			assert(false);
		}

	}

	void _Inorder(Node* root)
	{
		if (!root) {
			return;
		}
		_Inorder(root->_left);
		cout << root->_kv.first << " ";
		_Inorder(root->_right);
	}

	void _Height(Node* root)
	{
		if (!root) {
			return 0;
		}
		int left = _Height(root->_left);
		int right = _Height(root->_right);
		
		return left > right ? left + 1 : right + 1;
	}

	bool _IsBalancedTree(Node* root) 
	{
		if (!root) {
			return true;
		}

		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		int diff = rightHeight - leftHeight;

		if (abs(diff) > 2) {
			cout << "wrong" << endl;
			return false;
		}
		else if (diff != root->_bf) {
			return  false;
		}

		return _IsBalancedTree(root->_left) && _IsBalancedTree(root->_right);
	}
};