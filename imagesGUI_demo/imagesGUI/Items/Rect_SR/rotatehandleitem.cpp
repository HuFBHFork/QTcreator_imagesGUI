#include "rotatehandleitem.h"

#include <QBrush>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include<QStyleOptionGraphicsItem>
#include<QGraphicsScene>

#include<QDebug>>

GraphicsItemAdjuster::HandleItem::HandleItem(const QRectF &rect, GraphicsItemAdjuster *ajuster)
    :QGraphicsRectItem(rect, ajuster)
    ,_ajuster(ajuster)
{

    this->setBrush(QBrush(Qt::black));
    this->setAcceptedMouseButtons(Qt::LeftButton);
    this->setFlag(ItemIsSelectable);
    this->setCursor(Qt::SizeAllCursor);
}

void GraphicsItemAdjuster::HandleItem::targetRectChanged(const QRectF &targetRect)
{
    QSizeF halfSize = this->rect().size() / 2.0f;
    QPointF newPos = targetRect.center() - QPointF(halfSize.width(), halfSize.height());
    alignPosition(targetRect, newPos);
    this->setPos(newPos);
}

void GraphicsItemAdjuster::HandleItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    _mouseFlagToMove=true;
    event->accept();
}

void GraphicsItemAdjuster::HandleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //if_return
    if (!_mouseFlagToMove)
    {
        event->ignore();
        return;
    }

    //do_that_wanna
    {

        QPointF mousePos = event->pos();
        QPointF offset = mousePos - event->lastPos();
        QRectF targetRect(QPointF(), _ajuster->targetSize());
        QSizeF minSize = _ajuster->minSize();

        solveConstraints(offset, minSize, targetRect);
//        qDebug()<<minSize;

        _ajuster->updateTargetRect(targetRect);//传递参数
    }

}

void GraphicsItemAdjuster::HandleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    event->setAccepted(_mouseFlagToMove);
    _mouseFlagToMove = false;
}

void GraphicsItemAdjuster::HandleItem::alignPosition(const QRectF &targetRect, QPointF &position)
{

    position.setX(targetRect.right());
    position.setY(targetRect.bottom());
}

void GraphicsItemAdjuster::HandleItem::solveConstraints(QPointF offset, QSizeF minSize, QRectF &targetRect) const
{

    //
    if (offset.x() < 0)
    {
        qreal width = targetRect.width() + offset.x();
        if (minSize.width() > width)
        {
            offset.rx() += minSize.width() - width;
        }
        targetRect.adjust(0, 0, offset.x(), 0);
    }


    if (offset.y()<0)
    {
        qreal height = targetRect.height() + offset.y();
        if (minSize.height() > height)
        {
            offset.ry() += minSize.height() - height;
        }
        targetRect.adjust(0, 0, 0, offset.y());
    }

    //
    if (offset.x() > 0)
    {
        qreal width = targetRect.width() + offset.x();
        if (minSize.width() > width)
        {
            offset.rx() += minSize.width() - width;
        }
        targetRect.adjust(0, 0, offset.x(), 0);
    }

    if (offset.y()>0)
    {
        qreal height = targetRect.height() + offset.y();
        if (minSize.height() > height)
        {
            offset.ry() += minSize.height() - height;
        }
        targetRect.adjust(0, 0, 0, offset.y());
    }

}


//***CLASS:
GraphicsItemAdjuster::RotateItem::RotateItem(const QRectF &rect, GraphicsItemAdjuster *ajuster)
    :QGraphicsEllipseItem(rect,ajuster)
    ,_ajuster(ajuster)
{
    this->setBrush(QBrush(Qt::blue));
    this->setAcceptedMouseButtons(Qt::LeftButton);
    this->setFlag(ItemIsSelectable);
    this->setCursor(Qt::SizeAllCursor);
}

void GraphicsItemAdjuster::RotateItem::targetRectChanged(const QRectF &targetRect)
{
    QSizeF halfSize = this->rect().size() / 2.0f;
    QPointF newPos = targetRect.center() - QPointF(halfSize.width(), halfSize.height());
    alignPosition(targetRect, newPos);
    this->setPos(newPos);
}

void GraphicsItemAdjuster::RotateItem::alignPosition(const QRectF &targetRect, QPointF &position)
{
    position.setX(targetRect.right()+this->rect().width());
    position.setY(targetRect.top());
}


void GraphicsItemAdjuster::RotateItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    _mouseFlagToRotate=true;
    event->accept();
}

void GraphicsItemAdjuster::RotateItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //if_return
    if (!_mouseFlagToRotate)
    {
        event->ignore();
        return;
    }

    //do_that_wanna
    {
        QPointF mousePos;
        mousePos=event->scenePos();

        _ajuster->updateTargetRota(mousePos);
    }

}

void GraphicsItemAdjuster::RotateItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    event->setAccepted(_mouseFlagToRotate);
    _mouseFlagToRotate = false;
}
