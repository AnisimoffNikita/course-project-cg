#include "modelview2.h"

#include "src/animation/rotatetransform.h"
#include "src/animation/scene.h"
#include "src/animation/renderer.h"
#include "src/animation/meshgenerator.h"
#include "src/animation/sceneobjectfactory.h"
#include "src/animation/lightzbufferrenderer.h"
#include "src/animation/objloader.h"
#include <QPainter>

ModelView2::ModelView2(QWidget *parent)
    : QWidget(parent)
    , scene(std::make_unique<Scene>())
    , renderer(std::make_unique<LightZBufferRenderer>())
{
    sceneSetup();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this,  &ModelView2::scheduler);
    timer->start();
    time.start();
}

void ModelView2::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void ModelView2::mouseMoveEvent(QMouseEvent *event)
{
    auto dx = event->pos().x() - lastPos.x();
    //    auto dy = event->pos().y() - lastPos.y();
    auto camera = scene->getActiveCamera();

    if (camera.expired())
    {
        return;
    }

    auto workCamera = camera.lock();
    RotateYTransformation y(Math::ToRadians(-dx) / 2, Vec3(0, 0, 0));
    workCamera->transform(y);
    lastPos = event->pos();
}

void ModelView2::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0, 0, image);
}

void ModelView2::updateCanvas()
{
}

void ModelView2::scheduler()
{
    int w = width(), h = height();
    renderer->start(300, w, h);
    scene->render(renderer);
    uchar *buffer = renderer->getRendered();
    image = QImage(buffer, w, h, QImage::Format_RGB32);
    renderer->finish();
    this->repaint();
}

void ModelView2::sceneSetup()
{
    CameraFactory::PerspectiveData data;
    data.fovX = Math::ToRadians(80);
    data.fovY = Math::ToRadians(80);
    data.near = 0.1;
    data.far = 100;
    CameraFactory cameraFactory(Vec3(6, 0, 6), Vec3(0, 0, 0), Vec3(0, 1, 0),
                                data);
    auto camera = cameraFactory.create();
    scene->add(camera);
    scene->setActiveCamera(camera);
    {
        ObjLoader loader("/home/nikita/untitled.obj");
        Mesh mesh = loader.load();
        ModelFactory modelFactory(Vec3(0, 0, 0), mesh);
        auto model = modelFactory.create();
        scene->add(model);
    }
    //    {
    //        ObjLoader loader("/home/nikita/untitled2.obj");
    //        Mesh mesh = loader.load();
    //        ModelFactory modelFactory(Vec3(-3, -3, -3), mesh);
    //        auto model = modelFactory.create();
    //        scene->add(model);
    //    }
    AmbientLightFactory ambientFactory(0.4);
    auto ambient = ambientFactory.create();
    scene->add(ambient);
    {
        PointLightFactory pointFactory(Vec3(3, 3, 3), 1);
        auto point = pointFactory.create();
        scene->add(point);
    }
    //    {
    //        PointLightFactory pointFactory(Vec3(-3, 3, 3), 1);
    //        auto point = pointFactory.create();
    //        scene->add(point);
    //    }
}
