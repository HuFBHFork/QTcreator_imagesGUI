#ifndef LABELITEM_RECT_S_H
#define LABELITEM_RECT_S_H

/*
 * LabelItem_Rect_S类：
 * 绘制交互创建的代理对象是：SceneDraw_Rect_S对象
 * LabelItem_Rect_S对象支持鼠标交互调整大小
 *
*/


#include"graphicsitemresizer.h"

#include<QGraphicsRectItem>

class LabelItem_Rect_S:public QGraphicsRectItem
{
public:
    explicit LabelItem_Rect_S(QGraphicsItem *parent = Q_NULLPTR);
    explicit LabelItem_Rect_S(const QRectF &rect, QGraphicsItem *parent = Q_NULLPTR);
    virtual ~LabelItem_Rect_S();
    void set_resizer(const QSizeF &size,const QPointF &pos);

protected:
    virtual void on_targetRectChanged(const QRectF &rect);//子类重写自己的调整行为

private:
    void new_resizer();
    GraphicsItemResizer *_resizer=nullptr;

};

#endif // LABELITEM_RECT_S_H
