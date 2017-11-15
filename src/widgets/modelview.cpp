#include "modelview.h"

#include <QStyle>

#include "src/animation/rotatetransform.h"


ModelView::ModelView(QWidget *parent) :
    QGraphicsView(parent),
    graphicsScene(new QGraphicsScene()),
    pixmap(640,480)
{
    this->setStyleSheet("border: none;outline: none;");
    this->setBackgroundBrush(QBrush(QColor(236,232,228)));
    this->setScene(graphicsScene);
    this->setSizeAdjustPolicy(AdjustIgnored);
    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

void ModelView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    this->fitInView(graphicsScene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void ModelView::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void ModelView::mouseMoveEvent(QMouseEvent *event)
{
    if (scene.expired())
        return;
    auto dx = event->pos().x() - lastPos.x();
    auto dy = event->pos().y() - lastPos.y();

    auto work = scene.lock();

    auto camera = work->getActiveCamera();
    if (camera.expired())
        return;

    auto workCamera = camera.lock();

    RotateZTransformation z(Math::ToRadians(dx)/2, Vertex(0,0,0));
    RotateXTransformation x(Math::ToRadians(dy)/2, Vertex(0,0,0));
    workCamera->transform(z);
    workCamera->transform(x);

    auto pixmap = work->render();


    setPixmap(pixmap);

    lastPos = event->pos();
}

std::weak_ptr<Scene> ModelView::getModelScene() const
{
    return scene;
}

void ModelView::setModelScene(const std::weak_ptr<Scene> &value)
{
    scene = value;
}

QPixmap ModelView::getPixmap() const
{
    return pixmap;
}

void ModelView::setPixmap(const QPixmap &value)
{
    pixmap = value;
    graphicsScene->clear();
    graphicsScene->addPixmap(pixmap);
    this->fitInView(graphicsScene->itemsBoundingRect(), Qt::KeepAspectRatio);
}
