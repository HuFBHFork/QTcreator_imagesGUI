#ifndef SCENEDRAW_RECT_SR_H
#define SCENEDRAW_RECT_SR_H


/*
 * SceneDraw_Rect_SR类：
 * 用于绘制交互创建：LabelItem_Rect_SR对象
 * LabelItem_Rect_SR对象支持鼠标交互调整大小与旋转
 *
*/


#include"Scene/scenedraw.h"
#include<QGraphicsRectItem>

class SceneDraw_Rect_SR:public SceneDraw
{
public:
    SceneDraw_Rect_SR();
    ~SceneDraw_Rect_SR();

    //类族规约：类ID
    enum {ShapeType=3};
    int myType() const override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event,QGraphicsScene *scene) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event,QGraphicsScene *scene)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event,QGraphicsScene *scene)override;

private:
    QGraphicsRectItem *tmpRect=nullptr;
};

#endif // SCENEDRAW_RECT_SR_H
