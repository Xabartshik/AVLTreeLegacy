
#include "BinarySearchTree.h"
#include <vector>
//Всатвка O(log2(n))
// Поиск O(log2(n))
// Удаление O(log2(n))
// Повороты O(1)
// Доступ O(log2(n))
// Класс AVLTreeNode наследуется от TreeNode и имеет дополнительное поле для коэффициента баланса.
template<typename T>
class AVLTreeNode : public TreeNode<T> {
public:


    // Конструктор по умолчанию.
    AVLTreeNode() : TreeNode<T>(), balanceFactor(0) {}

    // Конструктор, принимающий данные.
    AVLTreeNode(const T& data) : TreeNode<T>(data), balanceFactor(0) {}

    // Конструктор, принимающий данные и указатели на предыдущий и следующий узлы.
    AVLTreeNode(const T& data, TreeNode<T>* getLeft(), TreeNode<T>* getRight()) : TreeNode<T>(data, getLeft(), getRight()), balanceFactor(0) {}

    // Деструктор.
    ~AVLTreeNode() {}

    // Конструктор копирования.
    AVLTreeNode(const AVLTreeNode& other) : TreeNode<T>(other), balanceFactor(other.balanceFactor) {}

    // Конструктор перемещения.
    AVLTreeNode(AVLTreeNode&& other) : TreeNode<T>(std::move(other)), balanceFactor(other.balanceFactor) {}

    // Оператор копирования.
    AVLTreeNode& operator=(const AVLTreeNode& other) {
        TreeNode<T>::operator=(other);
        balanceFactor = other.balanceFactor;
        return *this;
    }

    // Оператор перемещения.
    AVLTreeNode& operator=(AVLTreeNode&& other) {
        TreeNode<T>::operator=(std::move(other));
        balanceFactor = other.balanceFactor;
        return *this;
    }

    // Преобразовательт указателя на (на левый) TreeNode в указатель на AVLTreeNode
    AVLTreeNode<T>* getLeft() {
        return static_cast<AVLTreeNode<T>*>(this->n_left);
    }

    // Преобразовательт указателя на (на правый) TreeNode в указатель на AVLTreeNode
    AVLTreeNode<T>* getRight() {
        return static_cast<AVLTreeNode<T>*>(this->n_right);
    }

    // Преобразовательт указателя на (на левый) TreeNode в указатель на AVLTreeNode
    const AVLTreeNode<T>* getLeft() const {
        return static_cast<const AVLTreeNode<T>*>(this->n_left);
    }

    // Преобразовательт указателя на (на правый) TreeNode в указатель на AVLTreeNode
    const AVLTreeNode<T>* getRight() const {
        return static_cast<const AVLTreeNode<T>*>(this->n_right);
    }

    // Коэффициент баланса узла.
    short int balanceFactor;


};

// Класс AVLTree представляет собой само сбалансированное бинарное дерево поиска.
template<typename T>
class AVLTree {
private:
    // Указатель на корень дерева.
    AVLTreeNode<T>* root;

    // Функция для обновления коэффициента баланса узла.
    void updateBalanceFactor(AVLTreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }

