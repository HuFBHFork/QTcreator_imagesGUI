#include "labelwidget.h"
#include "ui_labelwidget.h"

#include"Scene/labelscene.h"
#include"Scene/scenedraw.h"
#include"Scene/sceneio.h"

#include"Items/Rect/scenedraw_rect.h"
#include"Items/Rect_S/scenedraw_rect_s.h"
#include"Items/Rect_SR/scenedraw_rect_sr.h"
#include"Items/Polygon_S/labelitem_polygon_s.h"

#include<QFileDialog>
#include<QScrollBar>
#include<QDebug>

#include"labelwidgetcustombtn.h"


LabelWidget::LabelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LabelWidget)
{
    ui->setupUi(this);

    //初始化固定的属性
    ini_params();
    ini_box(ui->box_draw_area);
    ini_box(ui->box_btnCustom_area);


    //构造本地对象
    _sceneLocal=new LabelScene();   
    _sceneIOLocal=new SceneIO();//do nothing
    new_boxDrawItems();
    new_boxCustomItems();


    //定制设置：采用默认
    ini_LabelWidget();
    this->setMouseTracking(true);
}

LabelWidget::~LabelWidget()
{
    delete _sceneLocal;
    delete _sceneIOLocal;
    del_boxDrawItems(_drawDicLocal);
    del_boxCustomItems(_cBtnDicLocal);

    //查询与处理定制的对象
    del_boxDrawItems(_drawDic);
    del_boxCustomItems(_cBtnDic);

    delete ui;
}

void LabelWidget::setScene(QGraphicsScene *scene)
{
    if(scene==nullptr)
    {
        return ;
    }

    ui->graphicsView->setScene(scene);//接收外部scene，但不需要用本类成员记录
    _flag_enable_draw=false;//外部scene不支持绘图，仅做基本显示交互
}

QGraphicsScene *LabelWidget::getScene() const
{
    return ui->graphicsView->scene();
}

bool LabelWidget::is_drawSupport() const
{
    return _flag_enable_draw;
}

void LabelWidget::setScene(LabelScene *scene)
{
    if(scene==nullptr)
    {
        return ;
    }
    ui->graphicsView->setScene(scene);//替换scene，且支持保留绘制功能
}

void LabelWidget::reset_scene()
{
    ui->graphicsView->setScene(_sceneLocal);
    _flag_enable_draw=true;
}

void LabelWidget::set_enable_viewMove(bool flag)
{
    ui->graphicsView->set_flag_viewTranslate(flag);
}

void LabelWidget::set_enable_viewZoom(bool flag)
{
    ui->graphicsView->set_flag_viewZoom(flag);
}

void LabelWidget::set_visible_scrollBar(bool flag)
{
    ui->graphicsView->set_flag_showScrollBar(flag);
}

void LabelWidget::set_view_zoomRatio(int stepvalue)
{
    ui->graphicsView->setZoomRatio(stepvalue);
}

void LabelWidget::set_view_zoomValue(int zoomValue)
{
    ui->graphicsView->setViewScaleValue(zoomValue);
}

void LabelWidget::set_view_color(QColor color)
{
    ui->graphicsView->setViewBackgroundColor(color);
}

QRect LabelWidget::get_view_geometry() const
{
    return ui->graphicsView->getViewGrometry();
}

void LabelWidget::set_sceneIO(SceneIO *sceneio)
{
    if(sceneio!=nullptr)
    {
        _sceneIO=sceneio;
        sceneio->setScene(ui->graphicsView->scene());
    }
}

SceneIO *LabelWidget::get_sceneIO()
{
    return _sceneIO;
}

void LabelWidget::reset_sceneIO()
{
    _sceneIO=_sceneIOLocal;
}

void LabelWidget::set_sceneIO_hide(bool hide, LabelWidget::IObtn btn)
{
    switch (btn) {
    case Load:
        ui->btn_read->setVisible(!hide);
        break;
    case Save:
        ui->btn_write->setVisible(!hide);
        break;
    case Print:
        ui->btn_print->setVisible(!hide);
        break;
    case All:
        ui->box_sceneIO->setVisible(!hide);
    default:
        break;
    }
}

void LabelWidget::set_sceneIO_usingDialog(bool flag)
{
    _flag_sceneIO_usingDialog=flag;
}

bool LabelWidget::is_sceneIO_usingDialog() const
{
    return _flag_sceneIO_usingDialog;
}

void LabelWidget::set_boxDraw_hide(bool hide)
{
    ui->box_draw->setVisible(!hide);
}

