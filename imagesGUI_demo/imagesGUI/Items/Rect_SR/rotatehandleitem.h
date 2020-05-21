#ifndef ROTATEHANDLEITEM_H
#define ROTATEHANDLEITEM_H


#include"graphicsitemadjuster.h"
#include <QGraphicsRectItem>

//***CLASS:
class GraphicsItemAdjuster::HandleItem : public QGraphicsRectItem
{
public:
    explicit HandleItem(const QRectF &rect, GraphicsItemAdjuster *ajuster);

    void targetRectChanged(const QRectF &targetRect);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    //
    void alignPosition(const QRectF &targetRect, QPointF &position);
    void solveConstraints(QPointF offset, QSizeF minSize, QRectF &targetRect) const;

private:
    //core_menber
    GraphicsItemAdjuster* _ajuster;//对_ajuster为依赖关系（而非组合）

    //assist_menber
    bool _mouseFlagToMove=false;

};



//***CLASS:
class GraphicsItemAdjuster::RotateItem:public QGraphicsEllipseItem
{
public:
    explicit RotateItem(const QRectF &rect, GraphicsItemAdjuster *ajuster);

    void targetRectChanged(const QRectF &targetRect);

protected:
     //保护成员：想设计在类族中用于重写行为（一般设计为虚函数）
     void alignPosition(const QRectF &targetRect, QPointF &position);

     virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
     virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
     virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;


private:
    GraphicsItemAdjuster* _ajuster;

    //
    bool _mouseFlagToRotate=false;

};

#endif // ROTATEHANDLEITEM_H
