#include "RBTree.h"

typedef RBTreeNode* RBTree;
typedef RBTreeNode Node;
typedef RBTreeNode* Position;

RBTreeNode::RBTreeNode(QWidget *parent) : QWidget(parent)
{
    this->left=nullptr;
    this->right=nullptr;
}

//声明一个NUllNode用于指向空结点,NULL用于表示叶子结点
Position NullNode = NULL;

//声明全局结点   X：当前待插入结点，P:父结点，Gp:祖父结点，GGp:曾夫结点，B兄弟结点
static Position X, P, GP, GGP, B, R;

RBTreeNode::RBTreeNode(int n,RBTree &T,QWidget *parent):QWidget(parent)
{
    //RBTree T;
    if(NullNode==NULL)
    {
        NullNode=new RBTreeNode;//(RBTree)malloc(sizeof(RBTreeNode));
        NullNode->left=NullNode->right=NullNode;
        NullNode->color=black;
        NullNode->elem=INT_FAST32_MAX;//NullNode指向无穷，这里用近似代替

        //创建头节点
        T=new RBTreeNode;//(RBTree)malloc(sizeof(Node));
        T->elem=-INT_FAST32_MAX;
        T->left=T->right=NullNode;//头节点元素为负无穷，只有右边有意义
        T->color=black;
    }
    Insert(n,T);
}

//对树的初始化
RBTree RBTreeNode::Initial()
{
    RBTree T=nullptr;
    if (NullNode == NULL)
    {
        NullNode = new RBTreeNode;//(RBTree)malloc(sizeof(RBTreeNode));
        NullNode->left = NullNode->right = NullNode;
        NullNode->color = black;
        NullNode->elem = INT_FAST32_MAX;//NullNode指向无穷，这里用近似代替

        //创建头节点
        T = new RBTreeNode;//(RBTree)malloc(sizeof(Node));
        T->elem = -INT_FAST32_MAX;
        T->left = T->right = NullNode;//头节点元素为负无穷，只有右边有意义
        T->color = black;
    }
    return T;
}


//旋转操作
Position RBTreeNode::spin(int n, Position p)
{
    //如果n比当前结点元素小
    if (n < p->elem)
    {
        if (n < p->left->elem)
            return p->left = Singleleftspin(p->left);//如果n比当前结点的左节点都小，执行单左旋
        else
            return p->left = Singlerightspin(p->left);//如果n比当前结点的左节点大，执行单右旋
    }

    //如果n比当前结点元素大
    else
    {
        if (n < p->right->elem)
            return p->right = Singleleftspin(p->right);//如果n比当前结点的左节点都小，执行单右旋
        else
            return p->right = Singlerightspin(p->right);//如果n比当前结点的左节点都小，执行单右旋
    }
}


void RBTreeNode::handlecolor(int n, Position p)
{
    //待插入节点颜色初始为红色
    X->color = red;
    X->left->color = black;
    X->right->color = black;
    //父节点若为红，进行调整
    if (P->color == red)
    {
        GP->color = red;
        if ((n < GP->elem) != (n < P->elem))
            P = spin(n, GP);//执行双旋转
        X = spin(n, GGP);
        X->color = black;
    }
    p->right->color = black;//确保根结点是黑色的
}

