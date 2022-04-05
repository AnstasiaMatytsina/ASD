#include <iostream>
#include <assert.h>
using namespace std;

class Node // Класс узел
{
private:
	int key;
	Node* left, * right;
public:
	friend class BinaryTree;
	Node(int k = 0, Node* L = NULL, Node* R = NULL);// конструктор по умолчанию
	int Key() 
	{ 
		return key; 
	}
	friend ostream& operator << (ostream& o, Node* t)//перегрузка оператора вывод
	{
		if (t == NULL) 
			cout << "Такого узла нет";
		else 
			cout << t->key;//вывод значения ключа
		return o;
	}
};

class BinaryTree //Класс бинарное дерево
{
private:
	Node* root; //указатель на корень
public:
	BinaryTree(Node *temp)//Конструктор поумолчанию
	{
		if (temp)
		{
			root = temp;
		}
		else
			root = NULL;
	}
	BinaryTree(int* a, int n) //конструктор с двумя параметрами, где а-массив элементов, n-кол-во элементов
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
	int Height() //ф-ция вычисления высоты дерева
	{
		return Height_node(root);
	}
	int Height_node(Node* temp) //ф-ция вычисления высоты узла
	{
		if (temp == NULL) return 0; //у пустых деревьев и узлов соответствующая высота
		int h_l = Height_node(temp->left); //в высоту левого поддерева заносим рекурсией значение высоты левого потомка
		int h_r = Height_node(temp->right); //в высоту правого поддерева заносим рекурсией значение высоты правого потомка
		if (h_l > h_r) return h_l + 1; //Если высота левого потомка больше правого, то высота корня данного поддерева соответственно на 1 больше
		return h_r + 1; //Иначе высота корня данного поддерева больше высоты правого поддерева на 1
	}
	void levels() //Передаём высоту дерева в качестве параметра в ф-цию обхода по уровням
	{
		int u = Height();
		for (int i = 0; i < u; i++) //по циклу обходим дерево u раз
		{
			levels(root, i);//передаём какой уровень нужно вывести
			cout << endl;// отступаем
		}
	}
	void levels(Node* temp, int i) //ф-ция нахождения нужного уровня
	{
		if (temp == NULL) return; //Если узел пустой, возвращаемся
		else
		{
			if (i == 0) //если u=0, то мы дошли до нужного уровня, выводим элемент
			{
				cout << temp->key << "  ";
				return;
			}
			if (temp->left) levels(temp->left, i - 1); //рекурсией уходим влево и уменьшаем число уровней, которое осталось пройти до нужного
			if (temp->right) levels(temp->right, i - 1); //рекурсией уходим вправо и уменьшаем число уровней, которое осталось пройти до нужного
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
	Node* find_node(int k)//ф-ция нахождения узла
	{
		Node* p = find_node(root, k);//возвращаем нужный узел, либо NULL
		return p;//возвращаем узел
	}
	Node* find_node(Node* temp, int k)//ф-ция нахождения узла
	{
		if (temp == NULL) 
			return temp;//если узел пуст, возвращаемся 
		if (k == temp->key) 
			return temp;//если искомое значение совпадает с ключём текущего узла, мы нашли его, возвращаем его
		if (k < temp->key) 
			temp = find_node(temp->left, k);//Если искомое значение меньше ключа текущего узла, идём в левое поддерево
		else 
			if (k > temp->key) 
				temp = find_node(temp->right, k);//Иначе в правое поддерево
		return temp;//возвращаем результат поисков
	}
	BinaryTree del_node(int k)//ф-ция удаления узла
	{
		Node* temp = find_node(k), * r = root;//Ищем узел в дереве 
		if (temp == NULL) return *this;//Если мы не находим его, значит удалять нечего, возвращаем текущее дерево
		if (temp == root)//если удаляемый узел это корень, удаляем корень и на его месть возвращаем результат ф-ции удаления узла из дерева
		{
			root = del_node(temp);
			return *this;//возвращаем новое дерево
		}
		while ((r->left != temp) && (r->right != temp))//пока мы не найдём путь от корня до удаляемого узла:
		{
			if (r->key > temp->key)r = r->left;//Если значение текущего узла больше нужного узла, двигаемся влево
			else r = r->right; //Иначе вправо
		}
		if (r->left == temp) r->left = del_node(temp);//Если левый потомок текущего узла = нужному, в левого потомка возвращаем результат удаления узла q
		else r->right = del_node(temp);//иначе, в правого потомка
		return *this;//возвращаем новое дерево
	}
	Node* del_node(Node* temp)//удаление узла из дерева
	{
		Node* s, * r;//s будет потомком текущего узла, r-предком
		if (temp->left == NULL && temp->right == NULL)//Если у удаляемого узла нет потомков, просто опустошаем его
		{
			delete temp;
			temp = NULL;
			return temp;
		}
		if (temp->right == NULL)//если он не имеет правого потомка, то на его место становится его левый потомок
		{
			r = temp;
			temp = temp->left;
			delete r;
			return temp;
		}
		if (temp->left == NULL)//если он не имеет левого потомка, то на его место становится его правый потомок
		{
			r = temp;
			temp = temp->right;
			delete r;
			return temp;
		}
		//Если есть и левый и правый потомок, выбираем ближайший по значению узел из правого поддерева
		s = temp->right;
		if (s->left == NULL)//Если у правого потомка удаляемого узла нет левого потомка, значит правый потомок наименьший из этого поддерева
		{
			temp->key = s->key;//Не использую присвоение, т.к. сотрутся данные о левом поддереве удаляемого узла, а это недопустимо
			temp->right = s->right;
			delete s;//очищаю память s
			return temp;
		}
		while (s->left != NULL)//Если левый потомок правого поддерева удаляемого узла не пуст, идём налево доконца, т.к. последний будет наименьшим по значению
		{
			r = s; s = s->left;//r-предок s
		}
		temp->key = s->key;//переназначаем новый узел на место удалённого
		r->left = s->right;
		delete s;//очищаем память
		return temp;
	}
	Node* Root() //Возвращение корня
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

	//Вспомогательные функции для узлов и дерева (используются только внутри класса)
private:
	BinaryTree create(int n)//ф-ция создания дерева
	{
		int k;//вводимые с клавиатуры значения ключей
		cout << "Введите элементы" << endl;
		for (int i = 0; i < n; i++)
		{
			cin >> k;
			root = add_node(root, k);//добавление узлов в дерево
		}
		return *this;//возвращение конечного дерева
	}
	BinaryTree add_node(int k)//добавления узла в дерево
	{
		root = add_node(root, k);//возвращает корень с изменённой информацией о потомках и т.д.
		return *this;//возвращает конечное дерево
	}
	Node* add_node(Node* temp, int k)//ф-ция добавления узла в дерево
	{
		if (temp == NULL) //Если узел пуст, то добавляем наш узел в это место
		{
			Node* temp = new Node(k);//создаём узел, используя конструктор по умолчанию(к-значение ключа нашего узла)
			return temp;//возвращаем узел
		}
		if (k <= temp->key)
			temp->left = add_node(temp->left, k);//Если значение добавляемого узла меньше либо равно текущему, рекурсивно уходим в левое поддерево
		else
			temp->right = add_node(temp->right, k);//Иначе если значение добавляемого узла больше текущего, рекурсивно уходим в правое поддерево
		return temp;//возвращаем узел
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