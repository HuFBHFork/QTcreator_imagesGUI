#include "labelitem_rect_s.h"

#include<QDebug>

LabelItem_Rect_S::LabelItem_Rect_S(QGraphicsItem *parent):
    QGraphicsRectItem(parent)
{
    new_resizer();
}

LabelItem_Rect_S::LabelItem_Rect_S(const QRectF &rect, QGraphicsItem *parent):
    QGraphicsRectItem(rect,parent)
{
    new_resizer();
}

LabelItem_Rect_S::~LabelItem_Rect_S()
{
    delete _resizer;
}

void LabelItem_Rect_S::set_resizer(const QSizeF &size, const QPointF &pos)
{
    _resizer->setTargetSize(size);
    _resizer->setTargetLeftPos(pos);
}

void LabelItem_Rect_S::on_targetRectChanged(const QRectF &rect)
{
    //只支持Translate变换：没有调整旋转中心

    QPointF pos = this->pos();
    this->setPos(pos + rect.topLeft());

    QRectF old = this->rect();
    this->setRect(QRectF(old.topLeft(), rect.size()));//同步形状

}

void LabelItem_Rect_S::new_resizer()
{
    _resizer = new GraphicsItemResizer(this);
    _resizer->setBrush(QColor(64, 64, 64));
    _resizer->setMinSize(QSizeF(0, 0));

    //设置resizersize属性
    set_resizer(this->boundingRect().size(),QPointF(this->rect().x(),this->rect().y()));

    //C++11采用lambda表达式
    QObject::connect(_resizer, &GraphicsItemResizer::targetRectChanged, [this](const QRectF &rect)
    {
        on_targetRectChanged(rect);
    });

}
