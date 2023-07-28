#ifndef ABSTRACTTREE_H
#define ABSTRACTTREE_H
#pragma once

//树的基类
class AbstractTree
{
public:
    explicit AbstractTree(){}
    explicit AbstractTree(int n)
    {
        setElem(n);
    }
    ~AbstractTree() {}

    int getElem()
    {
        return this->elem;
    }

    void setElem(int n)
    {
        this->elem = n;
    }

private:
    int elem;
};

#endif // ABSTRACTTREE_H