void LabelWidget::clear_boxDraw()
{
    //隐藏本地Draw，删除定制Draw
    set_boxDraw_localItems_hide();

    del_boxDrawItems(_drawDic);//仅删除ui的btn，不删除接收的draw
}

void LabelWidget::reset_boxDraw()
{
    //先清除外部，再显示原来本地
    del_boxDrawItems(_drawDic);

    //设置显示
    set_boxDraw_localItems_hide(false);
}

void LabelWidget::add_boxDrawItem(SceneDraw *draw, const QIcon &icon)
{
    _boxDraw->removeItem(_boxDrawSpacer);

    QPushButton *btn=new QPushButton();
    btn->setIcon(icon);
    btn->setMaximumWidth(30);
    _boxDraw->addWidget(btn);
    connect(btn,SIGNAL(clicked(bool)),this,SLOT(on_boxDraw_btn_clicked()));

    _drawDic.insert(btn,draw);

    _boxDraw->addItem(_boxDrawSpacer);
}

void LabelWidget::add_boxDrawItem(SceneDraw *draw, const QString &name)
{
    _boxDraw->removeItem(_boxDrawSpacer);

    QPushButton *btn=new QPushButton(name);
    _boxDraw->addWidget(btn);
    connect(btn,SIGNAL(clicked(bool)),this,SLOT(on_boxDraw_btn_clicked()));

    _drawDic.insert(btn,draw);

    _boxDraw->addItem(_boxDrawSpacer);
}

void LabelWidget::add_boxDrawItem(QPushButton *btn, SceneDraw *draw)
{
    _boxDraw->removeItem(_boxDrawSpacer);

    _boxDraw->addWidget(btn);
    connect(btn,SIGNAL(clicked(bool)),this,SLOT(on_boxDraw_btn_clicked()));

    _drawDic.insert(btn,draw);

    _boxDraw->addItem(_boxDrawSpacer);
}

void LabelWidget::set_enable_DrawMode(bool flag)
{
    //绘图，则视图不可移动
    ui->graphicsView->set_flag_viewTranslate(!flag);

    //如果是Labelscene实例
    if(_flag_enable_draw)
    {
        LabelScene *labelScene=(LabelScene*)ui->graphicsView->scene();
        if(flag)
        {
            labelScene->setAddMode(LabelScene::AddMode::DrawMode);
        }
        else
        {
            labelScene->setAddMode(LabelScene::AddMode::NormalMode);
        }
    }
}

void LabelWidget::set_boxCustom_hide(bool hide)
{
    ui->box_btnCustom->setVisible(!hide);
}

void LabelWidget::set_boxCustom_title(const QString &title)
{
    ui->box_btnCustom->setTitle(title);
}

LabelView *LabelWidget::get_labelView() const
{
    return ui->graphicsView;
}

void LabelWidget::clear_boxCustom()
{
    //隐藏本地，删除定制
    set_boxCustom_localItems_hide();
    del_boxCustomItems(_cBtnDic);
}

void LabelWidget::reset_boxCustom()
{
    //删除定制，显示本地
    del_boxCustomItems(_cBtnDic);
    set_boxCustom_localItems_hide(false);
}

void LabelWidget::add_boxCustomItem(LabelWidgetCustomBtn *cBtn, const QIcon &icon)
{
    _boxCustomBtn->removeItem(_boxCustomBtnSpacer);

    QPushButton *btn=new QPushButton();
    btn->setIcon(icon);
    btn->setMaximumWidth(30);
    _boxCustomBtn->addWidget(btn);
    connect(btn,SIGNAL(clicked(bool)),this,SLOT(on_boxCustom_btn_clicked()));

    _cBtnDic.insert(btn,cBtn);

    _boxCustomBtn->addItem(_boxCustomBtnSpacer);
}

void LabelWidget::add_boxCustomItem(LabelWidgetCustomBtn *cBtn, const QString &name)
{
    _boxCustomBtn->removeItem(_boxCustomBtnSpacer);

    QPushButton *btn=new QPushButton(name);
    _boxCustomBtn->addWidget(btn);
    connect(btn,SIGNAL(clicked(bool)),this,SLOT(on_boxCustom_btn_clicked()));

    _cBtnDic.insert(btn,cBtn);

    _boxCustomBtn->addItem(_boxCustomBtnSpacer);
}

void LabelWidget::add_boxCustomItem(QPushButton *btn, LabelWidgetCustomBtn *cBtn)
{
    _boxCustomBtn->removeItem(_boxCustomBtnSpacer);

    _boxCustomBtn->addWidget(btn);
    connect(btn,SIGNAL(clicked(bool)),this,SLOT(on_boxCustom_btn_clicked()));

    _cBtnDic.insert(btn,cBtn);

    _boxCustomBtn->addItem(_boxCustomBtnSpacer);
}

