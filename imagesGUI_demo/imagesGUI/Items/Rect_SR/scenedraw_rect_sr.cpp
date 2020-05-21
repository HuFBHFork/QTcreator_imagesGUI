#include "scenedraw_rect_sr.h"

#include<QGraphicsScene>
#include"labelitem_rect_sr.h"

SceneDraw_Rect_SR::SceneDraw_Rect_SR()
{

}

SceneDraw_Rect_SR::~SceneDraw_Rect_SR()
{

}

int SceneDraw_Rect_SR::myType() const
{
    return ShapeType;
}

void SceneDraw_Rect_SR::mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    scene->clearSelection();

    QPointF pos1(event->scenePos()),pos2(event->scenePos());
    QRectF rect(pos1,pos2);

    tmpRect=new QGraphicsRectItem(rect);
    tmpRect->setPos(0,0);

    scene->addItem(tmpRect);
}

void SceneDraw_Rect_SR::mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
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

void SceneDraw_Rect_SR::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    if(tmpRect->rect().isValid())
    {
        QRectF rect(0,0,tmpRect->rect().width(),tmpRect->rect().height());//设置几何中心的矩形
        QPointF pos(tmpRect->rect().x(),tmpRect->rect().y());

        LabelItem_Rect_SR* tmp=new LabelItem_Rect_SR(rect);
        tmp->setFlags(QGraphicsItem::ItemIsSelectable |QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsMovable);

        scene->addItem(tmp);//临时变量is合法，则副本到容器
        tmp->setPos(pos);

    }

    //处理临时值
    scene->removeItem(tmpRect);
    delete tmpRect;
    tmpRect=nullptr;
}



