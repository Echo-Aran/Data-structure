#pragma once
template<class T>
struct BSTreeNode
{
	BSTreeNode(const T& key)
		:_left(nullptr)
		,_right(nullptr)
		,_key(key)
	{}

	BSTreeNode* _left;
	BSTreeNode* _right;
	T _key;
};

template<class T>
class BSTree
{
	typedef BSTreeNode<T> Node;
public:
	BSTree()
		:_root(nullptr)
	{}

	BSTree(const BSTree<T>& t) {
		_Copy(t._root);
	}

	~BSTree() {
		Destroy(_root);
	}

	BSTree<T>& operator=(const BSTree<T> t)
	{
		swap(_root, t._root);
		return *this;
	}
	
	bool Insert(const T& val)
	{
		if (_root == nullptr)
		{
			_root = new Node(val);
			return true;
		}
		else
		{
			Node* cur = _root;
			Node* parent = nullptr;
			//cur�Ҳ���λ��
			while (cur)
			{
				if (val < cur->_key) {
					parent = cur;
					cur = cur->_left;
				}
				else if (val > cur->_key) {
					parent = cur;
					cur = cur->_right;
				}
				else {
					return false;
				}
			}
			//����
			cur = new Node(val);
			if (val < parent->_key) {
				parent->_left = cur;
			}
			else {
				parent->_right = cur;
			}
			return true;
		}
	}

	bool Find(const T& val)
	{
		Node* cur = _root;
		while (cur)
		{
			if (val < cur->_key) {
				cur = cur->_left;
			}
			else if (val > cur->_key) {
				cur = cur->_right;
			}
			else {
				return true;
			}

		}
		return false;
	}

	bool Erase(const T& val)
	{
		//�ҵ�λ��
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			//��һ��ѭ������Ҫɾ����λ��cur
			if (val < cur->_key) {
				parent = cur;
				cur = cur->_left;
			}
			else if (val > cur->_key) {
				parent = cur;
				cur = cur->_right;
			}
			else {
				//cur��Ŀ��ɾ��λ��
				//����Ϊ��
				if (cur->_left == nullptr) {
					if (cur->_key > parent->_key) {
						parent->_right = cur->_right;
					}
					else {
						parent->_left = cur->_right;
					}
				}//����Ϊ��
				else if(cur->_right==nullptr){
					if (cur->_key > parent->_key) {
						parent->_right = cur->_left;
					}
					else {
						parent->_left = cur->_left;
					}
				}
				//��������������������
				else {
					//�������������ֵ�����ң���������������Сֵ������
					Node* leftMax = cur->_left;
					parent = cur;//parent����û�н�ȥ

					while (leftMax->_right)
					{
						//����������������
						parent = leftMax;
						leftMax = leftMax->_right;
					}
					swap(leftMax->_key, cur->_key);

					//��һ��ʼû��ȥ�����������Ҫ�ж�����
					//parent->_right = leftMax->_right;
					if (parent->_left == leftMax) {
						parent->_left = leftMax->_left;
					}
					else {
						parent->_right = leftMax->_right;
					}
					
					cur = leftMax;
				}
				delete cur;
				return true;
			}
		}
		return false;
	}

	//�����ṩ�Ľӿ�
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	//ʵ��
	void _InOrder(Node* root)
	{
		if (root == nullptr) {
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	
	}

	bool InsertR(const T& val)
	{
		return _InsertR(_root, val);
	}

	bool FindR(const T& val)
	{
		return _FindR(_root, val);
	}

	bool EraseR(const T& val)
	{
		return _EraseR(_root, val);
	}

private:
	bool _EraseR(Node*& root,const T& val)
	{
		if (root == nullptr) {
			return false;
		}
		
		if (val > root->_key) {
			_EraseR(root->_right, val);
		}
		else if (val < root->_key) {
			_EraseR(root->_left, val);
		}
		else {
			Node* del = root;
			if (root->_left == nullptr) {
				root = root->_right;
			}
			else if(root->_right==nullptr) {
				root = root->_left;
			}
			else {

				Node* leftMax = root->_left;
				while (leftMax->_right)
				{
					leftMax = leftMax->_right;
				}
				swap(leftMax->_key, root->_key);

				_EraseR(root->_left, val);
			}
			delete del;
			return true;
		}

		return false;
	}

	bool _InsertR(Node*& root,const T& val)
	{
		if (root == nullptr) 
		{
			root = new Node(val);
			return true;
		}

		if (val < root->_key) {
			_InsertR(root->_left, val);
		}
		else if(val>root->_key){
			_InsertR(root->_right, val);
		}
		else {
			return false;
		}
	}

	bool _FindR(Node*& root, const T& val)
	{
		if (root == nullptr)
		{
			return false;
		}

		if (val < root->_key) {
			_FindR(root->_left, val);
		}
		else if (val > root->_key) {
			_FindR(root->_right, val);
		}
		else {
			return true;
		}
	}

	Node* _Copy(const Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		Node* copyroot = new Node(root->_key);
		copyroot->_left = _Copy(root->_left);
		copyroot->_right = _Copy(root->_right);
		return copyroot;
	}

	void Destroy(Node*& root)
	{
		if (root==nullptr) {
			return;
		}

		Destroy(root->_left);
		Destroy(root->_right);
		
		delete root;//
		root = nullptr;
	}

	Node* _root;
};