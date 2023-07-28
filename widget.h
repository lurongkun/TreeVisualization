#ifndef WIDGET_H
#define WIDGET_H
#define BSTREE 1
#define AVLTREE 2
#define RBTREE 3
#define BSTLAYOUT 10
#define AVLLAYOUT 11
#define RBTLAYOUT 12
#define RMAX 110
#define RMIN 60
#include<QPainter>
#include<QPoint>
#include<QWidget>
#include<QString>
#include<QDebug>
#include<QMessageBox>
#include<QQueue>
#include<string>
#include<random>
#include<ctime>
#include"TreeLayout.h"
#include "ui_widget.h"
#include"AVLTree.h"
#include"RBTree.h"
#include"BinarySearchTree.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    typedef BinarySearchTree BSTNode;
    typedef BinarySearchTree* BSTree;
    typedef AVLTree AVLNode;
    typedef AVLTree* AVL;
    typedef RBTreeNode RBTNode;
    typedef RBTreeNode* RBTree;

    Widget(QWidget *parent = nullptr);
    ~Widget();

    TreeLayout<BSTree> BSTlayout; //布局类对象放在这里，方便扩展和使用
    BinarySearchTree* BSTroot=new BSTNode(this); //放进对象树

    TreeLayout<AVL> AVLlayout;
    AVLTree* AVLroot=new AVLNode(this); //放进对象树

    TreeLayout<RBTree> RBTlayout;
    RBTree fakeRoot=new RBTNode(this); //放进对象树
    RBTreeNode* RBTroot=new RBTNode(this);  //放进对象树,插入或删除的时候传入RBTroot,遍历的时候传入RBTroot->right

    int currentTree = BSTREE; //初始化树为普通二叉树
    int currentLayout = BSTLAYOUT; //初始化布局为普通二叉树布局

    int new_elem=-1; //记录最新插入的元素，用于标记
    bool isTravel=0; //记录是否需要遍历
    bool isFinishTravel=0; //记录遍历是否完成，也就是是否要下标
    int timer_id=0; //用来控制计时器的停止
    int interval=480; //遍历间隔
    QPoint travelingPoint; //正在遍历的节点位置


    QQueue<QPoint> node_position_queue; //节点的位置队列
    QQueue<QPoint> num_position_queue; //数字的位置队列
    QQueue<int> node_elem_queue; //元素的位置队列

    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

    bool checkInput(std::string& num); //检测输入是否正确

    void beginTime(); //开始计时

    void resetQueue(); //重置所有队列

    template<typename TreeNode>
    void drawNode(int new_elem,TreeNode* node,QPoint center,QPainter* painter,TreeLayout<TreeNode*> layout); //画节点函数用模板，方便扩展

    template<typename Treeroot>
    void pushTreeNLR(Treeroot* &root,QPoint center,TreeLayout<Treeroot*> layout); //前序遍历将整棵树的节点和元素入队

    template<typename Treeroot>
    void pushTreeLNR(Treeroot* &root,QPoint center,TreeLayout<Treeroot*> layout); //中序遍历将整棵树的节点和元素入队

    template<typename Treeroot>
    void pushTreeLRN(Treeroot* &root,QPoint center,TreeLayout<Treeroot*> layout); //后序遍历将整棵树的节点和元素入队

    template<typename Treeroot>
    void pushTreeLevel(Treeroot* &root,QPoint center,TreeLayout<Treeroot*> layout); //层序遍历将整棵树的节点和元素入队

    template<typename Treeroot>
    void insert_button_clicked(Treeroot* &root);

    template<typename Treeroot>
    void delete_button_clicked(Treeroot* &root);

    template<typename Treeroot>
    void buildRandTree(Treeroot* &root);

    //给红黑树提供一个重载，因为其底层实现的方式不同于其他两棵树，传入RBTroot->right
    void insert_button_clicked(RBTreeNode* &root);
    void delete_button_clicked(RBTreeNode* &root);
    void drawNode(int new_elem,RBTreeNode* node,QPoint center,QPainter* painter,TreeLayout<RBTreeNode*> layout);
    void buildRandTree(RBTreeNode* &root);

private:
    Ui::Widget *ui;
};

template<typename Treeroot>
void Widget::pushTreeNLR(Treeroot* &root,QPoint center,TreeLayout<Treeroot*> layout) //前序将整棵树的节点和元素入队
{

        if(root==nullptr)
        {
            //qDebug()<<"空";
            return; //根为空，直接返回
        }
        //节点入队
        node_elem_queue.push_back(root->getElem());
        node_position_queue.push_back(center);
        num_position_queue.push_back(center);
        //递归入队
        if(root->getLeft()!=nullptr)
        {
            pushTreeNLR(root->getLeft(),layout.leftNodeCenter(center,root),layout);
        }
        if(root->getRight()!=nullptr)
        {
            pushTreeNLR(root->getRight(),layout.rightNodeCenter(center,root),layout);
        }
}

