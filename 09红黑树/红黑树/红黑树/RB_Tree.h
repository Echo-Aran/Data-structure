#pragma once
#include<iostream>
using namespace std;

enum Color_Type
{
	Red,
	Black
};


template<class K,class V>
struct RBTreeNode
{
	pair<K, V> _kv;

	RBTreeNode* _parent;
	RBTreeNode* _left;
	RBTreeNode* _right;
	Color_Type _color;

	RBTreeNode(const pair<K, V> kv)
		: _kv(kv)
		, _parent(nullptr)
		, _left(nullptr)
		, _right(nullptr)
		, _color(Red)
	{}
		
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
private:
	Node* _root;
public:
	RBTree()
		:_root(nullptr)
	{}

	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_color = Black;
			return true;
		}

		Node* cur = _root;//ָ��ǰ�ڵ��λ��
		Node* parent = nullptr;//��ǰ�ڵ�ĸ��ڵ�

		//�ҵ�����λ��
		while (cur)
		{
			if (cur->_kv.first < kv.first) {
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first) {
				parent = cur;
				cur = cur->_left;
			}
			else {
				return false;
			}
		}

		cur = new Node(kv);
		cur->_color = Red;
		
		if (cur->_kv.first < parent->_kv.first) {
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

		//���ڵ�Ϊ��ɫ���������������
		while (parent && parent->_color == Red)
		{
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_color == Red)
				{
					// ��ɫ
					parent->_color = uncle->_color = Black;
					grandfather->_color = Red;

					// �������ϴ���
					cur = grandfather;
					parent = cur->_parent;
				}
				else//uncle�����ڻ�uncleΪ��
				{
					if (cur == parent->_left)
					{
						//	  g
						//	p
						//c
						rotateR(grandfather);
						parent->_color = Black;
						grandfather->_color = Red;
					}
					else
					{
						//	g
						//p	
						//	c
						rotateL(parent);
						rotateR(grandfather);
						cur->_color = Black;
						grandfather->_color = Red;
					}
					break;
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				// u������Ϊ��
				if (uncle && uncle->_color == Red)
				{
					// ��ɫ
					parent->_color = uncle->_color = Black;
					grandfather->_color = Red;

					// �������ϴ���
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_right)
					{
						// g
						//	  p
						//       c
						rotateL(grandfather);
						grandfather->_color = Red;
						parent->_color = Black;
					}
					else
					{
						// g
						//	  p
						// c
						rotateR(parent);
						rotateL(grandfather);
						cur->_color = Black;
						grandfather->_color = Red;
					}
					break;
				}
			}
		}

		_root->_color = Black;
		return true;
	}
	
	bool IsBalance()
	{
		return _IsBalance(_root);
	}

	int Height()
	{
		return _Height(_root);
	}

	bool checkColor(Node* root, int blacknum, int basenum)
	{
		if (root == nullptr)
		{
			if (blacknum != basenum)
			{
				return false;
			}
			return true;
		}

		if (root->_color == Black)
		{
			++blacknum;
		}

		if (root->_parent && root->_parent->_color == Red && root->_color == Red)
		{
			cout << root->_kv.first << "����������ɫ�ڵ�" << endl;
			return false;
		}

		return  checkColor(root->_left, blacknum, basenum) && checkColor(root->_right, blacknum, basenum);
	}
private:
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* pparent = parent->_parent;

		/*1.����subRL��parent֮��Ĺ�ϵ
		����������*/
		parent->_right = subRL;
		if (subRL) {
			subRL->_parent = parent;
		}

		//2.����subR��parent֮��Ĺ�ϵ
		//������������������
		subR->_left = parent;
		parent->_parent = subR;

		/*3.����pparent��subR֮��Ĺ�ϵ
		����һ���ڵ㽨������*/
		if (parent == _root)
		{
			_root = subR;
			subR->_parent == nullptr;
		}
		else
		{
			subR->_parent = pparent;
			if (parent == pparent->_left) {
				pparent->_left = subR;
			}
			else {
				pparent->_right = subR;
			}
		}

		/*����ƽ������*/
		parent->_bf = 0;
		subR->_bf = 0;
	}
	void RotateR(Node* parent)
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

		if (parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			subL->_parent = pparent;
			if (parent == pparent->_left) {
				pparent->_left = subL;
			}
			else {
				pparent->_right = subL;
			}

		}

		parent->_bf = subL->_bf = 0;
	}
	
	int _Height(Node* root)
	{
		if (!root) {
			return 0;
		}
		int left = _Height(root->_left);
		int right = _Height(root->_right);

		return left > right ? left + 1 : right + 1;
	}
	bool _IsBalance(Node* root)
	{
		if (root == nullptr)
		{
			return true;
		}
		if (root->_color != Black)
		{
			return false;
		}

		int basenum = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_color == Black) {
				++basenum;
			}
			cur = cur->_left;
		}

		return checkColor(root, 0, basenum);
	}

};