#ifndef GRAPHICSITEMRESIZER_H
#define GRAPHICSITEMRESIZER_H

#include <QObject>
#include <QGraphicsItem>
#include <QPen>


//***:!!!:resizer无法满足mainItem在旋转状态下的调整功能，而且因此不能复用到自定义Item中（？考虑重构|临时简易的其他方案）
//***：考虑到Item的开发和自定义定制，是更加低耦合的部分，可以通过“包”管理好各各程序员开发的解决方案（可复用类程序集）
class GraphicsItemResizer : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit GraphicsItemResizer(QGraphicsItem *parent = nullptr);
    ~GraphicsItemResizer();

    inline QBrush brush() const;//使用内联
    void setBrush(const QBrush &brush);

    inline QPen pen() const;
    void setPen(const QPen &pen);

    inline QSizeF minSize() const;
    void setMinSize(const QSizeF &minSize);

    inline QSizeF targetSize() const;
    inline QPointF TargetLeftPos() const;

public slots:
    void setTargetSize(const QSizeF &size);
    void setTargetLeftPos(const QPointF &pos);

signals:
    void targetRectChanged(const QRectF &rect);//发送信号：反馈HandleItems的

    // Item接口
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    class HandleItem;

    void updateHandleItemPositions();//管理者：更新HandleItem的在依附Item的位置
    void updateDimensions(QSizeF newSize,QPointF posLeft=QPointF());//管理者：更新HandleItem，调用updateHandleItemPositions
    void updateTargetRect(const QRectF &rect);//反馈回修改依附item的外围rect：发送信号

    QList<HandleItem *> mHandleItems;
    QPen mPen;
    QBrush mBrush;
    QSizeF mTargetSize;
    QPointF mTargetLeftPos;
    QSizeF mMinSize;
    QRectF mBounds;
};

QBrush GraphicsItemResizer::brush() const
{
    return mBrush;
}

QPen GraphicsItemResizer::pen() const
{
    return mPen;
}

QSizeF GraphicsItemResizer::minSize() const
{
    return mMinSize;
}

QSizeF GraphicsItemResizer::targetSize() const
{
    return mTargetSize;
}

QPointF GraphicsItemResizer::TargetLeftPos() const
{
    return mTargetLeftPos;
}

#endif // GRAPHICSITEMRESIZER_H
