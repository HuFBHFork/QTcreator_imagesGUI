#include "labelscene.h"

#include<QKeyEvent>
#include<QGraphicsSceneMouseEvent>
#include"Scene/scenedraw.h"

LabelScene::LabelScene(QObject *parent)
    :QGraphicsScene(parent)
{

}

LabelScene::LabelScene(LabelScene::AddMode mode, QObject *parent)
    :LabelScene(parent)
{
    _addMode=mode;
}


int LabelScene::addMode()
{
    return _addMode;
}

void LabelScene::setAddMode(AddMode mode)
{
    _addMode=mode;
}

SceneDraw *LabelScene::senceDraw()
{
    return _senceDraw;
}

void LabelScene::setSenceDraw(SceneDraw *draw)
{
    setAddMode(DrawMode);
    _senceDraw=draw;
}

void LabelScene::resetSceneDraw()
{
    _addMode=NormalMode;
    _senceDraw=nullptr;
}

void LabelScene::keyPressEvent(QKeyEvent *event)
{
    QList<QGraphicsItem *> selectItems =  selectedItems();
    switch (event->key())
    {
    case Qt::Key_Delete:
        if(selectItems.count()>0)
        {
            while(selectItems.count()>0)
            {
                QGraphicsItem * item =selectItems.last();
                removeItem(item);
                selectItems.pop_back();
                delete item;
                //remove和pop_back之后是否要delete::考虑增加flag_enable
            }
        }
        break;
    }

    //继续传递事件
    QGraphicsScene::keyPressEvent(event);
}

void LabelScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(SimpleStateMachine_forAddMode(event)!=NormalMode)//过滤addMode
    {
        return;
    }
    QGraphicsScene::mousePressEvent(event);
}

void LabelScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(SimpleStateMachine_forAddMode(event)!=NormalMode)
    {
        return;
    }
   QGraphicsScene::mouseMoveEvent(event);
}

void LabelScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(SimpleStateMachine_forAddMode(event)!=NormalMode)
    {
        return;
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

int LabelScene::SimpleStateMachine_forAddMode(QGraphicsSceneMouseEvent *event)
{
    switch (_addMode) {
    case DrawMode:
        this->clearSelection();
        if(_senceDraw!=nullptr)_senceDraw->senceDrawEvent(event,this);
        break;

    case NormalMode:
    default:
        break;
    }

    return _addMode;
}