void LabelWidget::set_pixmap(const QPixmap &pixmap)
{
    //确保app只有一张处理图：其他的元素在此app中由绘制创建
    if(_mainImg!=nullptr)
    {
        _sceneLocal->removeItem(_mainImg);
        delete _mainImg;
    }
    _sceneLocal->setSceneRect(0,0,pixmap.width(),pixmap.height());
    _mainImg=_sceneLocal->addPixmap(pixmap);
    _mainImg->setZValue(-1);

}

void LabelWidget::set_image(const QString &fileName)
{
    set_pixmap(QPixmap(fileName));
}

QPixmap LabelWidget::get_pixmap() const
{
    if(_mainImg==nullptr)
    {
        return QPixmap();
    }
    return _mainImg->pixmap();
}

void LabelWidget::set_image(QImage &img)
{
    //QImage转化为QPixmap
    QPixmap pixmap;
    pixmap.convertFromImage(img);
    set_pixmap(pixmap);
}

QImage LabelWidget::get_image() const
{
    //QPixmap转化为QImage
    if(_mainImg==nullptr)
    {
        return QImage();
    }
    QPixmap pixmap=_mainImg->pixmap();
    return pixmap.toImage();
}


void LabelWidget::ini_LabelWidget()
{
    //labelWidget默认设置：基本功能：用作View,接收scene，但具有本地scene
    //不显示工具栏
    set_sceneIO_hide();
    set_boxDraw_hide();
    set_boxCustom_hide();

    //采用本地scene、sceneIO
    reset_scene();
    reset_sceneIO();

    //设置默认值
    _sceneLocal->setSceneRect(0,0,1000,1000);
}

void LabelWidget::ini_box(QScrollArea *p)
{
    //设置样式
    p->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    p->horizontalScrollBar()->setStyleSheet("QScrollBar{height:5px;}");
}

void LabelWidget::ini_params()
{
    //获取参数用于初始化
    _boxDraw=ui->scrollAreaWidgetContents->layout();
    _boxCustomBtn=ui->scrollAreaWidgetContents_2->layout();

    //确保组合到Widget中，被widget管理
    _boxDrawSpacer=new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    _boxCustomBtnSpacer=new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

}

void LabelWidget::new_boxDrawItems()
{
    //
    _boxDraw->removeItem(_boxDrawSpacer);

    //构造本地items:创建btn、draw、绑定事件
    //lsDraw:new_drawLocal
    QList<SceneDraw*> lsDraw;
    lsDraw.append(new SceneDraw_Rect());
    lsDraw.append(new SceneDraw_Rect_S());
    lsDraw.append(new SceneDraw_Rect_SR());
    lsDraw.append(new SceneDraw_Polygon_S());

    //btnMsg:new_btn
    QList<QIcon> lsIcon;
    lsIcon.append(QIcon(":/drawtool/rect"));
    lsIcon.append(QIcon(":/drawtool/rect_s"));
    lsIcon.append(QIcon(":/drawtool/rect_sr"));
    lsIcon.append(QIcon(":/drawtool/polygon_s"));
    int index=0;

    //connect
    for(auto iter:lsDraw)
    {
        //btn
        QPushButton *btn=new QPushButton();
        btn->setIcon(lsIcon.at(index++));
        btn->setMaximumWidth(30);
        _boxDraw->addWidget(btn);
        connect(btn,SIGNAL(clicked(bool)),this,SLOT(on_boxDraw_btn_clicked()));

        //draw
        _drawDicLocal.insert(btn,iter);
    }

    //
    _boxDraw->addItem(_boxDrawSpacer);
}

void LabelWidget::set_boxDraw_localItems_hide(bool hide)
{
    //不析构对象：遍历本地对象，从UI中移除(隐藏)
    QList<QPushButton *> ls=_drawDicLocal.keys();
    for(auto iter:ls)
    {
        iter->setVisible(!hide);
    }
}

void LabelWidget::del_boxDrawItems(QMap<QPushButton *, SceneDraw *> &drawDic)
{
    QList<QPushButton *> ls=drawDic.keys();
    for(auto iter:ls)
    {
        delete iter;//释放对应btn
        delete drawDic[iter];//释放_drawLocal
    }

    drawDic.clear();//清空指针列表

}

