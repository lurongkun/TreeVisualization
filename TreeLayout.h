#ifndef TREELAYOUT_H
#define TREELAYOUT_H
#define Rootx 448
#define Rooty 230
#include<QPoint>

//*************************************************//
//                                                 //
//    这个类专门用于确定下一个节点和线的位置          //
//                干脆叫他“树的布局”                //
//                                                //
//************************************************//


template<class Tree>
class TreeLayout
{
public:

    QPoint leftNodeCenter(QPoint currentNodeCenter,Tree& tree); //(如果左节点存在的话)获取其他左节点的圆心
    QPoint rightNodeCenter(QPoint currentNodeCenter,Tree& tree); //(如果右节点存在的话)获取其他右节点的圆心

    QPoint leftLineStart(QPoint currentNodeCenter); //获取其他节点的左边线的开始位置
    QPoint leftLineEnd(QPoint currentNodeCenter,Tree& tree); //获取其他节点的左边线的结束位置

    QPoint rightLineStart(QPoint currentNodeCenter); //获取其他节点的右边线的开始位置
    QPoint rightLineEnd(QPoint currentNodeCenter,Tree& tree); //获取其他节点的右边线的结束位置

    QPoint firstCircleCenter = QPoint(Rootx,Rooty); //根节点圆心
    const int radius = 16; //节点半径
    QPoint firstLeftLineStart = QPoint(firstCircleCenter.x()-radius/1.414,firstCircleCenter.y()+radius/1.414); //根节点左边线的开始点
    QPoint firstRightLineStart = QPoint(firstCircleCenter.x()+radius/1.414,firstCircleCenter.y()+radius/1.414); //根节点右边线的开始点
    const int linedx = 8; //连接两节点之间的线的两个端点之间的横坐标差值dx,取正
    const int linedy = 20; //连接两节点之间的线的两个端点之间的纵坐标差值dy,取正

};

template<class Tree>
QPoint TreeLayout<Tree>::leftNodeCenter(QPoint currentNodeCenter,Tree& tree) //(如果左节点存在的话)算出左节点的圆心
{
    int endx=currentNodeCenter.x()-(2*radius/1.414+linedx);
    int endy=currentNodeCenter.y()+(2*radius/1.414+linedy);
    int Lheight=getHeight(tree->getLeft());
    if(Lheight>=2) //左树高大于等于2时开始调整
    {
        endx=currentNodeCenter.x()-(3*radius+linedx)*(1<<(Lheight-2));
    }
    return QPoint(endx,endy);
}

template<class Tree>
QPoint TreeLayout<Tree>::rightNodeCenter(QPoint currentNodeCenter,Tree& tree) //(如果右节点存在的话)算出右节点的圆心
{
    int endx=currentNodeCenter.x()+(2*radius/1.414+linedx);
    int endy=currentNodeCenter.y()+(2*radius/1.414+linedy);
    int Rheight=getHeight(tree->getRight());
    if(Rheight>=2) //右树高大于等于2时开始调整
    {
        endx=currentNodeCenter.x()+(3*radius+linedx)*(1<<(Rheight-2));
    }
    return QPoint(endx,endy);
}

template<class Tree>
QPoint TreeLayout<Tree>::leftLineStart(QPoint currentNodeCenter) //获取其他节点的左边线的开始位置
{
    return QPoint(currentNodeCenter.x()-radius/1.414-1,currentNodeCenter.y()+radius/1.414+1);
}

template<class Tree>
QPoint TreeLayout<Tree>::leftLineEnd(QPoint currentNodeCenter,Tree& tree) //获取其他节点的左边线的结束位置
{
    QPoint temp=leftNodeCenter(currentNodeCenter,tree);
    return QPoint(temp.x()+radius/1.414,temp.y()-radius/1.414);
}

template<class Tree>
QPoint TreeLayout<Tree>::rightLineStart(QPoint currentNodeCenter) //获取其他节点的右边线的开始位置
{
    return QPoint(currentNodeCenter.x()+radius/1.414+1,currentNodeCenter.y()+radius/1.414+2);
}

template<class Tree>
QPoint TreeLayout<Tree>::rightLineEnd(QPoint currentNodeCenter,Tree& tree) //获取其他节点的右边线的结束位置
{
    QPoint temp=rightNodeCenter(currentNodeCenter,tree);
    return QPoint(temp.x()-radius/1.414,temp.y()-radius/1.414);
}

#endif // TREELAYOUT_H

