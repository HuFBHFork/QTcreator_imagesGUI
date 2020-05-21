#ifndef SCENEDRAW_RECT_H
#define SCENEDRAW_RECT_H

#include"Scene/scenedraw.h"

#include<QGraphicsRectItem>


/*
 * SceneDraw_Rect类：
 * 演示对LabelWidget的扩展：绘制一个简单的矩形
 *
*/

class SceneDraw_Rect:public SceneDraw
{
public:
    SceneDraw_Rect();
    ~SceneDraw_Rect();

    //类族规约：类ID
    enum {ShapeType=1};
    int myType() const override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event,QGraphicsScene *scene) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event,QGraphicsScene *scene)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event,QGraphicsScene *scene)override;

private:
    QGraphicsRectItem *tmpRect=nullptr;
};

#endif // SCENEDRAW_RECT_H
