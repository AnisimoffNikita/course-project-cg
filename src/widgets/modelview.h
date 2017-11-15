#ifndef MODELVIEW_H
#define MODELVIEW_H

#include <QWidget>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QPixmap>

#include <memory>
#include "src/animation/scene.h"

class ModelView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ModelView(QWidget *parent = 0);

    QPixmap getPixmap() const;
    void setPixmap(const QPixmap &value);

    std::weak_ptr<Scene> getModelScene() const;
    void setModelScene(const std::weak_ptr<Scene> &value);

protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QGraphicsScene *graphicsScene;
    QPixmap pixmap;
    QPoint lastPos;

    std::weak_ptr<Scene> scene;
};

#endif // MODELVIEW_H
