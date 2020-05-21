#include "scenedraw_rect.h"

#include<QGraphicsScene>
#include<QDebug>

SceneDraw_Rect::SceneDraw_Rect()
{

}

SceneDraw_Rect::~SceneDraw_Rect()
{

}

int SceneDraw_Rect::myType() const
{
    return ShapeType;
}

void SceneDraw_Rect::mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    scene->clearSelection();

    QPointF pos1(event->scenePos()),pos2(event->scenePos());
    QRectF rect(pos1,pos2);

    tmpRect=new QGraphicsRectItem(rect);
    tmpRect->setPos(0,0);

    scene->addItem(tmpRect);
}

void SceneDraw_Rect::mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
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

void SceneDraw_Rect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    if(tmpRect==nullptr)
    {
        return;
    }

    if(tmpRect->rect().isValid())
    {
        QGraphicsRectItem *p=new QGraphicsRectItem(tmpRect->rect());
        scene->addItem(p);
        p->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsMovable);

    }

    //处理临时值
    scene->removeItem(tmpRect);
    delete tmpRect;
    tmpRect=nullptr;
}