void LabelWidget::new_boxCustomItems()
{
    //
    _boxCustomBtn->removeItem(_boxCustomBtnSpacer);

    //构造本地items:本地定制按钮doNothing:创建btn、custombtn、绑定事件
    //lsDraw
    QList<LabelWidgetCustomBtn*> lsCustom;
    lsCustom.append(new LabelWidgetCustomBtn(this));

    //connect
    for(auto iter:lsCustom)
    {
        //btn
        QPushButton *btn=new QPushButton("选择");
        _boxCustomBtn->addWidget(btn);
        connect(btn,SIGNAL(clicked(bool)),this,SLOT(on_boxCustom_btn_selectMode_click()));//注意修改回来

        //cbtn
        _cBtnDicLocal.insert(btn,iter);
    }

    _boxCustomBtn->addItem(_boxCustomBtnSpacer);
}

void LabelWidget::set_boxCustom_localItems_hide(bool hide)
{
    QList<QPushButton *> ls=_cBtnDicLocal.keys();
    for(auto iter:ls)
    {
        iter->setVisible(!hide);
    }
}

void LabelWidget::del_boxCustomItems(QMap<QPushButton *, LabelWidgetCustomBtn *> &cBtnDic)
{
    QList<QPushButton *> ls=cBtnDic.keys();
    for(auto iter:ls)
    {
        delete iter;//释放对应btn
        delete cBtnDic[iter];//释放_CustomLocal
    }

    cBtnDic.clear();//清空指针列表
}

void LabelWidget::on_btn_read_clicked()
{
    QString path;
    if(_flag_sceneIO_usingDialog)
    {
        path = QFileDialog::getOpenFileName(this,
                tr("加载文件"),
                "",
                tr("描述文件(*.xml *.json *.txt);;配置文件(*.ini; *.cfg; *.conf; *.config; *.dat);;全部( *.*)"));
    }

    //sceneIO:加载（获取路径）
    if(_sceneIO!=nullptr)
    {
        _sceneIO->sceneLoad(path);
    }
}

void LabelWidget::on_btn_write_clicked()
{
    QString path;
    if(_flag_sceneIO_usingDialog)
    {
        path = QFileDialog::getSaveFileName(this,
                tr("保存文件"),
                "",
                tr("描述文件(*.xml *.json *.txt);;配置文件(*.ini; *.cfg; *.conf; *.config; *.dat);;全部( *.*)"));
    }

    //sceneIO:保存（获取路径）
    if(_sceneIO!=nullptr)
    {
        _sceneIO->sceneSave(path);
    }
}

void LabelWidget::on_btn_print_clicked()
{
    QString path;
    if(_flag_sceneIO_usingDialog)
    {
        path = QFileDialog::getSaveFileName(this,
                tr("打印"),
                "",
                tr("图片(*.png *.jpg *.bmp)"));
    }

    //sceneIO：打印
    if(_sceneIO!=nullptr)
    {
        _sceneIO->scenePrint(path);
    }
}

void LabelWidget::on_boxDraw_btn_clicked()
{
    //先确定点击的按钮，再进行对应的绘制设置
    QPushButton *btn = (QPushButton*) sender();
    SceneDraw* selectDraw=nullptr;

    //获取对象
    if(_drawDic.contains(btn))
    {
        selectDraw=_drawDic[btn];//**!这么坑的吗？没有的话会创建一个Map<item>
    }
    else if(_drawDicLocal.contains(btn))
    {
        selectDraw=_drawDicLocal[btn];
    }

    //设置画布：赋予绘制对象
    if(selectDraw!=nullptr&&_flag_enable_draw)
    {
        LabelScene *labelScene=(LabelScene *)ui->graphicsView->scene();
        labelScene->setSenceDraw(selectDraw);
    }

    //禁止视图拖图（与绘制行为冲突）
    ui->graphicsView->set_flag_viewTranslate(false);
}

void LabelWidget::on_boxCustom_btn_clicked()
{
    QPushButton *btn = (QPushButton*) sender();
    LabelWidgetCustomBtn* tmp=_cBtnDic[btn];
    if(tmp!=nullptr)
    {
        tmp->labelWidget_on_customBtnClick(this);//定制按钮支持this的所有公有行为
    }

}

void LabelWidget::on_boxCustom_btn_selectMode_click()
{
    //默认定制按钮：鼠标模式（选择，非绘制）
    ui->graphicsView->set_flag_viewTranslate(true);

    //如果是Labelscene实例
    if(_flag_enable_draw)
    {
        LabelScene *labelScene=(LabelScene*)ui->graphicsView->scene();
        labelScene->setAddMode(LabelScene::AddMode::NormalMode);
    }

}
