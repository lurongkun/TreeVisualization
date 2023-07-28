#include "treelayout.h"
#include"binarysearchtree.h"
#include"Functions.h"
#include<QDebug>
typedef BinarySearchTree* Tree;




//QPoint TreeLayout::leftNodeCenter(QPoint currentNodeCenter,Tree& tree) //(如果左节点存在的话)算出左节点的圆心
//{
//    int endx=currentNodeCenter.x()-(2*radius/1.414+linedx);
//    int endy=currentNodeCenter.y()+(2*radius/1.414+linedy);
//    int Lheight=getHeight(tree->getLeft());
//    if(Lheight>=2) //左树高大于等于2时开始调整
//    {
//        endx=currentNodeCenter.x()-(3*radius+linedx)*(1<<(Lheight-2));
//    }
//    return QPoint(endx,endy);
//}


//QPoint TreeLayout::rightNodeCenter(QPoint currentNodeCenter,Tree& tree) //(如果右节点存在的话)算出右节点的圆心
//{
//    int endx=currentNodeCenter.x()+(2*radius/1.414+linedx);
//    int endy=currentNodeCenter.y()+(2*radius/1.414+linedy);
//    int Rheight=getHeight(tree->getRight());
//    if(Rheight>=2) //右树高大于等于2时开始调整
//    {
//        endx=currentNodeCenter.x()+(3*radius+linedx)*(1<<(Rheight-2));
//    }
//    return QPoint(endx,endy);
//}


//QPoint TreeLayout::leftLineStart(QPoint currentNodeCenter) //获取其他节点的左边线的开始位置
//{
//    return QPoint(currentNodeCenter.x()-radius/1.414,currentNodeCenter.y()+radius/1.414);
//}


//QPoint TreeLayout::leftLineEnd(QPoint currentNodeCenter,Tree& tree) //获取其他节点的左边线的结束位置
//{
//    QPoint temp=leftNodeCenter(currentNodeCenter,tree);
//    return QPoint(temp.x()+radius/1.414,temp.y()-radius/1.414);
//}


//QPoint TreeLayout::rightLineStart(QPoint currentNodeCenter) //获取其他节点的右边线的开始位置
//{
//    return QPoint(currentNodeCenter.x()+radius/1.414,currentNodeCenter.y()+radius/1.414);
//}


//QPoint TreeLayout::rightLineEnd(QPoint currentNodeCenter,Tree& tree) //获取其他节点的右边线的结束位置
//{
//    QPoint temp=rightNodeCenter(currentNodeCenter,tree);
//    return QPoint(temp.x()-radius/1.414,temp.y()-radius/1.414);
//}

