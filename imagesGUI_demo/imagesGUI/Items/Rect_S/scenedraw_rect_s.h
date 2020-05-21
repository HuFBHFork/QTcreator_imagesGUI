#ifndef SCENEDRAW_RECT_S_H
#define SCENEDRAW_RECT_S_H

/*
 * SceneDraw_Rect_S类：
 * 用于绘制交互创建：LabelItem_Rect_S对象
 * LabelItem_Rect_S对象支持鼠标交互调整大小
 *
*/


#include"Scene/scenedraw.h"

#include<QGraphicsRectItem>

class SceneDraw_Rect_S:public SceneDraw
{
public:
    SceneDraw_Rect_S();
    ~SceneDraw_Rect_S();

    //类族规约：类ID
    enum {ShapeType=2};
    int myType() const override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event,QGraphicsScene *scene) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event,QGraphicsScene *scene)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event,QGraphicsScene *scene)override;

private:
    QGraphicsRectItem *tmpRect=nullptr;

};

#endif // SCENEDRAW_RECT_S_H
