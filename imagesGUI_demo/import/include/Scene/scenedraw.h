#ifndef SCENEDRAW_H
#define SCENEDRAW_H

/*
 *SenceDraw职能：
 * 作为LabelScene的鼠标绘制行为接口，给scene动态添加；
 * 接收LabelScene的鼠标事件，根据设置值绘制创建各种item；
 *
*/

#include<QGraphicsSceneMouseEvent>

class QGraphicsScene;

class SceneDraw
{
public:
    SceneDraw();
    virtual ~SceneDraw();


    enum {
        ShapeType=0,
        UserType=65536
    };//设计规约：子类需要定义自己的shape值
    virtual int myType() const;

    virtual void senceDrawEvent(QGraphicsSceneMouseEvent * event,QGraphicsScene *scene);

    //静态接口
    static int drawType();
    static void setDrawType(int type);
    static SceneDraw* factorySceneDraw();//返回一个setDrawType()指定的、已经创建的实例
    static int indexOf(SceneDraw *draw);//返回实例序号
    static SceneDraw* index(int index);//返回指定序号的实例

protected:

    //**:子类重写扩展：一般子类重写此函数即可完成绘制创建任务
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event,QGraphicsScene *scene);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event,QGraphicsScene *scene);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event,QGraphicsScene *scene);

protected:
    static int _drawType;
public:
    static QList<SceneDraw*> _draws;
};




#endif // SCENEDRAW_H
