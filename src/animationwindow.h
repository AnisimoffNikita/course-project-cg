#ifndef ANIMATIONWINDOW_H
#define ANIMATIONWINDOW_H

#include <QMainWindow>

namespace Ui {
class AnimationWindow;
}

class AnimationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AnimationWindow(QWidget *parent = 0);
    ~AnimationWindow();

private:
    Ui::AnimationWindow *ui;
};

#endif // ANIMATIONWINDOW_H
