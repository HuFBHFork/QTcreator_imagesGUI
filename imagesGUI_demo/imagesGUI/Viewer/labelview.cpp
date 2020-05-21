#include "labelview.h"
#include "ui_labelview.h"

#include<QMouseEvent>

LabelView::LabelView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LabelView)
{
    ui->setupUi(this);
    ui->graphicsView->setLabelPos(ui->pos_x,ui->pos_y);
    ui->graphicsView->setLabelShowZoomValue(ui->zoom_value);
    this->setMouseTracking(true);
}

LabelView::~LabelView()
{
    delete ui;
}

void LabelView::setScene(QGraphicsScene *scene)
{
    ui->graphicsView->setScene(scene);
}

QGraphicsScene *LabelView::scene()
{
    return ui->graphicsView->scene();
}

void LabelView::set_flag_viewTranslate(bool flag)
{
    ui->graphicsView->set_enableMouseMoveView(flag);
}

void LabelView::set_flag_showScrollBar(bool flag)
{
    ui->graphicsView->set_visibleScrollBar(flag);
}

void LabelView::set_flag_viewZoom(bool flag)
{
    ui->graphicsView->set_enble_zoom(flag);
}

void LabelView::set_SceneEnabled(bool flag)
{
    ui->graphicsView->setInteractive(flag);
}

QSize LabelView::getViewSize() const
{
    return ui->graphicsView->size();
}

QRect LabelView::getViewGrometry() const
{
    return ui->graphicsView->geometry();
}

void LabelView::setZoomRatio(int ratio)
{
     ui->graphicsView->setZoomRatio(ratio);
}

int LabelView::getZoomRatio()
{
    return ui->graphicsView->getZoomRatio();
}

void LabelView::setViewScaleValue(qreal scaleValue)
{
    ui->graphicsView->set_viewScaleValue(scaleValue);
}

qreal LabelView::getViewScaleValue()
{
    return ui->graphicsView->getViewScaleValue();
}

void LabelView::setViewBackgroundColor(QColor color)
{
    ui->graphicsView->setViewBackgroundColor(color);
}

void LabelView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::RightButton)
    {

    }

    //继续传递事件
    QWidget::mousePressEvent(event);
}

