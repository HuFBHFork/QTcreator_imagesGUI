#include "labelitem_polygon_s.h"

#include<QDebug>
#include<QPainter>
#include<QStyleOptionGraphicsItem>
#include<QGraphicsScene>

LabelItem_Polygon_S::LabelItem_Polygon_S(const QPolygonF &polygon, QGraphicsItem *parent)
    :QGraphicsPolygonItem(polygon,parent)
    ,_handleItemSize(5,5)
{
    updateListPolygonRect();
}

LabelItem_Polygon_S::~LabelItem_Polygon_S()
{

}

QSizeF LabelItem_Polygon_S::handleitemSize() const
{
    return _handleItemSize;
}

void LabelItem_Polygon_S::setHandleItemSize(QSizeF size)
{
    QSizeF minisize(4,4);
    if(size.width()<minisize.width())
    {
        size.setWidth(minisize.width());
    }
    else if(size.height()<minisize.height())
    {
        size.setHeight(minisize.height());
    }

    _handleItemSize=size;
}

void LabelItem_Polygon_S::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QList<QRectF>::const_iterator iter;
    for(iter=_lsPolygonRect.begin();iter!=_lsPolygonRect.end();iter++)
    {
        QRectF rect(*iter);
        if(rect.contains(event->pos()))
        {
            _flag_mouseMoveChangeTar=true;
            this->setFlag(QGraphicsItem::ItemIsMovable,false);
            _tarChangeIndex=_lsPolygonRect.indexOf(*iter);
            break;
        }
    }
    QGraphicsPolygonItem::mousePressEvent(event);

}

void LabelItem_Polygon_S::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //if_do
    if(_flag_mouseMoveChangeTar)
    {
        //更新目标点：_tarChangeIndex
        _lsPolygonPos.removeAt(_tarChangeIndex);
        _lsPolygonPos.insert(_tarChangeIndex,event->pos());
        if(_tarChangeIndex==0)
        {
            _lsPolygonPos.removeLast();
            _lsPolygonPos.append(event->pos());
        }

        //更新Polygon
        updataLabelItemPolygon();
        //更新Polygon相关属性
        updateListPolygonRect();

    }

    QGraphicsPolygonItem::mouseMoveEvent(event);
}

void LabelItem_Polygon_S::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //Flag_press状态还原
    _flag_mouseMoveChangeTar=false;
    this->setFlag(QGraphicsItem::ItemIsMovable,true);


    QGraphicsPolygonItem::mouseReleaseEvent(event);
}

void LabelItem_Polygon_S::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);

    QPen pen;
    pen.setColor(QColor(Qt::black));
    painter->setPen(pen);
    painter->setBrush(QColor(Qt::black));

    QList<QRectF>::const_iterator iter;

    QPolygonF handleItem;
    for(iter=_lsPolygonRect.begin();iter!=_lsPolygonRect.end();iter++)
    {
        QRectF rect(*iter);
        handleItem.clear();

        handleItem<<rect.topLeft()
                 <<rect.topRight()
                <<rect.bottomRight()
               <<rect.bottomLeft();

        painter->drawPolygon(handleItem);

    }

    QStyleOptionGraphicsItem op;
    op.initFrom(widget);
    op.state = QStyle::State_None;
    QGraphicsPolygonItem::paint(painter,option,widget);

}

QRectF LabelItem_Polygon_S::boundingRect() const
{
    return shape().controlPointRect();
}

QPainterPath LabelItem_Polygon_S::shape() const
{
    QPainterPath path ;
    path.addPolygon(this->polygon());

    QList<QRectF>::const_iterator iter;
    QPolygonF handleItem;
    for(iter=_lsPolygonRect.begin();iter!=_lsPolygonRect.end();iter++)
    {
        QRectF rect(*iter);
        handleItem.clear();

        handleItem<<rect.topLeft()
                 <<rect.topRight()
                <<rect.bottomRight()
               <<rect.bottomLeft();

        path.addPolygon(handleItem);
    }

    return path;
}

void LabelItem_Polygon_S::updataLabelItemPolygon()
{
    QPolygonF polygon;
    QList<QPointF>::const_iterator iter;
    for(iter=_lsPolygonPos.begin();iter!=_lsPolygonPos.end();iter++)
    {
        polygon<<*iter;
    }

    prepareGeometryChange();
    this->setPolygon(polygon);
    update();
}

