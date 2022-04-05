#include <iostream>
#include <assert.h>
using namespace std;

class Node // ����� ����
{
private:
	int key;
	Node* left, * right;
public:
	friend class BinaryTree;
	Node(int k = 0, Node* L = NULL, Node* R = NULL);// ����������� �� ���������
	int Key() 
	{ 
		return key; 
	}
	friend ostream& operator << (ostream& o, Node* t)//���������� ��������� �����
	{
		if (t == NULL) 
			cout << "������ ���� ���";
		else 
			cout << t->key;//����� �������� �����
		return o;
	}
};

class BinaryTree //����� �������� ������
{
private:
	Node* root; //��������� �� ������
public:
	BinaryTree(Node *temp)//����������� �����������
	{
		if (temp)
		{
			root = temp;
		}
		else
			root = NULL;
	}
	BinaryTree(int* a, int n) //����������� � ����� �����������, ��� �-������ ���������, n-���-�� ���������
	{
		root = NULL;
		for (int i = 0; i < n; i++)
		{
			root = add_node(root, a[i]);
		}
	}
	BinaryTree(BinaryTree& temp)
	{
		copy(temp.root, this->root);
	}
	~BinaryTree()
	{
		clear(root);
	}
	int Height() //�-��� ���������� ������ ������
	{
		return Height_node(root);
	}
	int Height_node(Node* temp) //�-��� ���������� ������ ����
	{
		if (temp == NULL) return 0; //� ������ �������� � ����� ��������������� ������
		int h_l = Height_node(temp->left); //� ������ ������ ��������� ������� ��������� �������� ������ ������ �������
		int h_r = Height_node(temp->right); //� ������ ������� ��������� ������� ��������� �������� ������ ������� �������
		if (h_l > h_r) return h_l + 1; //���� ������ ������ ������� ������ �������, �� ������ ����� ������� ��������� �������������� �� 1 ������
		return h_r + 1; //����� ������ ����� ������� ��������� ������ ������ ������� ��������� �� 1
	}
	void levels() //������� ������ ������ � �������� ��������� � �-��� ������ �� �������
	{
		int u = Height();
		for (int i = 0; i < u; i++) //�� ����� ������� ������ u ���
		{
			levels(root, i);//������� ����� ������� ����� �������
			cout << endl;// ���������
		}
	}
	void levels(Node* temp, int i) //�-��� ���������� ������� ������
	{
		if (temp == NULL) return; //���� ���� ������, ������������
		else
		{
			if (i == 0) //���� u=0, �� �� ����� �� ������� ������, ������� �������
			{
				cout << temp->key << "  ";
				return;
			}
			if (temp->left) levels(temp->left, i - 1); //��������� ������ ����� � ��������� ����� �������, ������� �������� ������ �� �������
			if (temp->right) levels(temp->right, i - 1); //��������� ������ ������ � ��������� ����� �������, ������� �������� ������ �� �������
		}
	}
	BinaryTree& operator= (BinaryTree& temp)
	{
		if (this == &temp) return *this;
		else
		{
			clear(this->root);
			copy(temp.root, this->root);
			return *this;
		}
	}
	Node* find_node(int k)//�-��� ���������� ����
	{
		Node* p = find_node(root, k);//���������� ������ ����, ���� NULL
		return p;//���������� ����
	}
	Node* find_node(Node* temp, int k)//�-��� ���������� ����
	{
		if (temp == NULL) 
			return temp;//���� ���� ����, ������������ 
		if (k == temp->key) 
			return temp;//���� ������� �������� ��������� � ������ �������� ����, �� ����� ���, ���������� ���
		if (k < temp->key) 
			temp = find_node(temp->left, k);//���� ������� �������� ������ ����� �������� ����, ��� � ����� ���������
		else 
			if (k > temp->key) 
				temp = find_node(temp->right, k);//����� � ������ ���������
		return temp;//���������� ��������� �������
	}
	BinaryTree del_node(int k)//�-��� �������� ����
	{
		Node* temp = find_node(k), * r = root;//���� ���� � ������ 
		if (temp == NULL) return *this;//���� �� �� ������� ���, ������ ������� ������, ���������� ������� ������
		if (temp == root)//���� ��������� ���� ��� ������, ������� ������ � �� ��� ����� ���������� ��������� �-��� �������� ���� �� ������
		{
			root = del_node(temp);
			return *this;//���������� ����� ������
		}
		while ((r->left != temp) && (r->right != temp))//���� �� �� ����� ���� �� ����� �� ���������� ����:
		{
			if (r->key > temp->key)r = r->left;//���� �������� �������� ���� ������ ������� ����, ��������� �����
			else r = r->right; //����� ������
		}
		if (r->left == temp) r->left = del_node(temp);//���� ����� ������� �������� ���� = �������, � ������ ������� ���������� ��������� �������� ���� q
		else r->right = del_node(temp);//�����, � ������� �������
		return *this;//���������� ����� ������
	}
	Node* del_node(Node* temp)//�������� ���� �� ������
	{
		Node* s, * r;//s ����� �������� �������� ����, r-�������
		if (temp->left == NULL && temp->right == NULL)//���� � ���������� ���� ��� ��������, ������ ���������� ���
		{
			delete temp;
			temp = NULL;
			return temp;
		}
		if (temp->right == NULL)//���� �� �� ����� ������� �������, �� �� ��� ����� ���������� ��� ����� �������
		{
			r = temp;
			temp = temp->left;
			delete r;
			return temp;
		}
		if (temp->left == NULL)//���� �� �� ����� ������ �������, �� �� ��� ����� ���������� ��� ������ �������
		{
			r = temp;
			temp = temp->right;
			delete r;
			return temp;
		}
		//���� ���� � ����� � ������ �������, �������� ��������� �� �������� ���� �� ������� ���������
		s = temp->right;
		if (s->left == NULL)//���� � ������� ������� ���������� ���� ��� ������ �������, ������ ������ ������� ���������� �� ����� ���������
		{
			temp->key = s->key;//�� ��������� ����������, �.�. �������� ������ � ����� ��������� ���������� ����, � ��� �����������
			temp->right = s->right;
			delete s;//������ ������ s
			return temp;
		}
		while (s->left != NULL)//���� ����� ������� ������� ��������� ���������� ���� �� ����, ��� ������ �������, �.�. ��������� ����� ���������� �� ��������
		{
			r = s; s = s->left;//r-������ s
		}
		temp->key = s->key;//������������� ����� ���� �� ����� ���������
		r->left = s->right;
		delete s;//������� ������
		return temp;
	}
	Node* Root() //����������� �����
	{
		return root;
	}
	void printTree(int l, Node* temp)
	{
		if (temp == NULL) return;
		printTree(l + 3, temp->right);
		for (int k = 0; k < l; k++) cout << " ";
		cout.width(2);
		cout << temp->key << "\n";
		printTree(l + 3, temp->left);
	}

