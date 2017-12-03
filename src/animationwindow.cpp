#include "animationwindow.h"
#include "ui_animationwindow.h"

AnimationWindow::AnimationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AnimationWindow)
{
    ui->setupUi(this);
}

AnimationWindow::~AnimationWindow()
{
    delete ui;
}
