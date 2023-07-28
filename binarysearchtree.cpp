#include "BinarySearchTree.h"
#include"Functions.h"
#include<QDebug>
#include<iostream>
typedef BinarySearchTree BSTNode;
typedef BinarySearchTree* BST;


BinarySearchTree::BinarySearchTree(QWidget *parent) : QWidget(parent)
{
    this->left = nullptr;
    this->right = nullptr;
}

BinarySearchTree::BinarySearchTree(int n, QWidget *parent):QWidget(parent), AbstractTree(n)
{
    this->left = nullptr;
    this->right = nullptr;
}

//插入
void BinarySearchTree::Insert(int n, BST bst=nullptr)
{
    if (getElem() == n)
        return;
    if (getElem() < n)  //往右边插
    {
        if (this->right == nullptr)  //如果为空，就创建一个节点
            this->right = new BSTNode(n);
        else
            this->right->Insert(n);
    }
    else  //往左边插
    {
        if (this->left == nullptr) //如果为空，就创建一个节点
            this->left = new BSTNode(n);
        else
            this->left->Insert(n);
    }
}

BST BinarySearchTree::Delete(int n,BST &bst)
{
    BSTNode* temp;
    if (bst == nullptr) std::cout << "未找到要删除的元素\n";
    else if (n < bst->getElem())
        bst->left = Delete(n, bst->left); //往左边找要删除的节点,返回删除左子树后新的左子树的根节点的地址
    else if (n > bst->getElem())
        bst->right = Delete(n, bst->right); //往右边找要删除的节点，同理
    else //找到了要删除的节点
    {
        if (bst->left != nullptr && bst->right != nullptr) //如果要删除的节点有左右子节点
        {
            temp = FindMin(bst->right); //往右子树找最小元素（或者往左子树找最大元素）填充要删除的节点
           // bst->getElem() = temp->getElem();
            bst->setElem(temp->getElem());
            bst->right = Delete(bst->getElem(), bst->right); //在要删除节点的右子树中删除最小元素
        }
        else //被删除的节点有一个或者无子节点
        {
            temp = bst;
            if (bst->left == nullptr) //有右节点或无节点
                bst = bst->right; //这样一来，要删除的节点的父节点就会指向那个右节点
            else if (bst->right == nullptr) //有左节点或无节点
                bst = bst->left; //同理
            delete temp; //删除节点
            temp = nullptr;
        }
    }
    return bst;
}


BST& BinarySearchTree::getLeft()
{
    return this->left;
}

BST& BinarySearchTree::getRight()
{
    return this->right;
}

BinarySearchTree::~BinarySearchTree()
{

}
