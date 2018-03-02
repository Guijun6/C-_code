#pragma once

template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode* _left;
	BinaryTreeNode* _right;
	T _data;

	BinaryTreeNode(const T& x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(const T* a, size_t size, const T& invalid)
	{
		cout << "B" << endl;
		size_t index = 0;
		_root = CreatTree(a, size, invalid, index);
	}

	//前序创建
	Node* CreatTree(const T* a, size_t size, const T& invalid, size_t& index)
	{
		Node* root = NULL;
		if ((a[index] != invalid) && index < size)
		{
			root = new Node(a[index]);
			root->_left = CreatTree(a, size, invalid, ++index);
			root->_right = CreatTree(a, size, invalid, ++index);
		}
		return root;
	}
	
	/*BinaryTree(const BinaryTree<T>& t)
	{
		size_t index = 0;
		_root = _CopyBinaryTree(t,index);
	}
	Node* _CopyBinaryTree(const BinaryTree<T>& t, size_t& index)
	{
		Node* root = NULL;
		if (index <= t.Size())
		{
			root = new Node((t._root + index)->_data);
			root->_left = _CopyBinaryTree(t, index++);
			root->_right = _CopyBinaryTree(t, index++);
		}
		return root;
	}*/

	BinaryTree& operator=(BinaryTree t)
	{
		_root = NULL;
		swap(_root, t._root);
		return *this;
	}
	~BinaryTree()
	{
		cout << "~B" << endl;
		_DestoryBinaryTree(_root);
		_root = NULL;
	}
	void _DestoryBinaryTree(Node* root)
	{
		if (root == NULL)
			return;
		_DestoryBinaryTree(root->_left);
		_DestoryBinaryTree(root->_right);
		delete root;
	}
	void PrevOrder()
	{
		//前序访问
		_PrevOrder(_root);
		cout << endl;
	}
	void _PrevOrder(Node* root)
	{
		if (root == NULL)
			return;
		cout << root->_data << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}
	void InOrder()
	{
		//中序
		_InOrder(_root);
		cout << endl;
	}
	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_data << " ";
		_InOrder(root->_right);
	}
	void PostOrder()
	{
		//后序访问
		_PostOrder(_root);
		cout << endl;
	}
	void _PostOrder(Node* root)
	{
		if (root == NULL)
			return;
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_data << " ";
	}

	//层序
	void LevelOrder()
	{
		queue<Node*> q;
		if (_root)
			q.push(_root);
		while (!q.empty())
		{
			Node* front = q.front();
			cout << front->_data << " ";
			q.pop();
			if (front->_left)
				q.push(front->_left);
			if (front->_right)
				q.push(front->_right);
		}
		cout << endl;
	}
	void PrevOrder_NonR()
	{
		Node* cur = _root;
		stack<Node*> s;
		while (cur || !s.empty())
		{
			while (cur)
			{
				cout << cur->_data << " ";
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			s.pop();
			cur = top->_right;
		}
		cout << endl;
	}
	void InOrder_NonR()
	{
		Node* cur = _root;
		stack<Node*> s;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			s.pop();
			cout << top->_data << " ";
			cur = top->_right;
		}
		cout << endl;
	}

	//有问题？第二次访问每个根节点的时候才能出栈
	void PostOrder_NonR()
	{
		Node* prev = NULL;
		Node* cur = _root;
		stack<Node*> s;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();
			s.pop();
			cur = top->_right;
			prev = top;
			if (cur == NULL || prev == cur->_right)
			{
				cout << prev->_data << " ";
			}
		}
		cout << endl;
	}

	size_t Size()
	{
		return _Size(_root);
	}
	size_t _Size(Node* root)
	{
		if (root == NULL)
			return 0;
		return _Size(root->_left) + _Size(root->_right) + 1;
	}
	size_t Size_2()
	{
		size_t size = 0;
		_Size_2(_root, size);
		return size;
	}
	void _Size_2(Node* root, size_t& size)
	{
		if (root == NULL) return;
		size++;
		_Size_2(root->_left, size);
		_Size_2(root->_right, size);
	}
	size_t Depth()
	{
		return _Depth(_root);
	}
	size_t _Depth(Node* root)
	{
		if (root == NULL) return 0;

		size_t left = _Depth(root->_left);
		size_t right = _Depth(root->_right);

		return left > right ? (left + 1) : (right + 1);
	}
	size_t LeafSize()
	{
		size_t size = 0;
		_LeafSize(_root, size);
		return size;
	}
	void _LeafSize(Node* root, size_t& size)
	{
		if (root == NULL) return;
		if ((root->_left == NULL) && (root->_right == NULL)) size++;
		_LeafSize(root->_left, size);
		_LeafSize(root->_right, size);
	}
	size_t LeafSize_2()
	{
		return _LeafSize_2(_root);
	}
	size_t _LeafSize_2(Node* root)
	{
		if (root == NULL) return 0;
		else if ((root->_left == NULL) && (root->_right == NULL)) return 1;
		return _LeafSize_2(root->_left) + _LeafSize_2(root->_right);
	}

	//有问题
	size_t GetKLevel(const size_t k)
	{
		if (k == 1)
			return 1;
		size_t i = 0;
		queue<Node*> q;
		if (_root)
			q.push(_root);
		while (i<k && !q.empty())
		{
			Node* front = q.front();
			q.pop();
			//cout << front->_data << " ";
			if (front->_left)
				q.push(front->_left);
			if (front->_right)
				q.push(front->_right);
			i++;
		}
		return q.size()-1;
	}
protected:
	Node* _root;
};