	//��������������� ������� ��� ����� � ������ (������������ ������ ������ ������)
private:
	BinaryTree create(int n)//�-��� �������� ������
	{
		int k;//�������� � ���������� �������� ������
		cout << "������� ��������" << endl;
		for (int i = 0; i < n; i++)
		{
			cin >> k;
			root = add_node(root, k);//���������� ����� � ������
		}
		return *this;//����������� ��������� ������
	}
	BinaryTree add_node(int k)//���������� ���� � ������
	{
		root = add_node(root, k);//���������� ������ � ��������� ����������� � �������� � �.�.
		return *this;//���������� �������� ������
	}
	Node* add_node(Node* temp, int k)//�-��� ���������� ���� � ������
	{
		if (temp == NULL) //���� ���� ����, �� ��������� ��� ���� � ��� �����
		{
			Node* temp = new Node(k);//������ ����, ��������� ����������� �� ���������(�-�������� ����� ������ ����)
			return temp;//���������� ����
		}
		if (k <= temp->key)
			temp->left = add_node(temp->left, k);//���� �������� ������������ ���� ������ ���� ����� ��������, ���������� ������ � ����� ���������
		else
			temp->right = add_node(temp->right, k);//����� ���� �������� ������������ ���� ������ ��������, ���������� ������ � ������ ���������
		return temp;//���������� ����
	}
	void copy(Node* temp, Node*& root)
	{
		if (temp != NULL)
		{
			root = new Node;
			root->key = temp->key;
			root->left = NULL;
			root->right = NULL;
			copy(temp->left, root->left);
			copy(temp->right, root->right);
		}
	}
	void clear(Node* temp)
	{
		if (temp == NULL) return;
		clear(temp->left);
		clear(temp->right);
		delete temp;
		temp = NULL;
	}
};
void main()
{
	setlocale(LC_ALL, "Russian");
	
}