template<typename Treeroot>
void Widget::pushTreeLNR(Treeroot* &root,QPoint center,TreeLayout<Treeroot*> layout) //中序遍历将整棵树的节点和元素入队
{
    if(root==nullptr) return; //根为空，直接返回
    //递归入队
    if(root->getLeft()!=nullptr)
    {
        pushTreeLNR(root->getLeft(),layout.leftNodeCenter(center,root),layout);
    }
    //节点入队
    node_elem_queue.push_back(root->getElem());
    node_position_queue.push_back(center);
    num_position_queue.push_back(center);
    if(root->getRight()!=nullptr)
    {
        pushTreeLNR(root->getRight(),layout.rightNodeCenter(center,root),layout);
    }
}

template<typename Treeroot>
void Widget::pushTreeLRN(Treeroot* &root,QPoint center,TreeLayout<Treeroot*> layout) //后序遍历将整棵树的节点和元素入队
{
    if(root==nullptr) return; //根为空，直接返回
    //递归入队
    if(root->getLeft()!=nullptr)
    {
        pushTreeLRN(root->getLeft(),layout.leftNodeCenter(center,root),layout);
    }
    if(root->getRight()!=nullptr)
    {
        pushTreeLRN(root->getRight(),layout.rightNodeCenter(center,root),layout);
    }
    //节点入队
    node_elem_queue.push_back(root->getElem());
    node_position_queue.push_back(center);
    num_position_queue.push_back(center);
}

template<typename Treeroot>
void Widget::pushTreeLevel(Treeroot* &root,QPoint center,TreeLayout<Treeroot*> layout) //层序遍历将整棵树的节点和元素入队
{
    if(root==nullptr) return;

    QQueue<Treeroot*> temp_node_queue; //新建两个临时队列用于充当“工具队”
    temp_node_queue.push_back(root);
    QQueue<QPoint> temp_position_queue;
    temp_position_queue.push_back(center);

    node_elem_queue.push_back(root->getElem()); //先将头节点信息入队
    node_position_queue.push_back(center);
    num_position_queue.push_back(center);

    Treeroot* pMove; //始终表示temp_node_queue的头元素
    QPoint cMove; //始终表示temp_position_queue的头元素

    while(!temp_node_queue.empty())
    {
        //给pMove和cMove赋值，并更新两个临时队列
        cMove=temp_position_queue.front();
        temp_position_queue.pop_front();
        pMove=temp_node_queue.front();
        temp_node_queue.pop_front();

        if(pMove->getLeft()!=nullptr)
        {
            temp_node_queue.push_back(pMove->getLeft());
            temp_position_queue.push_back(layout.leftNodeCenter(cMove,pMove));
            node_elem_queue.push_back(pMove->getLeft()->getElem());
            node_position_queue.push_back(temp_position_queue.back()); //把临时队列的末尾元素(即最新的元素)放进真正需要遍历的队列中
            num_position_queue.push_back(temp_position_queue.back());
        }
        if(pMove->getRight()!=nullptr)
        {
            temp_node_queue.push_back(pMove->getRight());
            temp_position_queue.push_back(layout.rightNodeCenter(cMove,pMove));
            node_elem_queue.push_back(pMove->getRight()->getElem());
            node_position_queue.push_back(temp_position_queue.back());
            num_position_queue.push_back(temp_position_queue.back());
        }
    }
}

