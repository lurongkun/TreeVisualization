#ifndef AVLTREE_H
#define AVLTREE_H
#include"abstractTree.h"
#include <QWidget>

class AVLTree : public QWidget, public AbstractTree
{
    Q_OBJECT
public:
    typedef AVLTree* AVL;
    typedef AVLTree* Position;
    explicit AVLTree(QWidget *parent = nullptr);
    explicit AVLTree(int n,QWidget *parent = nullptr); //构造函数，传入一个值构造
    ~AVLTree();

public:
    AVL Insert(int n,AVL& p);
    AVL Delete(int n, AVL &avltree);
    AVL LLrotate(Position k1);
    AVL RRrotate(Position k2);
    AVL LRrotate(Position k3);
    AVL RLrotate(Position k3);
    AVL& getLeft();
    AVL& getRight();
    int Height(Position node); //鑾峰彇AVL鏍戦珮

private:
    AVL left = nullptr;
    AVL right = nullptr;
    int height;
signals:

};

#endif // AVLTREE_H
