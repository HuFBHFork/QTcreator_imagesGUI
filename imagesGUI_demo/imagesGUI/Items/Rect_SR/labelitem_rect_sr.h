#ifndef LABELITEM_RECT_SR_H
#define LABELITEM_RECT_SR_H

/*
 * LabelItem_Rect_SR类：
 * 绘制交互创建的代理对象是：SceneDraw_Rect_SR对象
 * LabelItem_Rect_SR对象支持鼠标交互调整大小、鼠标交互旋转
 *
*/

#include<QGraphicsRectItem>
#include"graphicsitemadjuster.h"

class LabelItem_Rect_SR:public QGraphicsRectItem
{
public:

    explicit LabelItem_Rect_SR(const QRectF &rect, QGraphicsItem *parent = Q_NULLPTR);
    virtual ~LabelItem_Rect_SR();


private:
    void new_ajuster();
    QTransform caculaMatrix(QPointF s1,QPointF s2,QPointF p1,QPointF p2);//由向量计算仿射变换矩阵
    GraphicsItemAdjuster *_ajuster;

    QPointF _lastTranslate_mousePos;
};

#endif // LABELITEM_RECT_SR_H
