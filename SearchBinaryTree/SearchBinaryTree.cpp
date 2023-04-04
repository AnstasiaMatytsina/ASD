#include <iostream>
#include <assert.h>
#include <vector>

using namespace std;

class Node // Класс узел
{
protected:
	int key;
	Node* left, * right;
public:
	friend class BinaryTree;
	friend class SearchBinaryTree;
	Node();// конструктор по умолчанию
	Node(int k);// конструктор по умолчанию c key (для корня дерева),key - ключ узла(ветки)
	Node(int k, Node* l, Node* r);// конструктор с аргументами, где key - ключ узла (ветки), l - указатель на левую ветку, r - на правую
	bool emptyNode(Node* temp);
	int Key(); //возвращение ключа
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
protected:
	Node* root; //указатель на корень
public:
	BinaryTree();
	BinaryTree(Node* temp);
	BinaryTree(int* a, int n); //конструктор с двумя параметрами, где а-массив элементов, n-кол-во элементов
	BinaryTree(BinaryTree& temp);
	virtual ~BinaryTree();
	int height(); //ф-ция вычисления высоты дерева
	int heightNode(Node* temp); //ф-ция вычисления высоты узла
	void levels(); //Передаём высоту дерева в качестве параметра в ф-цию обхода по уровням
	void levels(Node* temp, int i); //ф-ция нахождения нужного уровня
	BinaryTree& operator= (BinaryTree& temp);//оператор присвоения
	Node* findNode(int k);//ф-ция нахождения узла
	Node* findNode(Node* temp, int k);//ф-ция нахождения узла
	virtual bool delNode(int k);//ф-ция удаления узла
	virtual Node* delNode(Node* temp);//удаление узла из дерева
	Node* rootFind(); //Возвращение корня
	void printTree(int l, Node* temp);// Вывод дерева в консоль
	int count();//Возвращает количество узлов
	int countNode(Node* temp);//Основная функция возвращения узлов
	int inVector(vector<int> v); //передаём пустой вектор размера n и возвращаем число узлов в дерева
	void inVector_auxiliary(Node* p, vector<int> v, int& k);// заполняем вектор
	bool isEmpty(); //Возвращает true, если дерево пустое
	//Вспомогательные функции для узлов и дерева (используются только внутри класса)
	BinaryTree create(int n);//ф-ция создания дерева
	virtual BinaryTree addNode(int x);//добавления узла в дерево
	virtual Node* addNode(Node* temp, int x);//ф-ция добавления узла в дерево
	void copy(Node* temp, Node*& root);
	void clear(Node* temp);
	virtual int maxKey()
	{
		return 1;
	}
	virtual int minKey()
	{
		return 1;
	}
};
class SearchBinaryTree : public BinaryTree {
public:
	//Так как изначальное двоичное дерево было написанно с конструктором и добавлением новых узлов по алгоритму двоичного дерева поиска 
	//Просто наследуем их конструкторы
	SearchBinaryTree() : BinaryTree() {}
	SearchBinaryTree(Node* temp) : BinaryTree(temp) {}
	SearchBinaryTree(int* mas, int n) : BinaryTree(mas, n) {}
	int minKey();  //Идем к максимально левой ветке
	int maxKey(); //Идем к максимально правой ветке
	BinaryTree create(int n);//ф-ция создания дерева
	BinaryTree addNode(int x); //добавления узла в дерево
	Node* addNode(Node* temp, int x); //ф-ция добавления узла в дерево
};

Node::Node()// конструктор по умолчанию
{
	key = 0;
	left = NULL;
	right = NULL;
}
Node::Node(int k)// конструктор по умолчанию c key (для корня дерева),key - ключ узла(ветки)
{
	key = k;
	left = NULL;
	right = NULL;
}
Node::Node(int k, Node* l, Node* r)// конструктор с аргументами, где key - ключ узла (ветки), l - указатель на левую ветку, r - на правую
{
	key = k;
	left = l;
	right = r;
}
bool Node::emptyNode(Node* temp)
{
	if (key == 0 && left == NULL && right == NULL)
		return 1;
	return 0;
}
int Node::Key() //возвращение ключа
{
	return key;
}

