#ifndef GRAPHICSITEMADJUSTER_H
#define GRAPHICSITEMADJUSTER_H


#include <QObject>
#include <QGraphicsItem>
#include <QPen>


//***:在LabelItem_v1中，用于修改Item的大小和旋转的辅助对象
class GraphicsItemAdjuster: public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit GraphicsItemAdjuster(QGraphicsItem *parent = nullptr);
    ~GraphicsItemAdjuster();

    //可有可无的外部接口：定制AjusterItem的样式
    void setHandlePen(const QPen &pen);
    void setRotatePen(const QPen &pen);
    void setHandleBrush(const QBrush &brush);
    void setRotateBrush(const QBrush &brush);

    //可有可无的外部接口：调整限制条件
    inline QSizeF minSize() const;
    void setMinSize(const QSizeF &minSize);
    inline QPointF TargetPos() const;

    //QGraphicsItem重写
    inline QSizeF targetSize() const;
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public slots:
    void setTargetSize(const QSizeF &size);

signals:
    void targetRectChanged(const QRectF &rect);
    void targetRotaChanged(QPointF newPos);

private:
    void updateTargetRect(const QRectF &rect);
    void updateDimensions(QSizeF newSize);
    void updateHandleItemPositions();

    void updateTargetRota(QPointF newPos);

private:
    class HandleItem;//调整大小
    class RotateItem;//调整旋转


    QSizeF mMinSize;
    QSizeF mTargetSize;
    QRectF mBounds;

    HandleItem *_handleItem;//组合关系，不需初始化到nullptr
    RotateItem *_rotateItem;

};


QSizeF GraphicsItemAdjuster::minSize() const
{
    return mMinSize;
}

QPointF GraphicsItemAdjuster::TargetPos() const
{
    this->parentItem()->pos();//无效？
}

QSizeF GraphicsItemAdjuster::targetSize() const
{
    return mTargetSize;
}

#endif // GRAPHICSITEMADJUSTER_H