        int leftHeight = getHeight(node->getLeft());
        int rightHeight = getHeight(node->getRight());
        node->balanceFactor = leftHeight - rightHeight;
    }

    // Функция для получения высоты узла.
    int getHeight(AVLTreeNode<T>* node) {
        if (node == nullptr) {
            return 0;
        }

        return 1 + std::max(getHeight(node->getLeft()), getHeight(node->getRight()));
    }

    // Функция для правого поворота.
    AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* node) {
        AVLTreeNode<T>* temp = node->getLeft();
        node->n_left = temp->getRight();
        temp->n_right = node;

        updateBalanceFactor(node);
        updateBalanceFactor(temp);

        return temp;
    }

    // Функция для левого поворота.
    AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* node) {
        AVLTreeNode<T>* temp = node->getRight();
        node->n_right = temp->getLeft();
        temp->n_left = node;

        updateBalanceFactor(node);
        updateBalanceFactor(temp);

        return temp;
    }

    // Функция для балансировки дерева.
    AVLTreeNode<T>* balanceTree(AVLTreeNode<T>* node) {
        if (node == nullptr) {
            return nullptr;
        }

        updateBalanceFactor(node);

        if (node->balanceFactor > 1) {
            if (getHeight(node->getLeft()->getLeft()) >= getHeight(node->getLeft()->getRight())) {
                //Одинарный правый поворот
                node = rotateRight(node);
            }
            else {
                //Большой правый поворот
                node->n_left = rotateLeft(node->getLeft());
                node = rotateRight(node);
            }
        }
        else if (node->balanceFactor < -1) {
            if (getHeight(node->getRight()->getRight()) >= getHeight(node->getRight()->getLeft())) {
                //Одинарный левый поворот
                node = rotateLeft(node);
            }
            else {
                //Большой левый поворот
                node->n_right = rotateRight(node->getRight());
                node = rotateLeft(node);
            }
        }

        return node;
    }

    // Функция для вставки узла в дерево.
    AVLTreeNode<T>* insertNode(AVLTreeNode<T>* node, const T& data) {
        if (node == nullptr) {
            return new AVLTreeNode<T>(data);
        }

        if (data < node->n_data) {
            node->n_left = insertNode(node->getLeft(), data);
        }
        else if (data > node->n_data) {
            node->n_right = insertNode(node->getRight(), data);
        }



        return balanceTree(node);
    }
    // Функция для удаления узла из дерева.
    AVLTreeNode<T>* deleteNode(AVLTreeNode<T>* node, const T& data) {
        if (node == nullptr) {
            return nullptr;
        }

        if (data < node->n_data) {
            node->n_left = deleteNode(node->getLeft(), data);
        }
        else if (data > node->n_data) {
            node->n_right = deleteNode(node->getRight(), data);
        }
        else {
            if (node->getLeft() == nullptr) {
                AVLTreeNode<T>* temp = node->getRight();
                delete node;
                return temp;
            }
            else if (node->getRight() == nullptr) {
                AVLTreeNode<T>* temp = node->getLeft();
                delete node;
                return temp;
            }

            AVLTreeNode<T>* temp = node->getRight();
            while (temp->getLeft() != nullptr) {
                temp = temp->getLeft();
            }

            node->n_data = temp->n_data;
            node->n_right = deleteNode(node->getRight(), temp->n_data);
        }

        return balanceTree(node);
    }

