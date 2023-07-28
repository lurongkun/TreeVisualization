#ifndef RBTREE_H
#define RBTREE_H
#include"abstractTree.h"
#include <QWidget>

typedef enum Colortype { red, black } Colortype;

class RBTreeNode : public QWidget
{
    Q_OBJECT
public:
    explicit RBTreeNode(QWidget *parent = nullptr);
    explicit RBTreeNode(int n, RBTreeNode*& p,QWidget *parent = nullptr);

    RBTreeNode* Initial();
    static RBTreeNode* spin(int n, RBTreeNode* p);
    static void handlecolor(int n, RBTreeNode* p);
    static void handledel();
    RBTreeNode* Insert(int n, RBTreeNode* p);
    RBTreeNode* halfDelete(int n, RBTreeNode* p);
    void Delete(int n, RBTreeNode* p);

    RBTreeNode* FindMin(RBTreeNode* bst);
    RBTreeNode* FindMax(RBTreeNode* bst);
    static RBTreeNode* Singleleftspin(RBTreeNode* k1);
    static RBTreeNode* Singlerightspin(RBTreeNode* k2);
    static RBTreeNode* Doubleleftspin(RBTreeNode* k1);
    static RBTreeNode* Doublerightspin(RBTreeNode* k2);

    //int getHeight(RBTreeNode* node);
    RBTreeNode* &getLeft();
    RBTreeNode* &getRight();

    RBTreeNode* handleNull(RBTreeNode* p);
    RBTreeNode* antihandleNull(RBTreeNode* p);
    int getColor();
    int getElem();
    void Clear(RBTreeNode* &a);
    //void LNR(RBTreeNode*);

private:
    int elem;
    RBTreeNode* left;
    RBTreeNode* right;
    Colortype color;
signals:

};

#endif // RBTREE_H
