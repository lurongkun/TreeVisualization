#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include<iostream>
#include"RBTree.h"

//判断是否存在
template<typename TreeNode>
bool isInTree(int goal, TreeNode* node)
{
    while (node != nullptr)
    {
        if (goal > node->getElem())
            node = node->getRight(); //去右子树找
        else if (goal < node->getElem())
            node = node->getLeft(); //去左子树找
        else
            return 1; //找到
    }
    return 0; //传入为空，查找失败
}

template<typename TreeNode>
void LNR(TreeNode* &node)
{
    if (node != nullptr)
    {
        LNR(node->getLeft());
        std::cout << node->getElem() << " ";
        LNR(node->getRight());
    }
    else
        return;
}

template<typename TreeNode>
void LRN(TreeNode* &node)
{
    if (node != nullptr)
    {
        LRN(node->getLeft());
        std::cout << node->getElem() << " ";
        LRN(node->getRight());
    }
    else
        return;
}


template<typename TreeNode>
void Clear(TreeNode* &node)
{
    if(node!=nullptr)
    {
        Clear(node->getLeft());
        Clear(node->getRight());
        node->Delete(node->getElem(),node);
    }
}

template<typename TreeNode>
TreeNode* FindMin(TreeNode* node)
{
    while (node->getLeft() != nullptr)//左边不为空
        node = node->getLeft();
    return node; //左边为空，说明找到最小值了
}

template<typename TreeNode>
int getHeight(TreeNode* node)
{
    if (node == nullptr) return 0;
    else
    {
        int hl, hr;
        hl = getHeight(node->getLeft());
        hr = getHeight(node->getRight());
        return std::max(hl, hr) + 1;
    }
}

#endif // FUNCTIONS_H
