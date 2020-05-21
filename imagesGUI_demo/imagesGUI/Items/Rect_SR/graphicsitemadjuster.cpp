#include "graphicsitemadjuster.h"

#include"rotatehandleitem.h"
#include <QPainter>
#include<QDebug>

static QSizeF handleSize = QSizeF(6, 6);
static QMarginsF handleBounds = QMarginsF(handleSize.width(), handleSize.height(), handleSize.width(), handleSize.height());


GraphicsItemAdjuster::GraphicsItemAdjuster(QGraphicsItem *parent)
    :QGraphicsItem(parent)
    ,mMinSize(handleSize.width(),0)
    ,mTargetSize(0, 0)
{

    QSizeF size=handleSize;
    size/=2.0f;
    static QRectF handleRect(QPointF(-size.width(),-size.height()), handleSize);

    this->setFlag(ItemHasNoContents);

    //scale
    _handleItem=new HandleItem(handleRect, this);

    //rotate
    _rotateItem=new RotateItem(handleRect,this);

}

GraphicsItemAdjuster::~GraphicsItemAdjuster()
{
    delete _handleItem;
    delete _rotateItem;
}

void GraphicsItemAdjuster::setHandlePen(const QPen &pen)
{
    _handleItem->setPen(pen);
}

void GraphicsItemAdjuster::setRotatePen(const QPen &pen)
{
    _rotateItem->setPen(pen);
}

void GraphicsItemAdjuster::setHandleBrush(const QBrush &brush)
{
    _handleItem->setBrush(brush);
}

void GraphicsItemAdjuster::setRotateBrush(const QBrush &brush)
{
    _rotateItem->setBrush(brush);
}

void GraphicsItemAdjuster::setMinSize(const QSizeF &minSize)
{
    //注意设置安全的阈值
    if(minSize.width()<handleSize.width())
    {
        mMinSize.setWidth(handleSize.width());
    }
    mMinSize.setHeight(minSize.height());

}

QRectF GraphicsItemAdjuster::boundingRect() const
{
    return mBounds;
}

void GraphicsItemAdjuster::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen p(Qt::gray, 1, Qt::DashLine);
    painter->setPen(p);
    painter->drawRect(mBounds - handleBounds);
}

void GraphicsItemAdjuster::setTargetSize(const QSizeF &size)
{
    if (size == targetSize())
    {
        return;
    }
    updateDimensions(size);
}

void GraphicsItemAdjuster::updateTargetRect(const QRectF &rect)
{
    if (rect.size() == targetSize())
    {
        return;
    }
    updateDimensions(rect.size());

    emit targetRectChanged(rect);
}

void GraphicsItemAdjuster::updateDimensions(QSizeF newSize)
{
    prepareGeometryChange();
    mTargetSize = newSize;

    QRectF rect = QRectF(QPointF(), newSize) + handleBounds;
    setPos(rect.topLeft());
    mBounds = QRectF(QPointF(), rect.size());
    updateHandleItemPositions();
}

void GraphicsItemAdjuster::updateHandleItemPositions()
{
    QRectF innerRect = mBounds - handleBounds;
    //发送消息
    _handleItem->targetRectChanged(innerRect);
    _rotateItem->targetRectChanged(innerRect);
}

void GraphicsItemAdjuster::updateTargetRota(QPointF newPos)
{
    emit targetRotaChanged(newPos);
}