BinaryTree::BinaryTree()
{
	Node* temp = new Node;
	root = temp;
}
BinaryTree::BinaryTree(Node* temp)
{
	if (temp)
	{
		root = temp;
	}
	else
		root = NULL;
}
BinaryTree::BinaryTree(int* a, int n) //конструктор с двумя параметрами, где а-массив элементов, n-кол-во элементов
{
	root = NULL;
	for (int i = 0; i < n; i++)
	{
		root = addNode(root, a[i]);
	}
}
BinaryTree::BinaryTree(BinaryTree& temp)
{
	copy(temp.root, this->root);
}
BinaryTree::~BinaryTree()
{
	clear(root);
}
int BinaryTree::height() //ф-ция вычисления высоты дерева
{
	return heightNode(root);
}
int BinaryTree::heightNode(Node* temp) //ф-ция вычисления высоты узла
{
	if (temp == NULL) return 0; //у пустых деревьев и узлов соответствующая высота
	int h_l = heightNode(temp->left); //в высоту левого поддерева заносим рекурсией значение высоты левого потомка
	int h_r = heightNode(temp->right); //в высоту правого поддерева заносим рекурсией значение высоты правого потомка
	if (h_l > h_r) return h_l + 1; //Если высота левого потомка больше правого, то высота корня данного поддерева соответственно на 1 больше
	return h_r + 1; //Иначе высота корня данного поддерева больше высоты правого поддерева на 1
}
void BinaryTree::levels() //Передаём высоту дерева в качестве параметра в ф-цию обхода по уровням
{
	int u = height();
	for (int i = 0; i < u; i++) //по циклу обходим дерево u раз
	{
		levels(root, i);//передаём какой уровень нужно вывести
		cout << endl;// отступаем
	}
}
void BinaryTree::levels(Node* temp, int i) //ф-ция нахождения нужного уровня
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
BinaryTree& BinaryTree::operator= (BinaryTree& temp)//оператор присвоения
{
	if (this == &temp) return *this;
	else
	{
		clear(this->root);
		copy(temp.root, this->root);
		return *this;
	}
}
Node* BinaryTree::findNode(int k)//ф-ция нахождения узла
{
	Node* p = findNode(root, k);//возвращаем нужный узел, либо NULL
	return p;//возвращаем узел
}
Node* BinaryTree::findNode(Node* temp, int k)//ф-ция нахождения узла
{
	if (temp == NULL)
		return temp;//если узел пуст, возвращаемся 
	if (k == temp->key)
		return temp;//если искомое значение совпадает с ключём текущего узла, мы нашли его, возвращаем его
	if (k < temp->key)
		temp = findNode(temp->left, k);//Если искомое значение меньше ключа текущего узла, идём в левое поддерево
	else
		if (k > temp->key)
			temp = findNode(temp->right, k);//Иначе в правое поддерево
	return temp;//возвращаем результат поисков
}
bool BinaryTree::delNode(int k)//ф-ция удаления узла
{
	Node* temp = findNode(k), * r = root;//Ищем узел в дереве 
	if (temp == NULL) return 0;
	if (temp == root)
	{
		root = delNode(temp);
		return 1;
	}
	while ((r->left != temp) && (r->right != temp))//пока мы не найдём путь от корня до удаляемого узла:
	{
		if (r->key > temp->key)r = r->left;//Если значение текущего узла больше нужного узла, двигаемся влево
		else r = r->right; //Иначе вправо
	}
	if (r->left == temp) r->left = delNode(temp);//Если левый потомок текущего узла = нужному, в левого потомка возвращаем результат удаления узла q
	else r->right = delNode(temp);//иначе, в правого потомка
	return 1;
}
Node* BinaryTree::delNode(Node* temp)//удаление узла из дерева
{
	Node* s, * r = temp;//s будет потомком текущего узла, r-предком
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
Node* BinaryTree::rootFind() //Возвращение корня
{
	return root;
}
void BinaryTree::printTree(int l, Node* temp)// Вывод дерева в консоль
{
	if (temp == NULL) return;
	printTree(l + 3, temp->right);
	for (int k = 0; k < l; k++) cout << " ";
	cout.width(2);
	cout << temp->key << "\n";
	printTree(l + 3, temp->left);
}
int BinaryTree::count()//Возвращает количество узлов
{
	return countNode(root);
}
int BinaryTree::countNode(Node* temp)//Основная функция возвращения узлов
{
	if (temp == NULL) //Если ветка не идет дальше, преедаем 1
		return 0;
	int c_l = countNode(temp->left);//подсчет левой части
	int c_r = countNode(temp->right);//подсчет правой части
	return c_l + c_r + 1;//Вывод количества справа и слева
}
int BinaryTree::inVector(vector<int> v) //передаём пустой вектор размера n и возвращаем число узлов в дерева
{
	int k = 0; //обнуляем счётчик
	inVector_auxiliary(root, v, k); //вызываем основную функцию заполнения упорядоченного вектора
	return k; //возвращаем число элементов в векторе
}
void BinaryTree::inVector_auxiliary(Node* p, vector<int> v, int& k)// заполняем вектор
{
	if (p == NULL)
		return;//если узел пуст, добавлять нечего, возвращаемся
	inVector_auxiliary(p->left, v, k);//рекурсивно уходим влево, пока не дойдём до конца
	v.at(k) = p->key;//заносим в вектор значение ключа
	k++; //увеличиваем счётчик элементов
	inVector_auxiliary(p->right, v, k);//рекурсивно уходим вправо и продолжаем
}
bool BinaryTree::isEmpty()//Возвращает true, если дерево пустое
{
	if (root == NULL)
		return 1;
	return 0;
}
BinaryTree BinaryTree::create(int n)//ф-ция создания дерева
{
	int k;//вводимые с клавиатуры значения ключей
	cout << "Введите элементы" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> k;
		root = addNode(root, k);//добавление узлов в дерево
	}
	return *this;//возвращение конечного дерева
}
BinaryTree BinaryTree::addNode(int x)//добавления узла в дерево
{
	root = addNode(root, x);//возвращает корень с изменённой информацией о потомках и т.д.
	return *this;//возвращает конечное дерево
}
Node* BinaryTree::addNode(Node* temp, int x)//ф-ция добавления узла в дерево
{
	if (temp == NULL) //Если узел пуст, то добавляем наш узел в это место
	{
		Node* temp = new Node(x);//создаём узел, используя конструктор по умолчанию(к-значение ключа нашего узла)
		return temp;//возвращаем узел
	}
	if (x <= temp->key)
		temp->left = addNode(temp->left, x);//Если значение добавляемого узла меньше либо равно текущему, рекурсивно уходим в левое поддерево
	else
		temp->right = addNode(temp->right, x);//Иначе если значение добавляемого узла больше текущего, рекурсивно уходим в правое поддерево
	return temp;//возвращаем узел
}
void BinaryTree::copy(Node* temp, Node*& root)
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
void BinaryTree::clear(Node* temp)
{
	if (temp == NULL) return;
	clear(temp->left);
	clear(temp->right);
	delete temp;
	temp = NULL;
}