void LabelItem_Polygon_S::updateListPolygonRect()
{
    QRectF rect;

    _lsPolygonPos.clear();
    _lsPolygonPos=this->polygon().toList();

    //
    _lsPolygonRect.clear();
    QList<QPointF>::const_iterator iter;
    for(iter=_lsPolygonPos.begin();iter!=_lsPolygonPos.end();iter++)
    {
        qreal w,h;
        w=_handleItemSize.width();
        h=_handleItemSize.height();

        QPointF pos_cen(*iter);
        QPointF pos_topl(pos_cen.x()-w/2.0f,pos_cen.y()-h/2.0f);
        QSizeF size(w,h);

        rect=QRectF(pos_topl,size);
        _lsPolygonRect.append(rect);

    }
    _lsPolygonRect.removeLast();//闭合曲线的点

}




SceneDraw_Polygon_S::SceneDraw_Polygon_S()
    :_size(4,4)
{
    QPointF pos(-_size.width()/2.0f,-_size.height()/2.0f);
    QRectF rect(pos,_size);
    _handleItem=new QGraphicsRectItem(rect);
    _handleItem->setPen(QPen(Qt::yellow));
    _handleItem->setBrush(QBrush(Qt::yellow));
    _handleItem->setZValue(1);
}

SceneDraw_Polygon_S::~SceneDraw_Polygon_S()
{
    delete _handleItem;
}

int SceneDraw_Polygon_S::myType() const
{
    return ShapeType;
}

void SceneDraw_Polygon_S::mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    switch (_state) {
    case Start:
        press_startState(event,scene);
        break;
    case Painting:
        press_paintingState(event,scene);
        break;
    case Finish:

        break;
    default:
        break;
    }

}

void SceneDraw_Polygon_S::mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{

}

void SceneDraw_Polygon_S::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    switch (_state) {
    case Start:
        break;
    case Painting:
        break;
    case Finish:
        release_finishState(event,scene);
        break;
    default:
        break;
    }

}

void SceneDraw_Polygon_S::press_startState(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    scene->clearSelection();

    //显示辅助点：起点
    _handleItem->setPos(event->scenePos());
    scene->addItem(_handleItem);

    //记录起点与计算检测区域
    _lsPos.append(event->scenePos());
    _rect=_handleItem->rect();
    _rect.translate(_handleItem->pos());

    //修改状态
    _state=Painting;
}

void SceneDraw_Polygon_S::press_paintingState(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    //添加点集
    _lsPos.append(event->scenePos());

    //绘制线段
    QPointF prePos=_lsPos.at(_lsPos.count()-2);
    QLineF line(_lsPos.last(),prePos);
    QGraphicsLineItem* tmpItem=new QGraphicsLineItem(line);
    scene->addItem(tmpItem);

    //记录线段
    _lsLine.append(tmpItem);

    //修改状态
    if(_rect.contains(_lsPos.last()))
    {
        //转到结束
        _state=Finish;
    }
    else
    {
        //保持状态
    }

}

void SceneDraw_Polygon_S::release_finishState(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    //清空屏幕：HandleItem、tmpLine
    scene->removeItem(_handleItem);
    for(int i=0;i<_lsLine.count();i++)
    {
        scene->removeItem(_lsLine.at(i));
    }

    //释放临时对象:tmp_lineItem
    for (QGraphicsLineItem *i:_lsLine)
    {
        delete i;
    }

    //添加目标Item：点集至少为3
    QPolygonF polygon;
    for (QPointF i:_lsPos)
    {
        polygon<<i;
    }
    LabelItem_Polygon_S *targetItem;
    if(_lsPos.count()>3)
    {
        targetItem=new LabelItem_Polygon_S(polygon);
        targetItem->setFlags(QGraphicsItem::ItemIsSelectable |QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsMovable);
        scene->addItem(targetItem);
    }

    //复位数据：HandleItem、tmpPos、tmpLine、rect
    _handleItem->setPos(0,0);
    _lsPos.clear();
    _lsLine.clear();
    _rect=QRectF();

    //修改状态
    _state=Start;

}
