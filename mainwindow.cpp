#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actOpenImage_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    "Open Image",
                                                    "~",
                                                    "Image Files (*.png *.jpg *.bmp)");
    ui->lblImage->setPixmap(QPixmap(filename));
}
