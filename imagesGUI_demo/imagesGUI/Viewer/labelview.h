#ifndef LABELVIEW_H
#define LABELVIEW_H

#include <QWidget>

class QGraphicsScene;

namespace Ui {
class LabelView;
}

class LabelView : public QWidget
{
    Q_OBJECT

public:
    explicit LabelView(QWidget *parent = nullptr);
    ~LabelView()override;

public:
    void setScene(QGraphicsScene *scene);
    QGraphicsScene *scene();

    void set_flag_viewTranslate(bool flag);//View视野平移
    void set_flag_showScrollBar(bool flag);//滚动条
    void set_flag_viewZoom(bool flag);
    void set_SceneEnabled(bool flag);//属性：使能View是否将事件传递给Scene

    QSize getViewSize()const ;
    QRect getViewGrometry()const;

    void setZoomRatio(int ratio);//设置单步滚动放缩值
    int getZoomRatio();
    void setViewScaleValue(qreal scaleValue);//设置视野放缩总倍率（百分值）
    qreal getViewScaleValue();
    void setViewBackgroundColor(QColor color);//设置view背景色

protected:
    //子类也可以重写鼠标右键事件：设置View属性
    virtual void mousePressEvent(QMouseEvent *event)override;


private:
    Ui::LabelView *ui;
};

#endif // LABELVIEW_H
