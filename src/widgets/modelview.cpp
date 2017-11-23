#include "modelview.h"

#include <QStyle>

#include "src/animation/rotatetransform.h"

#include "src/animation/scene.h"
#include "src/animation/renderer.h"
#include "src/animation/meshgenerator.h"
#include "src/animation/sceneobjectfactory.h"
#include "src/animation/lightzbufferrenderer.h"
#include "src/animation/objloader.h"

ModelView::ModelView(QWidget *parent) :
    QGraphicsView(parent),
    graphicsScene(new QGraphicsScene()),
    canvas(640, 480),
    scene(std::make_unique<Scene>())
{
    //    this->setStyleSheet("border: none;outline: none;");
    //    this->setBackgroundBrush(QBrush(QColor(236, 232, 228)));
    //    this->setScene(graphicsScene);
    //    this->setSizeAdjustPolicy(AdjustIgnored);
    //    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    //    CameraFactory::PerspectiveData data;
    //    data.fovX = Math::ToRadians(80);
    //    data.fovY = Math::ToRadians(80);
    //    data.near = 0.1;
    //    data.far = 100;
    //    CameraFactory cameraFactory(Vec3(6, 0, 6), Vec3(0, 0, 0), Vec3(0, 1, 0),
    //                                data);
    //    auto camera = cameraFactory.create();
    //    scene->add(camera);
    //    scene->setActiveCamera(camera);
    //    {
    //        ObjLoader loader("/home/nikita/untitled.obj");
    //        Mesh mesh = loader.load();
    //        ModelFactory modelFactory(Vec3(0, 0, 0), mesh);
    //        auto model = modelFactory.create();
    //        scene->add(model);
    //    }
    //    //    {
    //    //        ObjLoader loader("/home/nikita/untitled2.obj");
    //    //        Mesh mesh = loader.load();
    //    //        ModelFactory modelFactory(Vec3(-3, -3, -3), mesh);
    //    //        auto model = modelFactory.create();
    //    //        scene->add(model);
    //    //    }
    //    AmbientLightFactory ambientFactory(0.4);
    //    auto ambient = ambientFactory.create();
    //    scene->add(ambient);
    //    {
    //        PointLightFactory pointFactory(Vec3(3, 3, 3), 1);
    //        auto point = pointFactory.create();
    //        scene->add(point);
    //    }
    //    //    {
    //    //        PointLightFactory pointFactory(Vec3(-3, 3, 3), 1);
    //    //        auto point = pointFactory.create();
    //    //        scene->add(point);
    //    //    }
    //    renderer = std::make_unique<LightZBufferRenderer>(300, 1024, 768);
    //    scene->render(renderer);
    //    canvas = QPixmap::fromImage(renderer->getRendered());
    //    updateCanvas();
    //    timer = new QTimer(this);
    //    timer->setInterval(1000 / 24.0); // ms
    //    connect(timer, &QTimer::timeout, this,  &ModelView::scheduler);
    //    timer->start();
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
    auto dy = event->pos().y() - lastPos.y();
    auto camera = scene->getActiveCamera();

    if (camera.expired())
    {
        return;
    }

    auto workCamera = camera.lock();
    Vec3 cameraPos = workCamera->getPosition();
    RotateYTransformation y(Math::ToRadians(dx) / 2, Vec3(0, 0, 0));
    workCamera->transform(y);
    //    if (Math::Abs(cameraPos.x()) > Math::Abs(cameraPos.z()))
    //    {
    //        RotateYTransformation z(Math::ToRadians(-dy) / 2, Vec3(0, 0, 0));
    //        workCamera->transform(z);
    //    }
    //    else
    //    {
    //        RotateXTransformation x(Math::ToRadians(-dy) / 2, Vec3(0, 0, 0));
    //        workCamera->transform(x);
    //    }
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
