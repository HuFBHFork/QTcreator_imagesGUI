#ifndef LABELWIDGETCUSTOMBTN_H
#define LABELWIDGETCUSTOMBTN_H

#include"labelwidget.h"

class LabelWidgetCustomBtn
{
public:
    LabelWidgetCustomBtn(LabelWidget *labelwidget=nullptr){_labelwidget=labelwidget;}
    ~LabelWidgetCustomBtn(){}

    //属性参数
    void set_labelWidget(LabelWidget *labelwidget){_labelwidget=labelwidget;}
    LabelWidget *get_labelwidget(){return _labelwidget;}

    virtual void labelWidget_on_customBtnClick(LabelWidget *sourceLabelWidget){}

private:
    LabelWidget *_labelwidget=nullptr;

};

#endif // LABELWIDGETCUSTOMBTN_H