int SearchBinaryTree::minKey() { //Идем к максимально левой ветке
	if (root != NULL) {
		Node* temp = root;
		while (temp->left != NULL)
			temp = temp->left;
		return temp->key;
	}
}
int SearchBinaryTree::maxKey() { //Идем к максимально правой ветке
	if (root != NULL) {
		Node* temp = root;
		while (temp->right != NULL)
			temp = temp->right;
		return temp->key;
	}
}
BinaryTree SearchBinaryTree::create(int n)//ф-ция создания дерева
{
	int k;//вводимые с клавиатуры значения ключей
	cout << "Введите элементы" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> k;
		root = addNode(root, k);//добавление узлов в дерево
	}
	return *this;//возвращение конечного дерева
}
BinaryTree SearchBinaryTree::addNode(int x)//добавления узла в дерево
{
	root = addNode(root, x);//возвращает корень с изменённой информацией о потомках и т.д.
	return *this;//возвращает конечное дерево
}
Node* SearchBinaryTree::addNode(Node* temp, int x)//ф-ция добавления узла в дерево
{
	if (temp == NULL) //Если узел пуст, то добавляем наш узел в это место
	{
		Node* temp = new Node(x);//создаём узел, используя конструктор по умолчанию(к-значение ключа нашего узла)
		return temp;//возвращаем узел
	}
	if (x < temp->key)
		temp->left = addNode(temp->left, x);//Если значение добавляемого узла меньше , рекурсивно уходим в левое поддерево
	else
		temp->right = addNode(temp->right, x);//Иначе если значение добавляемого узла больше либо равно текущему, рекурсивно уходим в правое поддерево
	return temp;//возвращаем узел
}

