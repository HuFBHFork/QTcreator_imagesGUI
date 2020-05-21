QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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





SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui



#############################imageGUI_demo for usage lib/so
unix:!macx: LIBS += -L$$PWD/import/lib/ -limagesGUI

INCLUDEPATH += $$PWD/import/include
DEPENDPATH += $$PWD/import/include

####################################################


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


################################ imagesGUI_demo for develop
#SOURCES += \
#    imagesGUI/Items/Polygon_S/labelitem_polygon_s.cpp \
#    imagesGUI/Items/Rect/scenedraw_rect.cpp \
#    imagesGUI/Items/Rect_S/graphicsitemresizer.cpp \
#    imagesGUI/Items/Rect_S/handlerstrategies.cpp \
#    imagesGUI/Items/Rect_S/labelitem_rect_s.cpp \
#    imagesGUI/Items/Rect_S/resizehandleitem.cpp \
#    imagesGUI/Items/Rect_S/scenedraw_rect_s.cpp \
#    imagesGUI/Items/Rect_SR/graphicsitemadjuster.cpp \
#    imagesGUI/Items/Rect_SR/labelitem_rect_sr.cpp \
#    imagesGUI/Items/Rect_SR/rotatehandleitem.cpp \
#    imagesGUI/Items/Rect_SR/scenedraw_rect_sr.cpp \
#    imagesGUI/Mainwidget/labelwidget.cpp \
#    imagesGUI/Scene/labelscene.cpp \
#    imagesGUI/Scene/scenedraw.cpp \
#    imagesGUI/Viewer/labelview.cpp \
#    imagesGUI/Viewer/meview.cpp \
#    main.cpp \
#    mainwindow.cpp

#HEADERS += \
#    imagesGUI/Items/Polygon_S/labelitem_polygon_s.h \
#    imagesGUI/Items/Rect/scenedraw_rect.h \
#    imagesGUI/Items/Rect_S/graphicsitemresizer.h \
#    imagesGUI/Items/Rect_S/handlerstrategies.h \
#    imagesGUI/Items/Rect_S/labelitem_rect_s.h \
#    imagesGUI/Items/Rect_S/resizehandleitem.h \
#    imagesGUI/Items/Rect_S/scenedraw_rect_s.h \
#    imagesGUI/Items/Rect_SR/graphicsitemadjuster.h \
#    imagesGUI/Items/Rect_SR/labelitem_rect_sr.h \
#    imagesGUI/Items/Rect_SR/rotatehandleitem.h \
#    imagesGUI/Items/Rect_SR/scenedraw_rect_sr.h \
#    imagesGUI/Mainwidget/labelwidget.h \
#    imagesGUI/Mainwidget/labelwidgetcustombtn.h \
#    imagesGUI/Scene/labelscene.h \
#    imagesGUI/Scene/scenedraw.h \
#    imagesGUI/Scene/sceneio.h \
#    imagesGUI/Viewer/labelview.h \
#    imagesGUI/Viewer/meview.h \
#    imagesGUI/imagesGUI.h \
#    mainwindow.h

#FORMS += \
#    imagesGUI/Mainwidget/labelwidget.ui \
#    imagesGUI/Viewer/labelview.ui \
#    mainwindow.ui

#RESOURCES += \
#    imagesGUI/Mainwidget/rsLabelWidget.qrc

#INCLUDEPATH += $$PWD/imagesGUI

############################################################


