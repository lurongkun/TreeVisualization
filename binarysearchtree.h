#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include"abstractTree.h"
#include <QWidget>

class BinarySearchTree : public QWidget, public AbstractTree
{
    Q_OBJECT
public:

    typedef BinarySearchTree BSTNode;
    typedef BinarySearchTree* BST;
    explicit BinarySearchTree(QWidget *parent = nullptr);
    explicit BinarySearchTree(int n,QWidget *parent = nullptr); //构造函数，传入一个值构造

public:
    void Insert(int n,BST bst);
    BST Delete(int n, BST &bst);
    BST& getLeft();
    BST& getRight();
    ~BinarySearchTree();

private:
    BST left = nullptr;
    BST right = nullptr;

signals:

};

#endif // BINARYSEARCHTREE_H
