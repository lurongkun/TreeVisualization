#include "widget.h"
#include"Functions.h"
#include<QMessageBox>
#include<windows.h>
#define WindowLength 635
#define WindowWidth 896
#define ElemStratX 275
#define ElemStratY 480

typedef BinarySearchTree BSTNode;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(WindowWidth,WindowLength); //固定窗口大小
    this->setWindowTitle("三棵树");
    //先置空
    BSTroot=nullptr;
    AVLroot=nullptr;
    RBTroot=nullptr; //可以空遍历,但是不能有了插入后再删除干净的遍历
    //RBTroot->getRight()=nullptr;

    //连接切换普通二叉树键和响应
    connect(ui->BSTButton,&QPushButton::clicked,this,[=](){
        if(timer_id) killTimer(timer_id);
        isTravel=false; //退出遍历状态
        new_elem=-1;
        currentTree=BSTREE;
        update(); //重新调用绘图函数
    });

    //连接切换平衡二叉树键和响应
    connect(ui->AVLButton,&QPushButton::clicked,this,[=](){
        if(timer_id) killTimer(timer_id);
        isTravel=false; //退出遍历状态
        new_elem=-1;
        currentTree=AVLTREE;
        update();
    });

    //连接切换红黑树键和响应
    connect(ui->RBTButton,&QPushButton::clicked,this,[=](){
        if(timer_id) killTimer(timer_id);
        isTravel=false; //退出遍历状态
        new_elem=-1;
        currentTree=RBTREE;
        update();
    });

    //连接插入键和响应
    connect(ui->insertButton,&QPushButton::clicked,this,[=](){
        if(timer_id) killTimer(timer_id);
        isTravel=false; //退出遍历状态
        switch (currentTree)
        {
        case BSTREE: insert_button_clicked(BSTroot); break;
        case AVLTREE: insert_button_clicked(AVLroot); break;
        case RBTREE: insert_button_clicked(RBTroot); break;
        default: break;
        }
    });

    //连接删除键和响应
    connect(ui->deleteButton,&QPushButton::clicked,this,[=](){
        if(timer_id) killTimer(timer_id);
        isTravel=false; //退出遍历状态
        switch (currentTree)
        {
        case BSTREE: delete_button_clicked(BSTroot); break;
        case AVLTREE: delete_button_clicked(AVLroot); break;
        case RBTREE: delete_button_clicked(RBTroot); break;
        default: break;
        }
    });

    //连接清除键和响应
    connect(ui->clearButton,&QPushButton::clicked,this,[=](){
        if(!timer_id) killTimer(timer_id);
        isTravel=false; //退出遍历状态
        QMessageBox::StandardButton choice = QMessageBox::question(this," ","确认删除整棵树吗？",QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
        if(choice==QMessageBox::Yes)
        {
            switch (currentTree)
            {
            case BSTREE: Clear(BSTroot); break;
            case AVLTREE: Clear(AVLroot); break;
            case RBTREE: fakeRoot->Clear(RBTroot); break;
            default: break;
            }
            update();
        }
    });

    //连接前序遍历键和响应
    connect(ui->NLRButton,&QPushButton::clicked,this,[=](){
        if(timer_id) killTimer(timer_id);
        new_elem=-1; //把新元素标记清除      
        resetQueue(); //重置队列
        //将当前的树入队
        switch (currentTree)
        {
        case BSTREE: pushTreeNLR(BSTroot,BSTlayout.firstCircleCenter,BSTlayout); break;
        case AVLTREE: pushTreeNLR(AVLroot,AVLlayout.firstCircleCenter,AVLlayout); break;
        case RBTREE:
            if(RBTroot!=nullptr)            
                pushTreeNLR(RBTroot->getRight(),RBTlayout.firstCircleCenter,RBTlayout);            
            break;
        default: break;
        }        
        beginTime();
    });

    //连接中序遍历键和响应
    connect(ui->LNRButton,&QPushButton::clicked,this,[=](){
        if(timer_id) killTimer(timer_id);
        new_elem=-1; //把新元素标记清除
        resetQueue(); //重置队列
        //将当前的树入队
        switch (currentTree)
        {
        case BSTREE: pushTreeLNR(BSTroot,BSTlayout.firstCircleCenter,BSTlayout); break;
        case AVLTREE: pushTreeLNR(AVLroot,AVLlayout.firstCircleCenter,AVLlayout); break;
        case RBTREE:
            if(RBTroot!=nullptr)
                pushTreeLNR(RBTroot->getRight(),RBTlayout.firstCircleCenter,RBTlayout);
            break;
        default: break;
        }
        beginTime();
    });

    //连接后序遍历键和响应
    connect(ui->LRNButton,&QPushButton::clicked,this,[=](){
        if(timer_id) killTimer(timer_id);
        new_elem=-1; //把新元素标记清除
        resetQueue(); //重置队列
        //将当前的树入队
        switch (currentTree)
        {
        case BSTREE: pushTreeLRN(BSTroot,BSTlayout.firstCircleCenter,BSTlayout); break;
        case AVLTREE: pushTreeLRN(AVLroot,AVLlayout.firstCircleCenter,AVLlayout); break;
        case RBTREE:
            if(RBTroot!=nullptr)
                pushTreeLRN(RBTroot->getRight(),RBTlayout.firstCircleCenter,RBTlayout);
            break;
        default: break;
        }
        beginTime();
    });

    //连接层序遍历键和响应
    connect(ui->LevelButton,&QPushButton::clicked,this,[=](){
        if(timer_id) killTimer(timer_id);
        new_elem=-1; //把新元素标记清除
        resetQueue(); //重置队列
        //将当前的树入队
        switch (currentTree)
        {
        case BSTREE: pushTreeLevel(BSTroot,BSTlayout.firstCircleCenter,BSTlayout); break;
        case AVLTREE: pushTreeLevel(AVLroot,AVLlayout.firstCircleCenter,AVLlayout); break;
        case RBTREE:
            if(RBTroot!=nullptr)
                pushTreeLevel(RBTroot->getRight(),RBTlayout.firstCircleCenter,RBTlayout);
            break;
        default: break;
        }
        beginTime();
    });

    //连接随机生成键和响应
    connect(ui->randButton,&QPushButton::clicked,this,[=](){
        if(timer_id) killTimer(timer_id);
        isTravel=false; //退出遍历状态
        new_elem=-1;
        switch (currentTree)
        {
        case BSTREE: buildRandTree(BSTroot); break;
        case AVLTREE: buildRandTree(AVLroot); break;
        case RBTREE: buildRandTree(RBTroot); break;
        default: break;
        }
        update();
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerEvent(QTimerEvent *)
{
    if(!node_position_queue.empty())
        travelingPoint=node_position_queue.dequeue();
    update();
}

void Widget::paintEvent(QPaintEvent* )
{
    QPainter painter(this); //在当前窗口画画
    painter.setRenderHint(QPainter::Antialiasing); //设置初级抗锯齿，但是会对性能有一定影响
    //判断是否需要画遍历
    if(isTravel)
    {
        painter.setPen(QPen(QColor(144,31,229,127),3));
        painter.drawEllipse(travelingPoint,BSTlayout.radius+6,BSTlayout.radius+6); //画圆
        if(node_position_queue.empty())
        {
            isTravel=false;
            killTimer(timer_id);
            isFinishTravel=1;
        }
    }

    //判断是否要开始画字
    if(isFinishTravel)
    {
        //画下标
        painter.setPen(QPen(Qt::red,3));
        QFont font("微软雅黑",11); //设置字体和大小
        painter.setFont(font); //使用设置的字体
        int i=1;
        while(!num_position_queue.empty())
        {
            if(i<10)
                painter.drawText(num_position_queue.head().x()-5,num_position_queue.head().y()+35,QString::number(i));
            else
                painter.drawText(num_position_queue.head().x()-9,num_position_queue.head().y()+35,QString::number(i));
            num_position_queue.pop_front();
            ++i;
        }

        //画所有元素
        painter.setPen(QPen(Qt::black,3));
        int startx=ElemStratX,starty=ElemStratY; //输出元素的坐标
        int cnt=0; //记录输出了几次元素
        while(!node_elem_queue.empty())
        {
            painter.drawText(startx,starty,QString::number(node_elem_queue.dequeue()));
            ++cnt;
            if(cnt%10!=0) //十个换一行
            {
                startx+=40;
            }
            else
            {
                starty+=30;
                startx=ElemStratX;
            }
        }
        isFinishTravel=false;
    }

    QFont font("微软雅黑",20); //设置字体和大小
    painter.setPen(QPen(Qt::black,3));
    painter.setFont(font); //使用设置的字体
    if(currentTree==BSTREE)
    {
        painter.drawText(QRect(350,20,400,50),"普通二叉搜索树");
        if(BSTroot!=nullptr) //如果树不为空
        {
            drawNode(new_elem,BSTroot,BSTlayout.firstCircleCenter,&painter,BSTlayout); //画整棵树
        }

    }
    else if(currentTree==AVLTREE)
    {
        painter.drawText(QRect(375,20,400,50),"平衡二叉树");
        if(AVLroot!=nullptr) //如果树不为空
        {
            drawNode(new_elem,AVLroot,AVLlayout.firstCircleCenter,&painter,AVLlayout); //画整棵树
        }
    }
    else
    {
        painter.drawText(QRect(400,20,400,50),"红黑树");
        if(RBTroot!=nullptr) //如果树不为空
        {
            drawNode(new_elem,RBTroot->getRight(),RBTlayout.firstCircleCenter,&painter,RBTlayout); //画整棵树
        }
    }
}

bool Widget::checkInput(std::string& num) //判断输入是否符合要求
{
    int len=num.length();
    bool correct=true;
    //判断输入是否符合要求
    if(len==0) //长度等于0，即没有输入
    {
        correct=false;
    }
    else if(len<=3) //如果输入的数字超过3位就报错
    {
        for(int i=0;i<len;++i) //如果输入的不是数字就报错
        {
            if(!(num[i]-'0'>=0&&num[i]-'0'<=9))
            {
                correct=false;
            }
        }
    }
    else //长度大于三
    {       
        correct=false;
    }

    if(!correct)
        QMessageBox::critical(this,"ERROR","输入不符合要求");
    return correct;
}

void Widget::beginTime() //开始计时
{
    if(currentTree==BSTREE)
    {
        if(BSTroot!=nullptr) //如果树不为空
        {
            timer_id=startTimer(interval);
            Sleep(interval);
            isTravel=true; //进入遍历状态
        }
    }
    else if(currentTree==AVLTREE)
    {
        if(AVLroot!=nullptr) //如果树不为空
        {
            timer_id=startTimer(interval);
            Sleep(interval);
            isTravel=true; //进入遍历状态
        }
    }
    else
    {
        if(RBTroot!=nullptr) //如果树不为空
        {
            timer_id=startTimer(interval);
            Sleep(interval);
            isTravel=true; //进入遍历状态
        }
    }
}

void Widget::resetQueue() //重置所有队列
{
    //如果队不空，先清除队
    if(!node_elem_queue.empty())
    {
        node_elem_queue.clear();
    }
    if(!node_position_queue.empty())
    {
        node_position_queue.clear();
    }
    if(!num_position_queue.empty())
    {
        num_position_queue.clear();
    }
}

void Widget::insert_button_clicked(RBTreeNode* &root)
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
               // qDebug()<<"为空插入";
                fakeRoot = new RBTreeNode(value,root,this); //就创建一棵新树并放进对象树里
                ui->inputLineEdit->setText(""); //将输入框置空
                new_elem=value; //更新元素
                update(); //重新调用画图函数
            }
            else //不为空
            {
                fakeRoot->Insert(value,root); //在以root为根节点的树中插入
                int height=getHeight(root->getRight());
                if(height>5) //树高大于5，报错
                {
                    fakeRoot->Delete(value,root); //把刚才加进去的节点删掉
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

void Widget::delete_button_clicked(RBTreeNode* &root)
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
            fakeRoot->Delete(value,root);
            new_elem=-1; //重置新元素
            ui->inputLineEdit->setText(""); //将输入框置空
            update(); //重新调用画图函数
        }
    }
}

void Widget::drawNode(int new_elem,RBTreeNode* node,QPoint center,QPainter* painter,TreeLayout<RBTreeNode*> layout)
{
    if(node==nullptr) return;
    //画圆
    painter->setPen(QPen(Qt::black,3)); //设置画笔形式,黑色，粗度为3

    //判断红黑
    if(node->getColor()==red)
        painter->setBrush(QBrush(Qt::red));
    else
        painter->setBrush(QBrush(Qt::black));

    if(node->getElem()==new_elem)
    {
        painter->setPen(QPen(QColor(144,31,229,127),4));
        painter->drawEllipse(center,layout.radius,layout.radius); //画圆
        painter->drawLine(center.x()-9,center.y()+layout.radius+6,center.x()+9,center.y()+layout.radius+6);
        painter->setPen(QPen(Qt::black,3));
    }
    else
    {
        if(node->getColor()==red)
            painter->setPen(QPen(Qt::red,3));
        else
            painter->setPen(QPen(Qt::black,3));
        painter->drawEllipse(center,layout.radius,layout.radius); //画圆
    }

    //画数字
    painter->setPen(QPen(Qt::white,3));
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
    painter->setPen(QPen(Qt::black,3));
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

void Widget::buildRandTree(RBTreeNode* &root)
{
    if(root!=nullptr)
    {
        QMessageBox::StandardButton choice = QMessageBox::question(this," ","随机生成将覆盖已有的树，是否继续？",QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
        if(choice==QMessageBox::Yes)
        {
            fakeRoot->Clear(root);
        }
        else
            return;
    }
    //C++11随机数生成引擎
    std::default_random_engine engine(static_cast<int>(time(0)));
    std::uniform_int_distribution<int> randNum(RMIN, RMAX);
    int num=randNum(engine);
    fakeRoot = new RBTreeNode(num,root,this); //就创建一棵新树并放进对象树里
    num=randNum(engine);
    fakeRoot->Insert(num,root);
    for (int i = 1; i < 3; ++i)
    {
        num=randNum(engine);
        while(isInTree(num,root)) //若重复，重新生成
        {
            num=randNum(engine);
        }
        fakeRoot->Insert(num,root);
        fakeRoot->Insert(num-43,root);
        fakeRoot->Insert(num+49,root);
    }
}
