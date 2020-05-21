#include "mainwindow.h"
#include "ui_mainwindow.h"

#include"imagesGUI.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString dir = QCoreApplication::applicationDirPath();

    ui->widget->set_image(dir+"/image.jpg");

}

MainWindow::~MainWindow()
{
    delete ui;
}

