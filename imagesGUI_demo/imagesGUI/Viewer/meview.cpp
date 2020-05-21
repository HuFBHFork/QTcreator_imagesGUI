#include "meview.h"

#include<QDebug>//用于调试与输出运行信息（可重定向输出到文件）
#include<QMouseEvent>
#include<QScrollBar>
#include<QGraphicsItem>


meView::meView(QWidget *parent)
{
    //*定制组件：样式与行为
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff) ;
    this->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff ) ;
    this->setMouseTracking(true);
    //this->setCursor(Qt::CrossCursor);

    //初始化参数
    initMember();
}

meView::meView(QLabel *x, QLabel *y, QWidget *parent)
    :meView(parent)
{
    _posX=x;
    _posY=y;

}

//***:公开方法
void meView::setLabelPos(QLabel *x, QLabel *y)
{
    _posX=x;
    _posY=y;
}

void meView::setLabelShowZoomValue(QLabel *showZoom)
{
    _showZoomValue=showZoom;
}

void meView::set_enble_zoom(bool flag)
{
    _flag_enable_zoom=flag;
}

void meView::set_visibleScrollBar(bool flag)
{
    Qt::ScrollBarPolicy hBar,vBar;
    if(flag)
    {
        hBar=Qt::ScrollBarAlwaysOn;
        vBar=Qt::ScrollBarAlwaysOn;
    }
    else
    {
        hBar=Qt::ScrollBarAlwaysOff;
        vBar=Qt::ScrollBarAlwaysOff;
    }

    this->setHorizontalScrollBarPolicy(hBar) ;
    this->setVerticalScrollBarPolicy (vBar) ;
}


void meView::setZoomRatio(int ratio)
{
    //ratio为非负数百分值：[0,*)
    if(ratio<0)
    {
        return;
    }

    double factor=ratio/100.0;
    factor=std::pow(factor+1,1.0/120);

    _zoomRatio = factor;
}

int meView::getZoomRatio()
{
    double ratio=std::pow(_zoomRatio,120);
    ratio=std::abs(ratio-1);

    return (int)ratio*100;//返回单次放缩比例的百分值
}

void meView::set_viewScaleValue(qreal value)
{
    value/=100.0;
    this->resetTransform();
    this->scale(value, value);
    _mScaleValue=value;
    signal_to_widget_zoomValue();
}

qreal meView::getViewScaleValue()
{
    return _mScaleValue*100;//百分值：默认100%
}

void meView::setViewBackgroundColor(QColor color)
{
	//创建color色的调色板
	QPalette palette;
	palette.setBrush(backgroundRole(), color);
	//设置view调色板
    setPalette(palette);
}

void meView::set_enableMouseMoveView(bool flag)
{
    _sceneDraw_eq_mouseMoveView=flag;
}

void meView::signal_to_widget_zoomValue()
{
    //视野放缩倍率
    if(_showZoomValue!=nullptr)
    {
        _showZoomValue->setText(QString::asprintf("%.2f", _mScaleValue*100));
    }
}

void meView::signal_to_widget_pos(QPointF pointSence)
{
    //鼠标在背景图中的位置：回调写入到label的文本内容
    if(_posX!=nullptr&&_posY!=nullptr&&!pointSence.isNull())
    {
        _posX->setText(QString::asprintf("%.0f", pointSence.x()));
        _posY->setText(QString::asprintf("%.0f", pointSence.y()));
    }
}

//***:私有方法
void meView::setValueScrollBar(int x, int y)
{
    this->horizontalScrollBar()->setValue(x);
    this->verticalScrollBar()->setValue(y);
}

void meView::translateByMouse(QPointF delta)
{
    int x=this->horizontalScrollBar()->value()+delta.x();
    int y=this->verticalScrollBar()->value()+delta.y();
    setValueScrollBar(x,y);
}

