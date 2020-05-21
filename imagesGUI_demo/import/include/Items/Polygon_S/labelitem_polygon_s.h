#ifndef LABELITEM_POLYGON_S_H
#define LABELITEM_POLYGON_S_H


/*LabelItem_Polygon_S类：
 * LabelItem_Polygon_S对象支持调整各点的鼠标交互行为（暂不支持鼠标交互增减各点）
 *
 * 对LabelScene的绘制创建接口是SceneDraw_Polygon_S，其定义在本类之后，其依赖本类而实现LabelScene的行为接口
 *
 * 本文件：整个类文件被设计为完整包括了LabelItem_Polygon_S类功能所需的局部类、外部接口等的定义
 * 这也做不会改变类之间的关系，但改变了文件的依赖关系
 */

//*:QT_BEGIN_NAMESPACE
#include"Scene/scenedraw.h"
#include<QGraphicsPolygonItem>


//***：CLASS
class LabelItem_Polygon_S:public QGraphicsPolygonItem
{
public:
    explicit LabelItem_Polygon_S(const QPolygonF &polygon,QGraphicsItem *parent = Q_NULLPTR);

    ~LabelItem_Polygon_S();

    inline QSizeF handleitemSize()const;
    void setHandleItemSize(QSizeF size);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    QRectF boundingRect() const ;
    QPainterPath shape() const override;

private:
    void updataLabelItemPolygon();//更新多边形
    void updateListPolygonRect();//更新多边形相关属性


private:
    QSizeF _handleItemSize;
    QList<QRectF> _lsPolygonRect;
    QList<QPointF> _lsPolygonPos;
    int _tarChangeIndex;

    bool _flag_mouseMoveChangeTar=false;

};



/*SceneDraw_Polygon_S类：
 *
 * 绘制创建的对象：LabelItem_Polygon_S类的对象。
 * LabelItem_Polygon_S对象具备可交互的行为（可能是一个组合类）。
 *
 * SceneDraw_Polygon_S类依赖LabelItem_Polygon_S类，是其在LabelScene的交互创建接口。
 *
 * 对于设计为各Item类解耦合的初衷，可以这样组织文件：
 * ：将LabelItem类、其局部类、其对LabelScene的绘制接口都写在同一个文件中。
 */

//***：Interface_CLASS
class SceneDraw_Polygon_S:public SceneDraw
{
public:
    SceneDraw_Polygon_S();
    ~SceneDraw_Polygon_S();

    //类族规约（接口类规约）：类ID
    enum {ShapeType=4};
    int myType() const override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event,QGraphicsScene *scene) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event,QGraphicsScene *scene)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event,QGraphicsScene *scene)override;

private:
    //
    void press_startState(QGraphicsSceneMouseEvent * event,QGraphicsScene *scene);
    void press_paintingState(QGraphicsSceneMouseEvent * event,QGraphicsScene *scene);
    //
    void release_finishState(QGraphicsSceneMouseEvent * event,QGraphicsScene *scene);

private:
    QList<QPointF> _lsPos;//点集
    QList<QGraphicsLineItem*> _lsLine;//过度线段
    QGraphicsRectItem* _handleItem=nullptr;//过度点
    QSizeF _size;//起点检测范围
    QRectF _rect;//起点检测区域

    enum PaintState{Start,Painting,Finish}_state=Start;
};



#endif // LABELITEM_POLYGON_S_H
