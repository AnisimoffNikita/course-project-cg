#ifndef MODELVIEW_H
#define MODELVIEW_H

#include <QWidget>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QPixmap>
#include <QTimer>

#include <memory>

#include "src/animation/scene.h"
#include "src/animation/renderer.h"

class ModelView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ModelView(QWidget *parent = 0);

    void setModelScene(std::unique_ptr<Scene> &&value);

protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    void updateCanvas();
    void scheduler();

    QGraphicsScene *graphicsScene;
    QPixmap canvas;

    QPoint lastPos;
    QTimer *timer;

    std::unique_ptr<Scene> scene;
    std::unique_ptr<Renderer> renderer;
};

#endif // MODELVIEW_H