template<typename TreeNode>
void Widget::drawNode(int new_elem,TreeNode* node,QPoint center,QPainter* painter,TreeLayout<TreeNode*> layout)
{
    if(node==nullptr) return;
    //画圆
    painter->setPen(QPen(Qt::black,3)); //设置画笔形式,黑色，粗度为3
    if(node->getElem()==new_elem)
    {
        painter->setPen(QPen(QColor(144,31,229,127),3));
        painter->drawEllipse(center,layout.radius,layout.radius); //画圆
        painter->drawLine(center.x()-9,center.y()+layout.radius+6,center.x()+9,center.y()+layout.radius+6);
        painter->setPen(QPen(Qt::black,3));
    }
    else
    {
        painter->drawEllipse(center,layout.radius,layout.radius); //画圆
    }

    //画数字
    QFont font("微软雅黑",10); //设置字体和大小
    painter->setFont(font); //使用设置的字体   
    //下面根据输入数字的位数不同，设置不同的数字的位置
    int num=node->getElem();
    QPoint textCenter;
    if(num<10) //0~9
        textCenter=QPoint(center.x()-4,center.y()+4);
    else if(num<100) //10~99
        textCenter=QPoint(center.x()-8,center.y()+4);
    else //100~999
        textCenter=QPoint(center.x()-12,center.y()+4);
    painter->drawText(textCenter,QString::number(num)); //画数字

    //画线
    if(node->getLeft()!=nullptr)
    {
        //画左节点的线
        painter->drawLine(layout.leftLineStart(center),layout.leftLineEnd(center,node));
    }
    if(node->getRight()!=nullptr)
    {
        //画右节点的线
        painter->drawLine(layout.rightLineStart(center),layout.rightLineEnd(center,node));
    }

    //递归
    if(node->getLeft()!=nullptr)
    {
        //将左节点当作头节点
        drawNode(new_elem,node->getLeft(),layout.leftNodeCenter(center,node),painter,layout);
    }
    if(node->getRight()!=nullptr)
    {
        //将右节点当作头节点
        drawNode(new_elem,node->getRight(),layout.rightNodeCenter(center,node),painter,layout);
    }
}

template<typename Treeroot>
void Widget::insert_button_clicked(Treeroot* &root)
{
    QString QNum=ui->inputLineEdit->text();
    std::string num = QNum.toStdString();
    if(checkInput(num))//如果输入正确
    {
        int value=ui->inputLineEdit->text().toInt(); //将输入的内容从Qstring转为int
        if(isInTree(value,root)) //如果树里面已经有了输入的元素，就报错
        {
            QMessageBox::critical(this,"ERROR","该数字已存在");
            ui->inputLineEdit->setText(""); //将输入框置空
        }
        else //输入的为新的元素
        {
            if(root==nullptr) //如果树为空
            {
                root = new Treeroot(value,this); //就创建一棵新树并放进对象树里
                ui->inputLineEdit->setText(""); //将输入框置空
                new_elem=value; //更新元素
                //qDebug() <<"输入了";
                update(); //重新调用画图函数
            }
            else //不为空
            {
                root->Insert(value,root); //在以root为根节点的树中插入
                //qDebug() <<"插入了";
                int height=getHeight(root);
                if(height>5) //树高大于5，报错
                {
                    root->Delete(value,root); //把刚才加进去的节点删掉
                    QMessageBox::critical(this,"ERROR","树将超过5层");
                    ui->inputLineEdit->setText(""); //将输入框置空
                }
                else
                {
                    new_elem=value; //更新元素
                    ui->inputLineEdit->setText(""); //将输入框置空
                    update(); //重新调用画图函数
                }

            }
        }
    }
}

template<typename Treeroot>
void Widget::delete_button_clicked(Treeroot* &root)
{
    QString QNum=ui->inputLineEdit->text();
    std::string num = QNum.toStdString();
    if(checkInput(num))//如果输入正确
    {
        int value=ui->inputLineEdit->text().toInt(); //将输入的内容从Qstring转为int
        if(!isInTree(value,root)) //如果树里面不存在输入的元素，就报错
        {
            QMessageBox::critical(this,"ERROR","未找到该数");
            ui->inputLineEdit->setText(""); //将输入框置空
        }
        else //输入的为已存在的元素
        {
            root->Delete(value,root);
            new_elem=-1; //重置新元素
            ui->inputLineEdit->setText(""); //将输入框置空
            update(); //重新调用画图函数
        }
    }
}

template<typename Treeroot>
void Widget::buildRandTree(Treeroot* &root)
{
    if(root!=nullptr)
    {
        QMessageBox::StandardButton choice = QMessageBox::question(this," ","随机生成将覆盖已有的树，是否继续？",QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
        if(choice==QMessageBox::Yes)
        {
            Clear(root);
        }
        else
            return;
    }

    //C++11随机数生成引擎
    std::default_random_engine engine(static_cast<int>(time(0)));
    std::uniform_int_distribution<int> randNum(RMIN, RMAX);

    int num=randNum(engine);
    root = new Treeroot(num,this); //就创建一棵新树并放进对象树里
    num=randNum(engine);
    root->Insert(num,root);
    for (int i = 1; i < 3; ++i)
    {
        num=randNum(engine);
        while(isInTree(num,root)) //若重复，重新生成
        {
            num=randNum(engine);
        }
        root->Insert(num,root);
        root->Insert(num-53,root);
        root->Insert(num+57,root);
    }
}



#endif // WIDGET_H
