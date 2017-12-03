#ifndef MODELVIEW2_H
#define MODELVIEW2_H

#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QWidget>
#include <QTimer>
#include <QImage>
#include <QTime>

#include "src/animation/scene.h"
#include "src/animation/renderer.h"
#include "src/animation/actionmanager.h"

class ModelView2 : public QWidget
{
    Q_OBJECT
public:
    explicit ModelView2(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void paintEvent(QPaintEvent *);

private:
    void updateCanvas();
    void scheduler();
    void sceneSetup();


    unique_ptr<Scene> scene;
    unique_ptr<Renderer> renderer;
    unique_ptr<ActionManager> actionManager;
    QTimer *timer;
    QPoint lastPos;
    QImage image;
    QTime time;

};

#endif // MODELVIEW2_H
