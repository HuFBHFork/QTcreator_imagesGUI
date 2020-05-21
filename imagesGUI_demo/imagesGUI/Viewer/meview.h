#ifndef MEVIEW_H
#define MEVIEW_H

#include <QGraphicsView>
#include <QObject>
#include<QLabel>

class meView: public QGraphicsView
{
public:
    explicit meView(QWidget *parent = nullptr);
    explicit meView(QLabel *x,QLabel *y,QWidget *parent=nullptr);


private://私有字段
    QLabel *_posX=nullptr,*_posY=nullptr,*_showZoomValue=nullptr;//场景坐标显示

    bool _enableMouseTranslate=false;  //平移使能
    QPoint _posMouseLast;

    double _zoomRatio=1.001;//鼠标滚动
    qreal _mScaleValue=1.0;//当前放缩值（总放缩值）

    bool _sceneDraw_eq_mouseMoveView=true;//绘制图形
    bool _flag_enable_zoom=true;//滚轮放缩使能

public://属性get、set
    //**:用于定制Widget
    void setLabelPos(QLabel *x,QLabel *y);
    void setLabelShowZoomValue(QLabel *showZoom);

    //**:通用一般接口
    void set_enble_zoom(bool flag);//滚轮放缩使能
    void set_visibleScrollBar(bool flag);//设置滚动条显示标志位
    void setZoomRatio(int ratio);//设置单步放缩值（百分值）
    int getZoomRatio();
    void set_viewScaleValue(qreal value);//当前视野放缩总倍率(百分值)
    qreal getViewScaleValue();
	void setViewBackgroundColor(QColor color);//设置view背景色

    //鼠标拖图视野
    void set_enableMouseMoveView(bool flag);

private:
    //**：用于定制Widget
    void signal_to_widget_pos(QPointF pointSence);
    void signal_to_widget_zoomValue();

    //**:
    void setValueScrollBar(int x,int y);
    void translateByMouse(QPointF delta);
    QPointF scaleByMouse(QPoint pos, int scaleFactor);
    void initMember();//初始化一般成员变量

protected:
    //***1:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    //***2:
    void wheelEvent(QWheelEvent *event);

    bool _flag_show_CrossLine=true;
    bool _flag_mouse_in_view=true;
    QPoint _posMouse;
    QColor _lineColor=Qt::gray;
    int _lineWidth=1;
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
};

#endif // MEVIEW_H
