#include "AVLTree.h"
#include"Functions.h"
#include<QDebug>
#include<iostream>

typedef AVLTree AVLNode;
typedef AVLTree* AVL;
typedef AVLTree* Position;

AVLTree::AVLTree(QWidget *parent) : QWidget(parent)
{
    this->left = nullptr;
    this->right = nullptr;
}

AVLTree::AVLTree(int n, QWidget *parent) : QWidget(parent), AbstractTree(n)
{
    this->left = nullptr;
    this->right = nullptr;
}

int AVLTree::Height(Position p)
{
    if(p==nullptr)
        return -1;
    else
        return p->height;
}

AVL AVLTree::LLrotate(Position k2) //LL型
{
    Position k1=k2->left;
    k2->left=k1->right;
    k1->right=k2;

    k1->height=std::max(Height(k1->left),Height(k1->right))+1;
    k2->height=std::max(Height(k2->left),Height(k2->right))+1;

    return k1;//返回根节点
}

AVL AVLTree::RRrotate(Position k2) //RR型
{
    Position k1=k2->right;
    k2->right=k1->left;
    k1->left=k2;

    k1->height=std::max(Height(k1->left),Height(k1->right))+1;
    k2->height=std::max(Height(k2->left),Height(k2->right))+1;

    return k1;//返回根结点
}

AVL AVLTree::RLrotate(Position k3) //RL型
{
    k3->right = LLrotate(k3->right);
    return RRrotate(k3);
}


AVL AVLTree::LRrotate(Position k3) //LR型
{
    k3->left = RRrotate(k3->left);
    return LLrotate(k3);
}


//插入
AVL AVLTree::Insert(int x,AVL& T)
{
    if(T==nullptr)
    {
        T=new AVLNode(x);
    }
    else if(x<T->getElem())
    {
        /* 插入T的左子树 */
        T->left=Insert(x,T->left);
        //qDebug()<<"AVL左边插入";
        //qDebug()<<Height(T->left)<<" "<<Height(T->right);
        if(Height(T->left)-Height(T->right)==2)
        {
            //qDebug()<<"准备LX旋转";
            if (x < T->left->getElem()) /* 左单旋,LL旋转*/
            {
                T = LLrotate(T);
                //qDebug()<<"LL";
            }
            else
            {
                T = LRrotate(T);  /* 左-右双旋,LR旋转 */
                //qDebug()<<"LR";
            }
        }
    }
    else if(x>T->getElem())
    {
        /* 插入T的右子树 */
        T->right=Insert(x,T->right);
        //qDebug()<<"AVL右边插入";
        //qDebug()<<Height(T->left)<<" "<<Height(T->right);
        if(Height(T->right)-Height(T->left)==2)
        {
            //qDebug()<<"准备RX旋转";
            if (x > T->right->getElem())/* 右单旋 */
            {
                T = RRrotate(T);
                //qDebug()<<"RR";
            }
            else
            {
                T = RLrotate(T);
                //qDebug()<<"RL";
            }
        }
    }
    else /* n = elem , 什么都不干*/
        return T;
    T->height=std::max(Height(T->left),Height(T->right))+1;
    //qDebug()<<T->height;
    return T;
}

AVL AVLTree::Delete(int key, AVLNode* &T)
{
    AVL temp;
    if (T == nullptr)
        return T;
    if (key < T->getElem())
    {
        T->left = Delete(key, T->left);
        if (Height(T->right) - Height(T->left) == 2)
        {
            if (Height(T->right->left) > Height(T->right->right))
            {
                T = RLrotate(T);
            }
            else
            {
                T = RRrotate(T);
            }
        }
    }
    else if (key > T->getElem())
    {
        T->right = Delete(key, T->right);
        if (Height(T->left) - Height(T->right) == 2)
        {
            if (Height(T->left->right) > Height(T->left->left))
            {
                T = LRrotate(T);
            }
            else
            {
                T = LLrotate(T);
            }
        }
    }
    else //找到了要删除的节点
    {

        if (T->left != nullptr && T->right != nullptr) //如果要删除的节点有左右子节点
        {
            temp = FindMin(T->right); //往右子树找最小元素（或者往左子树找最大元素）填充要删除的节点
            T->setElem(temp->getElem());
            T->right = Delete(T->getElem(), T->right); //在要删除节点的右子树中删除最小元素
        }
        else //被删除的节点有一个或者无子节点
        {
            temp = T;
            if (T->left == nullptr) //有右节点或无节点
                T = T->right; //这样一来，要删除的节点的父节点就会指向那个右节点
            else if (T->right == nullptr) //有左节点或无节点
                T = T->left; //同理
            delete temp; //删除节点
            temp = nullptr;
        }
    }
    if (T != nullptr)
    {
        T->height = std::max(Height(T->left), Height(T->right)) + 1;
    }
    return T;
}

AVL& AVLTree::getLeft()
{
    return this->left;
}

AVL& AVLTree::getRight()
{
    return this->right;
}

AVLTree::~AVLTree()
{

}