//自顶向下删除中处理结点的颜色变化
void RBTreeNode::handledel()
{   //当前结点在P左边
    if (X->elem < P->elem)
    {
        //兄弟结点初始化
        B = P->right;
        //如果兄弟的子节点都为黑,B,X,P变色
        if (B->left->color == black && B->right->color == black)
        {
            P->right->color = P->left->color = red;
            P->color = black;
        }

        //兄弟的左节点为红
        else if (B->left->color == red)
        {
            X->color = red;
            P->color = black;
            if (GP->elem < B->elem)
                GP->right = Doublerightspin(P);
            else
                GP->left = Doublerightspin(P);
        }
        //兄弟右结点为红
        else
        {
            X->color = B->color = red;
            P->color = B->right->color = black;
            if (GP->elem < P->elem)
                GP->right = Singlerightspin(P);
            else
                GP->left = Singlerightspin(P);
        }
    }
    //当前节点在P右边，情况讨论同上
    else
    {
        B = P->left;
        if (B->left->color == black && B->right->color == black)
        {
            P->right->color = P->left->color = red;
            P->color = black;

        }
        else if (B->left->color == red)
        {
            X->color = B->color = red;
            P->color = B->right->color = black;
            if (GP->elem < B->elem)
                GP->right = Singleleftspin(P);
            else
                GP->left = Singleleftspin(P);
        }
        else
        {
            X->color = red;
            P->color = black;
            if (GP->elem < B->elem)
                GP->right = Doubleleftspin(P);
            else
                GP->left = Doubleleftspin(P);
        }
    }
    NullNode->color = black;
}


//自顶向下的插入，可以使得不存在两层以上的红节点，保证了当父节点为红时，叔叔结点为黑的
RBTree RBTreeNode::Insert(int n, RBTree T)
{
    if (NullNode->elem == INT_FAST32_MAX)
        handleNull(T);
    antihandleNull(T);
    //对亲戚结点初始化
    X = P = GP = T;

    NullNode->elem = n;//NUllNOde结点元素指向要插入元素，遍历到空结点插入即可

    while (X->elem != n)
    {
        GGP = GP;
        GP = P;
        P = X;
        if (n < X->elem)
            X = X->left;
        else
            X = X->right;

        //在向下迭代的过程中，我们将改变有子结点都为红色的情况
        if (X->left->color == red && X->right->color == red)
            handlecolor(n, T);

    }

    if (X != NullNode)
        return NullNode;//X已经存在于树中，复制该值即可

    X = new RBTreeNode;//(RBTree)malloc(sizeof(Node));
    X->elem = n;
    X->left = X->right = NullNode;

    if (n < P->elem)
        P->left = X;
    else
        P->right = X;

    handlecolor(n, T);
    handleNull(T);
    return T;
}


//自顶向下的删除使得删除结点为红色
RBTree RBTreeNode::halfDelete(int n, RBTree T)
{
    //将假根涂红
    if (T->elem == -INT_FAST32_MAX)
    {
        T->color = red;
        R = T;
    }

    //每次迭代，进行亲戚更换
    GP = P;
    P = X;
    X = T;


    while (X->elem != n)
    {
        if (X->elem != P->elem)
        {
            GGP = GP;
            GP = P;
            P = X;
        }
        if (n < X->elem)
            X = X->left;
        else if (n > X->elem)
            X = X->right;
    hah:
        //如果子结点都为黑，为了下一次的迭代X是红的，需要进行处理
        if (X->left->color == black && X->right->color == black)
            handledel();

        else if (X->left->color == red && X->right->color == red)
        {
            if (X == R->right)
            {
                X->left->color = X->right->color = black;
                handledel();
            }
        }

        //当某一个结点为红（因为插入进行了处理，两个都是红节点只有在底层才可能出现）
        else
        {
            if (n == X->elem)
            {
                if (X->right->color == red)
                {
                    X->elem = FindMin(X->right)->elem;
                    halfDelete(X->elem, X->right);
                    return 0;
                }
                else
                {
                    X->elem = FindMax(X->left)->elem;
                    halfDelete(X->elem, X->left);
                    return 0;
                }
                break;
            }

            GGP = GP;
            GP = P;
            P = X;

            if (n < X->elem)
                X = X->left;
            else
                X = X->right;


            if (X->color != red)//兄弟结点为红色，B,P变色，旋转B,P
            {
                if (X->elem < P->elem)
                {
                    B = P->right;
                    B->color = black;
                    P->color = red;
                    if (GP->elem < B->elem)
                        GP->right = Singlerightspin(P);
                    else
                        GP->left = Singlerightspin(P);
                }
                else
                {
                    B = P->left;
                    B->color = black;
                    P->color = red;
                    if (GP->elem < B->elem)
                        GP->right = Singleleftspin(P);
                    else
                        GP->left = Singleleftspin(P);
                }
                goto hah;
            }
        }

    }


    //当前结点两个两个儿子都是叶子结点
    if (X->right == NullNode && X->left == NullNode)
    {
        if (X == P->left)
            P->left = NullNode;
        else
            P->right = NullNode;
    }

    //右节点为叶子，找左边最大的元素对当前替换，删除被替换结点
    else if (X->right == NullNode)
    {
        RBTree tem;
        RBTree l;
        l = X;
        tem = FindMax(X->left);
        //X->elem=tem->elem;
        halfDelete(tem->elem, X);
        l->elem = tem->elem;
        delete tem;//free(tem);
    }

    //左节点为叶子或者有两个子节点，找左边最大的元素对当前替换，删除被替换结点
    else
    {
        RBTree tem;
        RBTree l;
        l = X;
        tem = FindMin(X->right);
        //X->elem=tem->elem;
        halfDelete(tem->elem, X);
        l->elem = tem->elem;
        delete tem;//free(tem);
    }

    R->right->color = black;
    //Insert(NullNode->elem,T);
    return T;
}

