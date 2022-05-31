#include <iostream>
#include <assert.h>
#include <vector>

using namespace std;

class Node // ����� ����
{
private:
	int key;
	Node* left, * right;
public:
	friend class BinaryTree;
	Node()// ����������� �� ���������
	{
		key = 0;
		left = NULL;
		right = NULL;
	}
	Node(int k)// ����������� �� ��������� c key (��� ����� ������),key - ���� ����(�����)
	{
		key = k;
		left = NULL;
		right = NULL;
	}
	Node(int k, Node* l, Node* r)// ����������� � �����������, ��� key - ���� ���� (�����), l - ��������� �� ����� �����, r - �� ������
	{
		key = k;
		left = l;
		right = r;
	}
	bool emptyNode(Node * temp)
	{
		if (key == 0 && left == NULL && right == NULL)
			return 1;
		return 0;
	}
	int Key() //����������� �����
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
	BinaryTree()
	{
		Node* temp;
		root = temp;
	}
	BinaryTree(Node *temp)
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
	int height() //�-��� ���������� ������ ������
	{
		return heightNode(root);
	}
	int heightNode(Node* temp) //�-��� ���������� ������ ����
	{
		if (temp == NULL) return 0; //� ������ �������� � ����� ��������������� ������
		int h_l = heightNode(temp->left); //� ������ ������ ��������� ������� ��������� �������� ������ ������ �������
		int h_r = heightNode(temp->right); //� ������ ������� ��������� ������� ��������� �������� ������ ������� �������
		if (h_l > h_r) return h_l + 1; //���� ������ ������ ������� ������ �������, �� ������ ����� ������� ��������� �������������� �� 1 ������
		return h_r + 1; //����� ������ ����� ������� ��������� ������ ������ ������� ��������� �� 1
	}
	void levels() //������� ������ ������ � �������� ��������� � �-��� ������ �� �������
	{
		int u = height();
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
	BinaryTree& operator= (BinaryTree& temp)//�������� ����������
	{
		if (this == &temp) return *this;
		else
		{
			clear(this->root);
			copy(temp.root, this->root);
			return *this;
		}
	}
	Node* findNode(int k)//�-��� ���������� ����
	{
		Node* p = findNode(root, k);//���������� ������ ����, ���� NULL
		return p;//���������� ����
	}
	Node* findNode(Node* temp, int k)//�-��� ���������� ����
	{
		if (temp == NULL) 
			return temp;//���� ���� ����, ������������ 
		if (k == temp->key) 
			return temp;//���� ������� �������� ��������� � ������ �������� ����, �� ����� ���, ���������� ���
		if (k < temp->key) 
			temp = findNode(temp->left, k);//���� ������� �������� ������ ����� �������� ����, ��� � ����� ���������
		else 
			if (k > temp->key) 
				temp = findNode(temp->right, k);//����� � ������ ���������
		return temp;//���������� ��������� �������
	}
	bool delNode(int k)//�-��� �������� ����
	{
		Node* temp = findNode(k), * r = root;//���� ���� � ������ 
		if (temp == NULL) return 0;
		if (temp == root)
		{
			root = delNode(temp);
			return 1;
		}
		while ((r->left != temp) && (r->right != temp))//���� �� �� ����� ���� �� ����� �� ���������� ����:
		{
			if (r->key > temp->key)r = r->left;//���� �������� �������� ���� ������ ������� ����, ��������� �����
			else r = r->right; //����� ������
		}
		if (r->left == temp) r->left = delNode(temp);//���� ����� ������� �������� ���� = �������, � ������ ������� ���������� ��������� �������� ���� q
		else r->right = delNode(temp);//�����, � ������� �������
		return 1;
	}
	Node* delNode(Node* temp)//�������� ���� �� ������
	{
		Node* s, * r=temp;//s ����� �������� �������� ����, r-�������
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
	Node* rootFind() //����������� �����
	{
		return root;
	}
	void printTree(int l, Node* temp)// ����� ������ � �������
	{
		if (temp == NULL) return;
		printTree(l + 3, temp->right);
		for (int k = 0; k < l; k++) cout << " ";
		cout.width(2);
		cout << temp->key << "\n";
		printTree(l + 3, temp->left);
	}
	int count()//���������� ���������� �����
	{
		return countNode(root);
	}
	int countNode(Node* temp)//�������� ������� ����������� �����
	{
		if (temp == NULL) //���� ����� �� ���� ������, �������� 1
			return 0;
		int c_l = countNode(temp->left);//������� ����� �����
		int c_r = countNode(temp->right);//������� ������ �����
		return c_l + c_r+1;//����� ���������� ������ � �����
	}
	int inVector(vector<int> v) //������� ������ ������ ������� n � ���������� ����� ����� � ������
	{
		int k = 0; //�������� �������
		inVector_auxiliary(root, v, k); //�������� �������� ������� ���������� �������������� �������
		return k; //���������� ����� ��������� � �������
	}
	void inVector_auxiliary(Node* p, vector<int> v, int& k)// ��������� ������
	{
		if (p == NULL) 
			return;//���� ���� ����, ��������� ������, ������������
		inVector_auxiliary(p->left, v, k);//���������� ������ �����, ���� �� ����� �� �����
		v.at(k) = p->key;//������� � ������ �������� �����
		k++; //����������� ������� ���������
		inVector_auxiliary(p->right, v, k);//���������� ������ ������ � ����������
	}
	bool isEmpty()//���������� true, ���� ������ ������
	{
		if (root->key == 0 && root->left == NULL && root->right == NULL)
			return 1;
		return 0;
	}
	//��������������� ������� ��� ����� � ������ (������������ ������ ������ ������)
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
	BinaryTree add_node(int x)//���������� ���� � ������
	{
		root = add_node(root, x);//���������� ������ � ��������� ����������� � �������� � �.�.
		return *this;//���������� �������� ������
	}
	Node* add_node(Node* temp, int x)//�-��� ���������� ���� � ������
	{
		if (temp == NULL) //���� ���� ����, �� ��������� ��� ���� � ��� �����
		{
			Node* temp = new Node(x);//������ ����, ��������� ����������� �� ���������(�-�������� ����� ������ ����)
			return temp;//���������� ����
		}
		if (x <= temp->key)
			temp->left = add_node(temp->left, x);//���� �������� ������������ ���� ������ ���� ����� ��������, ���������� ������ � ����� ���������
		else
			temp->right = add_node(temp->right, x);//����� ���� �������� ������������ ���� ������ ��������, ���������� ������ � ������ ���������
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
int main()
{
	setlocale(LC_ALL, "Russian");
	int n = 13;
	int mas[13] = { 5,3,8,4,7,45,6,23,8,9,5,2,20 };
	BinaryTree BT(mas,n);
	Node* root = BT.rootFind();
	BT.printTree(0,root);
	cout << endl;
	cout << "������ ������: ";
	if (BT.isEmpty())
		cout << "true";
	else
		cout << "false";
	cout << endl<< "������ ������: ";
	int x = BT.height();
	cout << x << endl;
	cout << "������ ���� � ������ 3, ������: ";
	if (BT.delNode(3))
		cout << "true";
	else
		cout << "false";
	cout << endl;
	BT.printTree(0, root);
	cout<< endl;
	cout<< "���������� �����: "<< BT.count();
	return 0;
}