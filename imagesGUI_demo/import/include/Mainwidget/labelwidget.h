#ifndef LABELWIDGET_H
#define LABELWIDGET_H

#include <QWidget>



namespace Ui {
class LabelWidget;
}

/*
 * LabelWidget类：
 * 具备自己对象的组件；也可设置接收外部的对象
 *
 *
*/

//***:画布
class QGraphicsScene;
class SceneIO;

//**:label画布视图
class LabelView;
class LabelScene;
class SceneDraw;

//*:定制按钮
class LabelWidgetCustomBtn;

//
#include<QGraphicsPixmapItem>
class QScrollArea;
class QLayout;
class QPushButton;
class QSpacerItem;

class LabelWidget : public QWidget
{
    Q_OBJECT

public:
    enum IObtn{Load,Save,Print,All};

    explicit LabelWidget(QWidget *parent = nullptr);
    ~LabelWidget();


    //***1：用作View，接收scene
    void setScene(QGraphicsScene *scene);
    QGraphicsScene *getScene() const;//返回scene，以便控制
    bool is_drawSupport()const;
    void setScene(LabelScene *scene);
    void reset_scene();//恢复默认scene

    //**:用作LabelView：不提供完整的get-set，提供最常用的属性
    void set_enable_viewMove(bool flag=true);//视图移动使能
    void set_enable_viewZoom(bool flag=true);//视图放缩使能
    void set_visible_scrollBar(bool flag=true);//滚动条可视化
    void set_view_zoomRatio(int stepvalue);//滚轮单步放缩系数
    void set_view_zoomValue(int zoomValue);//视图放缩值
    void set_view_color(QColor color);//视图背景色
    QRect get_view_geometry()const;//视图在LabelWidget的几何值

    //***2:定制box_IO
    void set_sceneIO(SceneIO *sceneio);//接收一个依赖对象：该对象由外部管理
    SceneIO *get_sceneIO();
    void reset_sceneIO();//恢复本地IO
    void set_sceneIO_hide(bool hide=true,IObtn btn=All);
    void set_sceneIO_usingDialog(bool flag);//设置IO是否采用对话框方式获取路径
    bool is_sceneIO_usingDialog()const;

    //***3：待main验证:定制box_Draw：增删改查，仅清空、还原、增加
    void set_boxDraw_hide(bool hide=true);
    void clear_boxDraw();
    void reset_boxDraw();
    void add_boxDrawItem(SceneDraw *draw,const QIcon &icon);
    void add_boxDrawItem(SceneDraw *draw,const QString &name);
    void add_boxDrawItem(QPushButton*btn,SceneDraw *draw);
    void set_enable_DrawMode(bool flag=true);//设置为绘图（视图不可移动、画布AddMode为绘制模式）


    //***4：待main验证:定制box_btnCustom（可获取各种对象进行控制:lbview,scene-item,=this）
    void set_boxCustom_hide(bool hide=true);
    void set_boxCustom_title(const QString &title);
    LabelView* get_labelView()const;//返回view，以便外部控制view的属性和行为
    void clear_boxCustom();
    void reset_boxCustom();
    void add_boxCustomItem(LabelWidgetCustomBtn *cBtn,const QIcon &icon);
    void add_boxCustomItem(LabelWidgetCustomBtn *cBtn,const QString &name);
    void add_boxCustomItem(QPushButton*btn,LabelWidgetCustomBtn *cBtn);

    //**:应用于图像处理app:mark_后续还需要增加一个异步加载图片的行为
    void set_pixmap(const QPixmap &pixmap);
    void set_image(const QString& fileName);
    QPixmap get_pixmap()const;

    void set_image(QImage &img);
    QImage get_image()const;

protected:
    virtual void ini_LabelWidget();

private:
    void ini_box(QScrollArea* p);
    void ini_params();

    void new_boxDrawItems();
    void set_boxDraw_localItems_hide(bool hide=true);
    void del_boxDrawItems(QMap<QPushButton *, SceneDraw *>& drawDic);

    void new_boxCustomItems();
    void set_boxCustom_localItems_hide(bool hide=true);
    void del_boxCustomItems(QMap<QPushButton*,LabelWidgetCustomBtn*>& cBtnDic);
    

private slots:
    void on_btn_read_clicked();

    void on_btn_write_clicked();

    void on_btn_print_clicked();

    //box按钮点击事件
    void on_boxDraw_btn_clicked();
    void on_boxCustom_btn_clicked();
    void on_boxCustom_btn_selectMode_click();

private:
    Ui::LabelWidget *ui;

    //**1:Scene
    QGraphicsScene *_sceneLocal=nullptr;
    bool _flag_enable_draw=false;

    //**2:SceneIO
    SceneIO *_sceneIOLocal=nullptr,*_sceneIO=nullptr;
    bool _flag_sceneIO_usingDialog=false;

    //**3:Draw
    QLayout *_boxDraw=nullptr;
    QSpacerItem *_boxDrawSpacer=nullptr;
    QMap<QPushButton*,SceneDraw*> _drawDicLocal,_drawDic;

    //**4:btnCustom
    QLayout *_boxCustomBtn=nullptr;
    QSpacerItem *_boxCustomBtnSpacer=nullptr;
    QMap<QPushButton*,LabelWidgetCustomBtn*> _cBtnDicLocal,_cBtnDic;

    //**5:
    QGraphicsPixmapItem * _mainImg=nullptr;


};

#endif // LABELWIDGET_H
