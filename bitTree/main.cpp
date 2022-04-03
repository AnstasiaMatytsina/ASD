#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
using namespace std;

class Node
{
protected:
public:
	friend class BinaryTree;
	Node(int k = 0, Node* P = NULL, Node* L = NULL, Node* R = NULL)//r
	{
		key = k; 
		parent = P; 
		left = L; 
		right = R;
	}
	int Key() 
	{ 
		return key; 
	}
private:
	int key;
	Node* parent, * left, * right;
};

class BinaryTree
{
public:
	Node* root;
	//Вспомогательные функции для формирования дерева
	Node* Tree(int n, Node* p) //построение поддерева из n узлов с корнем p, ключи случайны
	{
		if (n == 0)return NULL;
		Node* q = new Node(rand() % 100, p);
		int nL, nR;
		nL = (n - 1) / 2; nR = n - 1 - nL;
		q->left = Tree(nL, q);
		q->right = Tree(nR, q);
		return q;
	}
	Node* Tree(int n, Node* p, int& i, int* a)
	{
		if (!n) return NULL;
		int nL, nR;
		Node* q = new Node(a[i], p); i++;
		nL = (n - 1) / 2; nR = n - 1 - nL;
		q->left = Tree(nL, q, i, a);
		q->right = Tree(nR, q, i, a);
		return q;
	}
	//Основные методы
	BinaryTree(int* a, int n) //a-массив ключей
	{
		int i = 0;
		root = Tree(n, 0, i, a);
	}
	BinaryTree(BinaryTree& T)
	{
		if (T.root == NULL) root = NULL;
		else
		{
			root = new Node(T.root->key);
			Copy(T.root->left, root, 0);
			Copy(T.root->right, root, 1);
		}
	}
	BinaryTree& operator= (BinaryTree& T)
	{
		if (this != &T)
		{
			Clear();
			if (T.root == NULL) root = NULL;
			else
			{
				root->key = T.root->key;
				Copy(T.root->left, root, 0);
				Copy(T.root->right, root, 1);
			}
		}
		return *this;
	}
	BinaryTree() 
	{ 
		root = NULL; 
	}
	~BinaryTree()
	{
		Clear();
	}
	Node* Root() //Возвращение корня
	{
		return root;
	}
	void Clear()
	{
		DelUnderT(root);
	}
	void DelL(Node* p) //удаление листа в поддереве с корнем p
	{
		if (p != nullptr) {
			if (p->left == NULL && p->right == NULL)
			{
				if (p->parent->left == p)
					p->parent->left = NULL;
				else p->parent->right = NULL;
				delete p;
				return;
			}
			if (p->left) DelL(p->left);
			else DelL(p->right);
		}
	}
	void DelUnderT(Node* p)
	{
		if (!p) return;
		if (p->left == NULL && p->right == NULL)
		{
			DelL(p);
			return;
		}
		if (p->left)
			DelUnderT(p->left);
		if (p->right)
			DelUnderT(p->right);
	}
	void Copy(Node* q, Node* p, int k) //копирование дерева с корнем q
	//p - предок нового дерева
	//k=0 - копируем левого потомка p, 1 - правого
	{
		assert(q == NULL);
		Node* t = new Node(q->key, p);
		if (k) p->right = t;
		else p->left = t;
		Copy(q->left, t, 0);
		Copy(q->right, t, 1);
	}
	int FindHight(Node* p) //поиск высоты
	{
		int r = 0, l = 0, h = 0;
		if (!p) return 0;
		if (p->right) r = FindHight(p->right);
		if (p->left) l = FindHight(p->left);
		if (r > l) h = r;
		else h = l;
		return h + 1;
	}
	int FindCount(Node* p)
	{
		int r = 0, l = 0, h = 0;
		if (!p) return 0;
		if (p->right) r = FindCount(p->right);
		if (p->left) l = FindCount(p->left);
		h = l + r;
		return h;
	}
	bool DelNode(Node* d) //удаление узла p
	{
		if (d->left == NULL && d->right == NULL)
		{
			DelL(d);
			return 0;
		}
		if (d->left && d->right == NULL)
		{
			Node* q = d->parent;
			if (q->left == d) 
				q->left = d->left;
			else 
				q->right = d->left;
			d->left->parent = q;
			delete d;
			return 0;
		}
		if (d->left == NULL && d->right)
		{
			Node* q = d->parent;
			if (q->left == d) q->left = d->right;
			else q->right = d->right;
			d->right->parent = q;
			delete d;
			return 0;
		}
		Node* q = d->parent; //когда d имеет оба наследника
		Node* t = d;
		while (t->left) t = t->left;
		if (t->right == NULL)
			t->parent->left = NULL;
		else
		{
			t->parent->left = t->right;
			t->right->parent = t->parent;
		}
		if (q->left == d) q->left = t;
		else q->right = t;
		t->left = d->left;
		t->right = d->right;
		t->parent = q;
		if (t->left)t->left->parent = t;
		t->right->parent = t;
		delete d;
		return 1;
	}
	Node* FindKey(Node* p, int k) //поиск ключа(начало корень p)
	{
		if (p != 0) 
		{
			if (p->key == k) return p;
			if (FindKey(p->left, k) != NULL) return FindKey(p->left, k);
			if (FindKey(p->right, k) != NULL) return FindKey(p->right, k);
		}
	}
	void PrintTree(int k, Node* p) //вывод дерева с корнем p на консоль
	{
		if (!p) return;
		PrintTree(k + 5, p->right);
		for (int i = 0; i < k; i++) cout << ' ';
		cout << p->key << endl;
		PrintTree(k + 5, p->left);
	}
};
void main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Введите изначальный массив из 10 чисел: ";
	int U[10] = { 10, 9, 8, 7, 10, 5, 4 , 3 , 10 , 1 }; //меняла значения для проверки всех операций
	/*for (int i = 0; i < 10; i++)
		cin >> U[i];
	cout << endl;
	*/
	cout << "Программа перестраивает массив в двоичное дерево, далее все операции будут производиться над этой структурой" << endl;
	BinaryTree BT(U, 10);
	Node* x;
	Node* y;
	cout << "Есть ли узел со значением 2: " << endl;
	x = BT.FindKey(BT.Root(), 2);
	if (x == NULL)
		cout << "Нет" << endl;
	else
		cout << "Найдено " << x->Key() << endl;
	cout << "Удалим узел со значением два: " << endl;
	BT.DelNode(x); //удаление узла, который нашли
	BT.PrintTree(1, BT.Root()); cout << endl;
	x = BT.FindKey(BT.Root(), 2);
	cout << "Проверим, есть ли у минимального узла еще ветви: " << endl;
	if (x == NULL)
		cout << "Нет" << endl;
	else
		cout << "Найдено " << x->Key() << endl;
	cout << endl;
	system("pause");
}