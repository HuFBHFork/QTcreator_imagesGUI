QT += widgets

TEMPLATE = lib
DEFINES += IMAGESGUI_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



RESOURCES += \
    Mainwidget/rsLabelWidget.qrc

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    Viewer/labelview.ui \
    Mainwidget/labelwidget.ui

HEADERS += \
    Items/Polygon_S/labelitem_polygon_s.h \
    Items/Rect/scenedraw_rect.h \
    Items/Rect_S/graphicsitemresizer.h \
    Items/Rect_S/handlerstrategies.h \
    Items/Rect_S/labelitem_rect_s.h \
    Items/Rect_S/resizehandleitem.h \
    Items/Rect_S/scenedraw_rect_s.h \
    Items/Rect_SR/graphicsitemadjuster.h \
    Items/Rect_SR/labelitem_rect_sr.h \
    Items/Rect_SR/rotatehandleitem.h \
    Items/Rect_SR/scenedraw_rect_sr.h \
    Scene/labelscene.h \
    Scene/scenedraw.h \
    Scene/sceneio.h \
    Viewer/labelview.h \
    Viewer/meview.h \
    Mainwidget/labelwidget.h \
    Mainwidget/labelwidgetcustombtn.h \
    imagesGUI.h

SOURCES += \
    Items/Polygon_S/labelitem_polygon_s.cpp \
    Items/Rect/scenedraw_rect.cpp \
    Items/Rect_S/graphicsitemresizer.cpp \
    Items/Rect_S/handlerstrategies.cpp \
    Items/Rect_S/labelitem_rect_s.cpp \
    Items/Rect_S/resizehandleitem.cpp \
    Items/Rect_S/scenedraw_rect_s.cpp \
    Items/Rect_SR/graphicsitemadjuster.cpp \
    Items/Rect_SR/labelitem_rect_sr.cpp \
    Items/Rect_SR/rotatehandleitem.cpp \
    Items/Rect_SR/scenedraw_rect_sr.cpp \
    Scene/labelscene.cpp \
    Scene/scenedraw.cpp \
    Viewer/labelview.cpp \
    Viewer/meview.cpp \
    Mainwidget/labelwidget.cpp
