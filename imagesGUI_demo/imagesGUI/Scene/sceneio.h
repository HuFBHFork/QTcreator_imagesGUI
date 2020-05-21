#ifndef SCENEIO_H
#define SCENEIO_H

/*
 *SenceIO职能：
 * 作为Sence的输入输出接口
 * 依赖项：sence
 *
*/


#include <QGraphicsScene>

class SceneIO
{
public:
    SceneIO(QGraphicsScene* scene=nullptr){_scene=scene;}
    ~SceneIO(){}

    void setScene(QGraphicsScene* scene){_scene=scene;}
    QGraphicsScene* getScene()const{return _scene;}

    //行为接口：子类实现接口，根据属性完成功能
    virtual void sceneLoad(QString path){}//从文件加载scene
    virtual void sceneSave(QString path){}//输出scene信息到文件
    virtual void scenePrint(QString path){}//打印scene到path(输出图片)
private:
    QGraphicsScene* _scene=nullptr;
};



#endif // SCENEIO_H
