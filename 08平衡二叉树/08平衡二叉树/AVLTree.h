#pragma once
template<class K,class V>
struct AVLTreeNode 
{
	//�洢�ļ�ֵ��
	pair<K, V> _kv;

	//ƽ�����ӣ�balance factor��
	int _bf;

	//�洢��������
	AVLTreeNode<K, V>* _parent;//�����ҵ����ڵ�
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;

	//���캯��
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

		Node* cur = _root;//ָ��ǰ�ڵ��λ��
		Node* parent = nullptr;//��ǰ�ڵ�ĸ��ڵ�

		//�ҵ�����λ��
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
		//���Ӳ�����
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

		while (parent)//��ԶҪ���µ����ڵ�
		{
			if (parent->_bf == 0) {
				break;
			}
			else if (abs(parent->_bf) == 1)
			{
				cur = cur->_parent;
				parent = parent->_parent;//���ϲ���
			}
			else if(abs(parent->_bf)==2)
			{
				//�ж�����һ����ת���
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
				//��������ߵ����˵���ڴ�֮ǰ���в�ƽ�������
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
			if (cur->_kv.first < key) // keyֵ���ڸý���ֵ
			{
				cur = cur->_left; // �ڸý������������в���
			}
			else if (cur->_kv.first < key) // keyֵС�ڸý���ֵ
			{
				cur = cur->_right; // �ڸý������������в���
			}
			else // ��ǰ�ڵ��ֵ����keyֵ
			{
				return cur; //���ظý��
			}
		}
		return nullptr; //����ʧ��
	}

	bool Erase(const K& key)
	{
		//���ڱ���������
		Node* cur = parent;
		Node* parent = nullptr;

		//���ڱ��ʵ��ɾ���Ľڵ�͸��ڵ�
		Node* deletePos = nullptr;
		Node* deleteparentPos = nullptr;

		//ȷ��ɾ���ڵ�
		while (cur) {
			if (key < cur->_kv.first) {
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_kv.first) {
				parent = cur;
				cur = cur->_right;
			}
			else//�����˴�ɾ���Ľڵ�
			{
				if (cur->_left == nullptr)//�����ɾ���ڵ��������Ϊ��
				{
					if (cur == _root)//�����ɾ���ڵ��Ǹ��ڵ�
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
						break;//�����Ƚڵ�˵��Ҫ����ƽ������
					}
				}
				else if (cur->_right == nullptr)//�����ɾ���ڵ��������Ϊ��
				{
					if (cur == _root)//�����ɾ���ڵ��Ǹ��ڵ�
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
						break;//�����Ƚڵ�˵��Ҫ����ƽ������
					}
				}
				else//�����ɾ���ڵ��������������Ϊ�գ��滻��ɾ��
				{
					//�滻��ɾ��
					//Ѱ�Ҵ�ɾ���ڵ���������keyֵ��С�Ľڵ���Ϊʵ��ɾ���ڵ㣨ת��Ϊ������Ϊ�յľ��棩
					Node* minparent = cur;
					Node* minright = cur->_right;
					while (minright->_left)
					{
						minparent = minright;
						minright = minright->_left;
					}
					//����ɾ���ڵ�����Ը���Ϊ��������keyֵ��С�ڵ������
					cur->_kv.first = minright->_kv.first;
					cur->_kv.second = minright->_kv.second;

					//�����������keyֵ��С�Ľڵ�Ϊɾ���ڵ�
					deleteparentPos = minparent;
					deletePos = minright;
					break;
				}
			}
		}

		//���deletePosû�и���,˵��û���ҵ����ڵ�
		if (deletePos == nullptr)
		{
			return false;
		}

		//��¼��ɾ���ڵ㼰�丸�ڵ�(ʵ��ɾ��ʱҪ��)
		cur->_kv.first = minright->_kv.first;
		Node* del = deletePos;
		Node* delparent = deleteparentPos;

		//����ƽ������
		while (deletePos != _root)//����Ҫһֱ���µ����ڵ�
		{
			//�ж�ɾ�����Ǹ��׵���һ�ߣ�Ȼ�����ƽ������
			if (deletePos = deleteparentPos->_left) {
				deleteparentPos->_bf++;
			}
			else
			{
				deleteparentPos->_bf--;
			}

			//�ж��Ƿ���Ҫ���ϼ�������
			if (abs(deleteparentPos->_bf) == 1) {
				break;
			}
			else if (deleteparentPos->_bf == 0) //��������������ĸ߶ȶ���仯����Ҫ�������ϸ���ƽ������
			{
				deletePos = deleteparentPos;
				deleteparentPos = deleteparentPos->_parent;
			}
			else if (abs(deleteparentPos->_bf) == 2)//��Ҫ������ת����
			{
				//�ж���ת���
				if (deleteparentPos->_bf = -2)
				{
					if (deleteparentPos->_left->_bf == -1) {
						Node* tmp = deleteparentPos->_left;//��¼��ת���µĸ��ڵ�
						rotateR(deleteparentPos);
						deleteparentPos = tmp;//��ת����ڵ����
					}
					else if(deleteparentPos->_left->_bf == 1) {
						Node* tmp = deleteparentPos->_left->_right;//��¼��ת���µĸ��ڵ�
						rotateLR(deleteparentPos);
						deleteparentPos = tmp;//��ת����ڵ����
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

			//delParentPos���ĸ߶ȱ仯����Ӱ���丸����ƽ�����ӣ���Ҫ�������ϸ���ƽ������
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

		//1.����subRL��parent֮��Ĺ�ϵ
		//����������
		parent->_right = subRL;
		if (subRL) {
			subRL->_parent = parent;
		}

		//2.����subR��parent֮��Ĺ�ϵ
		//������������������
		subR->_left = parent;
		parent->_parent = subR;

		//3.����pparent��subR֮��Ĺ�ϵ
		//����һ���ڵ㽨������
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

		//����ƽ������
		parent->_bf = 0;
		subR->_bf = 0;
	}


	void rotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* pparent = parent->_parent;


		//����
		parent->_left = subLR;
		if (subLR) {
			subLR->_parent = parent;
		}

		//������������������
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
		//parent����Ϊ��С��ƽ�������ĸ�������Ҫ����ת�Ժ����¸�ֵ
		rotateR(parent);
		
		//�����bfֵ�ɵ���ǰsubLR��bfֵ����
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