// AVLTreeLegacy.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "AVLTreeLegacy.h"
int main() {
    AVLTree<int>::AVLTreeRunTest();
    AVLTree<int> tree;

    tree.insert(5);
    tree.insert(4);
    tree.insert(1);
    tree.insert(2);
    std::cout << "AVL-дерево:" << std::endl;
    tree.printTree();
    cout << endl;
    tree.insert(3);
    tree.insert(7);
    tree.insert(3);
    tree.insert(8);
    std::cout << "AVL-дерево:" << std::endl;
    tree.printTree();
    cout << endl;
    tree.insert(20);
    tree.insert(5);
    tree.insert(15);

    std::cout << "AVL-дерево:" << std::endl;
    tree.printTree();

    std::cout << "Поиск ключа 4:" << std::endl;
    if (tree.find(4)) {
        std::cout << "Ключ найден" << std::endl;
    }
    else {
        std::cout << "Ключ не найден" << std::endl;
    }

    cout << tree.find(4)->balanceFactor << endl;
    cout << tree.find(5)->balanceFactor << endl;
    cout << tree.find(15)->balanceFactor << endl;
    tree.remove(4);
    tree.clear();

    std::cout << "AVL-дерево после удаления ключа 4:" << std::endl;
    tree.printTree();
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        cout << *it << " ";
    }
    return 0;
}