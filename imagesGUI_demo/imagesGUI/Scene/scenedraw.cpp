#include "scenedraw.h"

//***!!!:静态成员初始化，必须在cpp文件中
int SceneDraw::_drawType=0;
QList<SceneDraw*> SceneDraw::_draws;



SceneDraw::SceneDraw()
{
    _draws.push_back(this);
}

SceneDraw::~SceneDraw()
{
    _draws.removeOne(this);
}

int SceneDraw::myType() const
{
    return ShapeType;
}

void SceneDraw::senceDrawEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    switch (event->type()) {
    case QEvent::GraphicsSceneMousePress:
        this->mousePressEvent(event,scene);
        break;
    case QEvent::GraphicsSceneMouseMove:
        this->mouseMoveEvent(event,scene);
        break;

    case QEvent::GraphicsSceneMouseRelease:
        this->mouseReleaseEvent(event,scene);
        break;

    default:
        break;
    }

}

int SceneDraw::drawType()
{
    return _drawType;
}

void SceneDraw::setDrawType(int type)
{
    _drawType=type;
}

SceneDraw *SceneDraw::factorySceneDraw()
{
    QList<SceneDraw*>::const_iterator iter = _draws.constBegin();
    for ( ; iter != _draws.constEnd() ; ++iter ){
        if ((*iter)->myType()==_drawType )
            return (*iter);
    }
    return nullptr;
}

int SceneDraw::indexOf(SceneDraw *draw)
{
    return _draws.indexOf(draw);
}

SceneDraw *SceneDraw::index(int index)
{
    return _draws.at(index);
}

void SceneDraw::mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{

}

void SceneDraw::mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{

}

void SceneDraw::mouseReleaseEvent(QGraphicsSceneMouseEvent *event,QGraphicsScene *scene)
{

}
