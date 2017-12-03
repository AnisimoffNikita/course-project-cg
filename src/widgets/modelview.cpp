#include "modelview.h"

#include <QStyle>

#include "src/animation/rotatetransformation.h"

#include "src/animation/scene.h"
#include "src/animation/renderer.h"
#include "src/animation/sceneobjectfactory.h"
#include "src/animation/lightzbufferrenderer.h"
#include "src/animation/objloader.h"

ModelView::ModelView(QWidget *parent) :
    QGraphicsView(parent),
    graphicsScene(new QGraphicsScene()),
    canvas(640, 480),
    scene(std::make_unique<Scene>())
{
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
    auto dx = event->pos().x() - lastPos.x();
    auto camera = scene->getActiveCamera();

    if (camera.expired())
    {
        return;
    }

    auto workCamera = camera.lock();
    RotateYTransformation y(Math::ToRadians(dx) / 2, Vec3(0, 0, 0));
    workCamera->transform(y);
    lastPos = event->pos();
}

void ModelView::updateCanvas()
{
    graphicsScene->clear();
    graphicsScene->addPixmap(canvas);
    this->fitInView(graphicsScene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void ModelView::scheduler()
{
    //    scene->render(renderer);
    //    canvas = QPixmap::fromImage(renderer->getRendered());
    //    updateCanvas();
}

void ModelView::setModelScene(std::unique_ptr<Scene> &&value)
{
    scene = std::move(value);
}
