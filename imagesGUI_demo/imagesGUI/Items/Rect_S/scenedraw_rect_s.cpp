#include "scenedraw_rect_s.h"

#include<QGraphicsScene>
#include<QDebug>
#include"labelitem_rect_s.h"

SceneDraw_Rect_S::SceneDraw_Rect_S()
{

}

SceneDraw_Rect_S::~SceneDraw_Rect_S()
{

}

int SceneDraw_Rect_S::myType() const
{
    return ShapeType;
}

void SceneDraw_Rect_S::mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    scene->clearSelection();

    QPointF pos1(event->scenePos()),pos2(event->scenePos());
    QRectF rect(pos1,pos2);

    tmpRect=new QGraphicsRectItem(rect);
    tmpRect->setPos(0,0);

    scene->addItem(tmpRect);
}

void SceneDraw_Rect_S::mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    if(tmpRect!=nullptr)
    {

        QRectF rect(tmpRect->rect().topLeft(),event->scenePos());

        if(rect.isValid())
        {
            tmpRect->setRect(rect);
        }
    }
}

void SceneDraw_Rect_S::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    if(tmpRect==nullptr)
    {
        return;
    }

    if(tmpRect->rect().isValid())
    {
        QRectF rect(-0.5*tmpRect->rect().width(),-0.5*tmpRect->rect().height(),tmpRect->rect().width(),tmpRect->rect().height());//设置几何中心的矩形
        QPointF pos(tmpRect->rect().x()+0.5*tmpRect->rect().width(),tmpRect->rect().y()+0.5*tmpRect->rect().height());

        LabelItem_Rect_S* tmp=new LabelItem_Rect_S(rect);
        tmp->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsMovable);

        scene->addItem(tmp);//临时变量is合法，则副本到容器
        tmp->setPos(pos);

    }

    //处理临时值
    scene->removeItem(tmpRect);
    delete tmpRect;
    tmpRect=nullptr;
}