public:
    // Конструктор по умолчанию.
    AVLTree() : root(nullptr) {}

    // Деструктор.
    ~AVLTree() {
        clear();
    }

    // Функция для вставки элемента в дерево.
    void insert(const T& data) {
        root = insertNode(root, data);
    }

    // Функция для удаления элемента из дерева.
    void remove(const T& data) {
        root = deleteNode(root, data);
    }



    // Метод для вывода дерева в виде строки.
    template<typename T>
    string toString() {
        string result = "";
        toStringHelper(root, result);
        return result;
    }



    // Метод для вывода дерева в виде дерева.
    void printTree() {
        if (root)
            printTreeHelper(root, 0);
    }



    // Метод для поиска элемента в дереве.
    AVLTreeNode<T>* find(const T& data) {
        return findHelper(root, data);
    }

    //Метод поиска узла в дереве
    AVLTreeNode<T>* findNode(const T& data) {
        AVLTreeNode<T>* current = root;
        while (current != nullptr) {
            if (data < current->n_data) {
                current = current->getLeft();
            }
            else if (data > current->n_data) {
                current = current->getRight();
            }
            else {
                return current; // Найдено
            }
        }
        return nullptr; // Не найдено
    }



    // Метод для доступа к коэффициенту баланса узла по узлу.
    int getBalanceFactorNode(AVLTreeNode<T>* node) {
        if (node == nullptr) {
            return 0;
        }

        return node->balanceFactor;
    }

    // Метод для доступа к коэффициенту баланса узла по значению. Бросает исключение, если не нашел.
    int getBalanceFactor(T val) {
        AVLTreeNode<T>* node = find(val);
        if (node)
        {
            return getBalanceFactorNode(node);
        }
        else
            throw out_of_range("Value not found");
    }


    //Класс Итератор для AVLTreeNode (LNR, Inorder)
    class Iterator {
    private:
        AVLTreeNode<T>* root;
        stack<AVLTreeNode<T>*> nodeStack;

    public:
        // Конструктор итератора
        Iterator(AVLTreeNode<T>* n_root) {
            root = n_root;
            pushLeftBranch(n_root);
        }

        // Оператор проверки на неравенства
        bool operator!=(const Iterator& other) const {
            return !(hasNext() == false && other.hasNext() == false);
        }

        // Оператор проверки на равенства
        bool operator==(const Iterator& other) const {
            return nodeStack.empty() == other.nodeStack.empty();
        }

        // Проверка есть ли следующий элемент
        bool hasNext() const {

            return !nodeStack.empty();
        }

        // Оператор разыменования
        T& operator*() const {
            return nodeStack.top()->n_data;
        }

        // Получение информации 
        T& data() {
            return nodeStack.top()->n_data;
        }

        // Оператор инкремента
        Iterator& operator++() {
            return next();
        }

        // Сброс итератора
        void reset() {
            while (!nodeStack.empty())
                nodeStack.pop();
            pushLeftBranch(root);
        }

        // Переход к следующему элементы
        Iterator& next() {
            AVLTreeNode<T>* currentNode;
            if (!hasNext()) {
                throw std::out_of_range("No more elements in the iterator");
            }
            currentNode = nodeStack.top();
            nodeStack.pop();
            pushLeftBranch(currentNode->getRight());
            return *this;
        }

    private:
        // Метод помещающий все левые узлы узла node в nodeStack
        void pushLeftBranch(AVLTreeNode<T>* node) {
            while (node != nullptr) {
                nodeStack.push(node);
                node = node->getLeft();
            }
        }
    };

    // возвращает итератор на начало дерева
    Iterator begin() const {
        return Iterator(root);
    }

    // Переносит итератор на конец дерева
    Iterator end() const {
        return Iterator(nullptr);
    }
    void clear() {
        if (root)
        {
            clearNode(root);
            root = nullptr;
        }
    }

    // тестирование
    static void AVLTreeRunTest() {
        AVLTree<int> tree;

        // Тестирование вставки в пустое дерево
        tree.insert(10);
        assert(tree.find(10) != nullptr); // Должен найти 10
        assert(tree.find(20) == nullptr); // Не должен найти 20

        // Тестирование вставки нескольких элементов
        tree.insert(20);
        tree.insert(5);
        tree.insert(15);
        tree.printTree();
        assert(tree.find(5) != nullptr);  // Должен найти 5
        assert(tree.find(15) != nullptr); // Должен найти 15
        assert(tree.find(25) == nullptr); // Не должен найти 25

        // Тестирование удаления элемента
        tree.remove(20);
        assert(tree.find(20) == nullptr); // 20 должен быть удален

        // Тестирование удаления корня
        tree.remove(10);
        assert(tree.find(10) == nullptr); // 10 должен быть удален

        // Тестирование удаления элемента, которого нет
        tree.remove(100); // Ничего не произойдет, дерево остается корректным

        // Тестирование итератора
        tree.insert(7);
        tree.insert(3);
        tree.insert(8);

        AVLTree<int>::Iterator it = tree.begin();
        for (int val : tree) {
            cout << val << " ";
        }
        assert(it != tree.end()); // Должен иметь хотя бы один элемент
        assert(*it == 3);         // Первый элемент должен быть 3
        ++it;
        assert(*it == 5);         // Второй элемент должен быть 5
        ++it;
        assert(*it == 7);         // Третий элемент должен быть 7
        ++it;
        assert(*it == 8);         // Четвертый элемент должен быть 8
        ++it;
        assert(*it == 15);         // Четвертый элемент должен быть 8
        ++it;
        assert(it == tree.end()); // Достигнуть конца

        // Тестирование функции очистки дерева
        tree.clear();
        assert(tree.find(5) == nullptr);  // Все элементы должны быть удалены
        assert(tree.begin() == tree.end()); // Итератор должен быть пустым

        // Тестирование поворотов дерева
        tree.clear();
        vector<int> right;
        size_t i;

        // Поворот право право (малый правый поворот)
        tree.insert(7);
        tree.insert(8);
        tree.insert(5);
        tree.insert(6);
        tree.insert(3);
        tree.insert(4);
        tree.insert(1);
        right = { 1, 3, 4, 5, 6, 7, 8 };
        i = 0;
        for (int value : tree)
        {
            assert(abs(tree.getBalanceFactor(value)) < 2);
            i++;
        }
        tree.clear();


        // Поворот лево лево (малый левый поворот)
        tree.insert(2);
        tree.insert(1);
        tree.insert(4);
        tree.insert(3);
        tree.insert(6);
        tree.insert(5);
        tree.insert(7);
        right.clear();
        right = { 1, 2, 3, 4, 5, 6, 7 };
        i = 0;
        for (int value : tree)
        {
            assert(abs(tree.getBalanceFactor(value)) < 2);
            i++;
        }
        tree.clear();

        // Поворот право лево
        tree.insert(6);
        tree.insert(7);
        tree.insert(2);
        tree.insert(1);
        tree.insert(4);
        tree.insert(3);
        tree.insert(5);
        right.clear();
        right = { 1, 2, 3, 4, 5, 6, 7 };
        i = 0;
        for (int value : tree)
        {
            assert(abs(tree.getBalanceFactor(value)) < 2);
            i++;
        }
        tree.clear();

        // Поворот лево право
        tree.insert(2);
        tree.insert(1);
        tree.insert(6);
        tree.insert(4);
        tree.insert(3);
        tree.insert(5);
        tree.insert(7);
        AVLTree<int>::Iterator it5 = tree.begin();
        right.clear();
        right = { 1, 2, 3, 4, 5, 6, 7 };
        i = 0;
        for (int value : tree)
        {
            assert(*it5 == right[i]);
            ++it5;
            i++;
        }
        tree.clear();

        std::cout << "All tests passed successfully!" << std::endl;
    }


};
// Вспомогательный метод для поиска элемента в дереве.
template<typename T>
AVLTreeNode<T>* findHelper(AVLTreeNode<T>* node, const T& data) {
    if (node == nullptr) {
        return nullptr;
    }

    if (data < node->n_data) {
        return findHelper(node->getLeft(), data);
    }
    else if (data > node->n_data) {
        return findHelper(node->getRight(), data);
    }
    else {
        return node;
    }
}

// Функция для уничтожения дерева.
template<typename T>
void clearNode(AVLTreeNode<T>* node) {
    if (node == nullptr) {
        return;
    }

    clearNode(node->getLeft());
    clearNode(node->getRight());
    delete node;
}

// Вспомогательный метод для вывода дерева в виде дерева.
template<typename T>
void printTreeHelper(AVLTreeNode<T>* node, int level) {
    if (node == nullptr) {
        return;
    }

    printTreeHelper(node->getRight(), level + 1);
    for (int i = 0; i < level; i++) {
        std::cout << "  ";
    }
    std::cout << node->n_data << std::endl;
    printTreeHelper(node->getLeft(), level + 1);
}

// Вспомогательный метод для вывода дерева в виде строки.
template<typename T>
void toStringHelper(AVLTreeNode<T>* node, std::string& result) {
    if (node == nullptr) {
        return;
    }

    toStringHelper(node->getLeft(), result);
    result += std::to_string(node->n_data) + " ";
    toStringHelper(node->getRight(), result);
}