QPointF meView::scaleByMouse(QPoint pos, int scaleFactor)
{
    //保存鼠标所指的场景坐标
    QPointF posScene = mapToScene(pos);

    //scale坐标变换
    qreal factor = std::pow(_zoomRatio,scaleFactor);
    this->scale(factor, factor);
    _mScaleValue*=factor;

    //计算变换前鼠标所指位置，在新View坐标系中的值
    posScene = mapFromScene(posScene);

    //
    return posScene;
}

void meView::initMember()
{
	//创建黑色颜色 RGB：0，0，0 AlphaF：透明度（1为不透明）
	QColor  color(0, 0, 0);
	color.setAlphaF(1);
	//设置view背景颜色
	setViewBackgroundColor(color);
}

//***:功能响应
void meView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pointSence=this->mapToScene(event->pos());
    signal_to_widget_pos(pointSence);

    if (_sceneDraw_eq_mouseMoveView&&_enableMouseTranslate)
    {
        QPointF mouseDelta = event->pos()-_posMouseLast;
        translateByMouse(-mouseDelta);
        _posMouseLast = event->pos();
    }
    _posMouseLast = event->pos();
    //qDebug()<<_posMouseLast;
    //end:传递事件
     this->viewport()->update();
    QGraphicsView::mouseMoveEvent(event);
}

void meView::mousePressEvent(QMouseEvent *event)
{
    _posMouseLast = event->pos();
    if(this->scene()==nullptr)
    {
        return;
    }

    if(_sceneDraw_eq_mouseMoveView)
    {
        if (event->button() == Qt::LeftButton)
        {
            QPointF point = mapToScene(event->pos());
            if(this->scene()->itemAt(point,transform())==NULL)
            {
                _enableMouseTranslate = true;
                _posMouseLast = event->pos();
//                this->setCursor(Qt::ClosedHandCursor);//当事件传给scene后，鼠标样式被复位
            }
            else
            {
                if (this->scene()->itemAt(point,transform())->type()==QGraphicsPixmapItem::Type)
                {
                    //拖动视野：底下item=image
                    this->scene()->clearSelection();
                    _enableMouseTranslate = true;
                    _posMouseLast = event->pos();
//                    this->setCursor(Qt::ClosedHandCursor);//当事件传给scene后，鼠标样式被复位
                }
                else
                {
                    //传递事件：底下item=ROI
                     QGraphicsView::mousePressEvent(event);
                }
            }
        }
    }

    if(!_sceneDraw_eq_mouseMoveView)//鼠标绘图时，继续传递
    {
        QGraphicsView::mousePressEvent(event);
    }

}

void meView::mouseReleaseEvent(QMouseEvent *event)
{
    _posMouseLast = event->pos();
    if (event->button() == Qt::LeftButton)
    {
        _enableMouseTranslate = false;
        setCursor(Qt::ArrowCursor);
    }

    //end:继续传递事件
    QGraphicsView::mouseReleaseEvent(event);
}

void meView::wheelEvent(QWheelEvent *event)
{
    if (event)
    {
        if(_flag_enable_zoom)
        {
            QPointF posNewView=scaleByMouse(event->pos(),event->delta());
            QPointF mouseDelta=posNewView-event->pos();
            translateByMouse(mouseDelta);

            signal_to_widget_zoomValue();
        }
    }
}

void meView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);

    //if(_flag_show_CrossLine&&_flag_mouse_in_view)
    {
        QPainter painter(this->viewport());
        painter.setPen(QPen(_lineColor,_lineWidth));
        painter.drawLine(QPointF(0,_posMouseLast.y()),QPointF(this->width(),_posMouseLast.y()));
        painter.drawLine(QPointF(_posMouseLast.x(),0),QPointF(_posMouseLast.x(),this->height()));
    }

}

void meView::enterEvent(QEvent *event)
{
    _flag_mouse_in_view=true;
    this->viewport()->update();
}

void meView::leaveEvent(QEvent *event)
{
    _flag_mouse_in_view=false;
    this->viewport()->update();
}