void testSearchTree(int size)
{
	int failedCase = 0;
	SearchBinaryTree searchTree;
	vector<int> nodesKeys;


	for (int i = 0; i < size; ++i) {
		searchTree.addNode(i);
		nodesKeys.push_back(i);
	}


	int index, key;


	while (nodesKeys.size()) {
		// Поставила константу 3 как индекс удаления, так как 
		index = 3;
		nodesKeys.erase(nodesKeys.begin() + index);
		if (!searchTree.delNode(index)) {
			failedCase = 1;
			break;
		}


		if (nodesKeys.size()) {
			// Поставила константу 4 как индекс удаления, так как 
			index = 4;
			key = nodesKeys[index];
			nodesKeys.erase(nodesKeys.begin() + index);
			if (!searchTree.delNode(key)) {
				failedCase = 3;
				break;
			}
		}
	}


	if (failedCase || !searchTree.isEmpty()) {
		if (!failedCase) {
			failedCase = -1;
		}

		//std::cout << size << " " << searchTree.count() << std::endl;
		//std::cout << std::endl;
		//std::cout << std::endl;
	}
	cout << failedCase;
}

void testSearchTreeAsBinaryTree(int size)
{
	int failedCase = 0;
	SearchBinaryTree searchTree;
	BinaryTree& searchTreeRef = searchTree;
	std::vector<int> nodesKeys;


	for (int i = 0; i < size; ++i) {
		searchTreeRef.addNode(i);
		nodesKeys.push_back(i);
	}

	int index, key;

	while (nodesKeys.size()) {
		// Поставила константу 3 как индекс удаления, так как 
		index = 3;
		nodesKeys.erase(nodesKeys.begin() + index);
		if (!searchTreeRef.delNode(index)) {
			failedCase = 1;
			break;
		}

		if (nodesKeys.size()) {
			// Поставила константу 4 как индекс удаления, так как 
			index = 4;
			key = nodesKeys[index];
			nodesKeys.erase(nodesKeys.begin() + index);
			if (!searchTreeRef.delNode(key)) {
				failedCase = 3;
				break;
			}
		}
	}


	if (failedCase || !searchTreeRef.isEmpty()) {
		if (!failedCase) {
			failedCase = -1;
		}


		//std::cout << size << " " << searchTreeRef.count() << std::endl;
		//std::cout << std::endl;
		//std::cout << std::endl;
	}
	cout << failedCase;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	int n = 6;
	int mas[] = { 6,5,4,3,4,5 };
	// Для проверки работы через указатель
	BinaryTree* BT = new SearchBinaryTree(mas, n);
	Node* root = BT->rootFind();
	BT->printTree(0, root);
	cout << endl;
	cout << "Дерево пустое: ";
	if (BT->isEmpty())
		cout << "true";
	else
		cout << "false";
	cout << endl << "Высота дерева: ";
	int x = BT->height();
	cout << x << endl;
	cout << "Удалим узел с ключом 3, удален:" << BT->delNode(3) << endl;
	cout << endl;
	BT->printTree(0, root);
	cout << "Введите число, которое стоит добавить в дерево: ";
	int temp;
	cin >> temp;
	BT->addNode(temp);
	BT->printTree(0, root);
	cout << endl;
	cout << "Количество узлов: " << BT->count() << endl;
	cout << "Максимальный ключ: " << BT->maxKey() << endl;
	cout << "Минимальный ключ: " << BT->minKey() << endl;
	SearchBinaryTree BT2;
	cout << "Дерево пустое: ";
	if (BT2.isEmpty())
		cout << "true" << endl;
	else
		cout << "false" << endl;
	n = 0;
	int mas1[] = { NULL };
	cout << "Дерево пустое: ";
	SearchBinaryTree BT3(mas1, n);
	if (BT3.isEmpty())
		cout << "true";
	else
		cout << "false";
	// testSearchTree(10);
	// testSearchTreeAsBinaryTree(10);
	return 0;
}