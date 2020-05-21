#include "graphicsitemresizer.h"

#include "resizehandleitem.h"

#include <QPainter>


static QSizeF handleSize = QSizeF(6, 6);
static QMarginsF handleBounds = QMarginsF(handleSize.width(), handleSize.height(), handleSize.width(), handleSize.height());

GraphicsItemResizer::GraphicsItemResizer(QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , mTargetSize(0, 0)
    , mMinSize(5, 5)
{
    static QRectF handleRect(QPointF(), handleSize);//创建resize对象的范围

    this->setFlag(ItemHasNoContents);

    // sides
    mHandleItems.append(new HandleItem(HandleItem::Left, handleRect, this));
    mHandleItems.append(new HandleItem(HandleItem::Top, handleRect, this));
    mHandleItems.append(new HandleItem(HandleItem::Right, handleRect, this));
    mHandleItems.append(new HandleItem(HandleItem::Bottom, handleRect, this));
    // corners
    mHandleItems.append(new HandleItem(HandleItem::Top | HandleItem::Left, handleRect, this));
    mHandleItems.append(new HandleItem(HandleItem::Top | HandleItem::Right, handleRect, this));
    mHandleItems.append(new HandleItem(HandleItem::Bottom | HandleItem::Right, handleRect, this));
    mHandleItems.append(new HandleItem(HandleItem::Bottom | HandleItem::Left, handleRect, this));
}

GraphicsItemResizer::~GraphicsItemResizer()
{
    for (HandleItem *i : mHandleItems)
    {
        delete i;
    }
}

QRectF GraphicsItemResizer::boundingRect() const
{
    return mBounds;
}

void GraphicsItemResizer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //告诉编辑器和编译器不使用变量，不用发出警报
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QPen p(Qt::gray, 1, Qt::DashLine);
    painter->setPen(p);
    painter->drawRect(mBounds - handleBounds);
}

void GraphicsItemResizer::setPen(const QPen &pen)
{
    mPen = pen;
    for (HandleItem *i : mHandleItems)
    {
        i->setPen(pen);
    }
}

void GraphicsItemResizer::setBrush(const QBrush &brush)
{
    mBrush = brush;
    for (HandleItem *i : mHandleItems)
    {
        i->setBrush(brush);
    }
}

void GraphicsItemResizer::setTargetSize(const QSizeF &size)
{
    if (size == targetSize())
    {
        return;
    }
    updateDimensions(size,mTargetLeftPos);//更新HandleItems
}

void GraphicsItemResizer::setTargetLeftPos(const QPointF &pos)
{
    //设置HandleItems布局整体位置
    mTargetLeftPos=pos;
    updateDimensions(mTargetSize,mTargetLeftPos);
}

void GraphicsItemResizer::setMinSize(const QSizeF &minSize)
{
    if(minSize.width()>=5&&minSize.height()>=5)
    {
        mMinSize = minSize;//限定最小尺寸：或者不采用条件显示方式
    }
}

void GraphicsItemResizer::updateHandleItemPositions()
{
    QRectF innerRect = mBounds - handleBounds;
    for (HandleItem *i : mHandleItems)
    {
        i->targetRectChanged(innerRect);
    }
}

void GraphicsItemResizer::updateTargetRect(const QRectF &rect)
{
    if (rect.size() == targetSize())
    {
        return;
    }
    updateDimensions(rect.size(),mTargetLeftPos);

    //发送信号
    emit targetRectChanged(rect);
}


void GraphicsItemResizer::updateDimensions(QSizeF newSize, QPointF posLeft)
{
     //设置HandleItems的布局
    prepareGeometryChange();
    mTargetSize = newSize;

    QRectF rect = QRectF(posLeft, newSize) + handleBounds;
    setPos(rect.topLeft());
    mBounds = QRectF(QPointF(), rect.size());
    updateHandleItemPositions();
}
