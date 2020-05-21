#include "labelitem_rect_sr.h"

#include<QDebug>
LabelItem_Rect_SR::LabelItem_Rect_SR(const QRectF &rect, QGraphicsItem *parent)
    :QGraphicsRectItem(rect,parent)
{
    new_ajuster();
}

LabelItem_Rect_SR::~LabelItem_Rect_SR()
{
    delete _ajuster;
}

void LabelItem_Rect_SR::new_ajuster()
{
    //create_obj
    _ajuster = new GraphicsItemAdjuster(this);
    _ajuster->setHandleBrush(QColor(64, 64, 64));
    _ajuster->setMinSize(QSizeF(0, 0));

    _ajuster->setTargetSize(this->boundingRect().size());

    //update_function
    QObject::connect(_ajuster, &GraphicsItemAdjuster::targetRectChanged, [this](const QRectF &rect)
    {
        QRectF old = this->rect();
        this->setRect(QRectF(old.topLeft(), rect.size()));
    });

    //update_function
    QObject::connect(_ajuster, &GraphicsItemAdjuster::targetRotaChanged, [this](QPointF newPos)
    {
        if(_lastTranslate_mousePos==QPointF())
        {
            _lastTranslate_mousePos=newPos;
        }

        QTransform matrix=caculaMatrix(this->pos(),this->mapToScene(this->rect().topRight()),this->pos(),newPos);

        matrix=this->transform()*matrix;
        this->setTransform(matrix);

        //更新lastpos
        _lastTranslate_mousePos=newPos;
    });

}

QTransform LabelItem_Rect_SR::caculaMatrix(QPointF s1, QPointF s2, QPointF p1, QPointF p2)
{

    QPointF translateVector(p1-s1);
    QTransform translationForm(1, 0, 0, 1, translateVector.x(), translateVector.y());

    //向量与求模
    QPointF vector_a(s2-s1),vector_b(p2-p1),vector_c(p2-s2);
    vector_c=vector_c-translateVector;

    qreal a,b,c;
    a=std::sqrt(vector_a.x()*vector_a.x()+vector_a.y()*vector_a.y());
    b=std::sqrt(vector_b.x()*vector_b.x()+vector_b.y()*vector_b.y());
    c=std::sqrt(vector_c.x()*vector_c.x()+vector_c.y()*vector_c.y());
//    qDebug()<<"b:"<<b;//注意b=0,怎sin=NAN的情况！
    if(b<2)
    {
        b=2;
    }

    //解三角形
    double deg,cosDeg,sinDeg;
    cosDeg=(a*a+b*b-c*c)/(2*a*b);
    sinDeg=std::pow((1-cosDeg*cosDeg),0.5);

    //向量叉积:向量积反映矢量旋转方向
    double cros_a_b;
    cros_a_b=vector_a.x()*vector_b.y()-vector_a.y()*vector_b.x();

    if(cros_a_b<0)
    {
        sinDeg=-sinDeg;
    }

    QTransform rotationForm(cosDeg, sinDeg, -sinDeg, cosDeg, 0, 0);


    return rotationForm*translationForm;
}



