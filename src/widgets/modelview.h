#ifndef MODELVIEW_H
#define MODELVIEW_H

#include <QWidget>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QMouseEvent>

class ModelView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ModelView(QWidget *parent = 0);

    void setImage(const QImage &image);

protected:
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QGraphicsScene *scene;
};

#endif // MODELVIEW_H