void RBTreeNode::Delete(int n, RBTree p)
{
    antihandleNull(p);
    halfDelete(n, p);
    handleNull(p);
}

RBTree RBTreeNode::FindMin(RBTree bst)
{
    while (bst->left != NullNode)//左边不为空
        bst = bst->left;
    //左边为空，说明找到最小值了
    return bst;
}


//找最小值，也用迭代实现。就是拼命往左边找。
//但是这里的返回值不是指针，所以可以传入引用，用一个临时变量存起来就行
RBTree RBTreeNode::FindMax(RBTree bst)
{
    while (bst->right != NullNode)//左边不为空
        bst = bst->right;
    //左边为空，说明找到最小值了
    return bst;
}

//中序遍历，需要传入假根（头节点）的右节点
//void RBTreeNode::LNR(RBTree p)
//{
//    if (p != NULL)
//    {
//        LNR(p->left);
//        cout << (p->elem) << " " << p->color << "*" << "  " << "Height" << getHeight(p) << endl;
//        LNR(p->right);
//    }
//}


Position RBTreeNode::Singleleftspin(Position k2)
{
    Position k1;
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    return k1;//返回根节点
}

Position RBTreeNode::Singlerightspin(Position k2)
{
    Position k1;
    k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    return k1;//返回根结点
}

Position RBTreeNode::Doubleleftspin(Position k3)
{
    k3->left = Singlerightspin(k3->left);
    return Singleleftspin(k3);
}

Position RBTreeNode::Doublerightspin(Position k3)
{
    k3->right = Singleleftspin(k3->right);
    return Singlerightspin(k3);
}

RBTree RBTreeNode::handleNull(RBTree p)
{
    if (p == NullNode)
        p = NULL;
    else
    {
        p->left = handleNull(p->left);
        p->right = handleNull(p->right);
    }
    return p;
}

RBTree RBTreeNode::antihandleNull(RBTree p)
{
    if (p == NULL)
        p = NullNode;
    else
    {
        p->left = antihandleNull(p->left);
        p->right = antihandleNull(p->right);
    }
    return p;
}


int RBTreeNode::getColor()
{
    return this->color;//黑色为1，红色为0
}

int RBTreeNode::getElem()
{
    return this->elem;
}

RBTree& RBTreeNode::getLeft()
{
    return this->left;
}

RBTree& RBTreeNode::getRight()
{
    return this->right;
}

void RBTreeNode::Clear(RBTreeNode* &a)
{
    if (a != nullptr)
    {
        Clear(a->getLeft());
        Clear(a->getRight());
        delete a;
        a = nullptr;
        NullNode=nullptr;
    }
}
