#ifndef LABELSCENE_H
#define LABELSCENE_H


/*
 *Sence职能:
 * 用于管理Items（默认）;
 * 传递View事件给item（默认）;
 * 导出Graphics信息（自定义）;
 * 鼠标绘制创建item（自定义）；
*/

#include <QGraphicsScene>
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class SceneDraw;


class LabelScene: public QGraphicsScene
{
public:
    enum AddMode{NormalMode,DrawMode};

    explicit LabelScene(QObject *parent = nullptr);
    explicit LabelScene(AddMode mode,QObject *parent = nullptr);

    int addMode();//设置Sence添加item的模式：设置为绘制模式时，鼠标事件会截断在Sence层，不继续传递给item。
    void setAddMode(AddMode mode);
    SceneDraw* senceDraw();//设置Sence绘制添加item的接口对象，执行时会连带设置addMode==drawMode。
    void setSenceDraw(SceneDraw* draw);
    void resetSceneDraw();//复位鼠标绘制

protected:
    void keyPressEvent(QKeyEvent *event);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    int SimpleStateMachine_forAddMode(QGraphicsSceneMouseEvent *event);//负责处理addmode相关的消息传递

private:
    int _addMode=NormalMode;
    SceneDraw *_senceDraw=nullptr;

};

#endif // LABELSCENE_H
