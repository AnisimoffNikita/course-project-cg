#include "modelview2.h"

#include "src/animation/rotatetransform.h"
#include "src/animation/scene.h"
#include "src/animation/renderer.h"
#include "src/animation/sceneobjectfactory.h"
#include "src/animation/lightzbufferrenderer.h"
#include "src/animation/objloader.h"
#include "src/animation/scaletransformation.h"
#include "src/animation/rotatetransform.h"
#include "src/animation/actions.h"
#include <QPainter>

ModelView2::ModelView2(QWidget *parent)
    : QWidget(parent)
    , scene(std::make_unique<Scene>())
    , renderer(std::make_unique<LightZBufferRenderer>())
    , actionManager(std::make_unique<ActionManager>())
    , timer(new QTimer(this))
{
    sceneSetup();
    timer->setInterval(1000 / 60.0);
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
    auto dy = event->pos().y() - lastPos.y();
    auto camera = scene->getActiveCamera();

    if (camera.expired())
    {
        return;
    }

    auto workCamera = camera.lock();
    Vec3 cameraPos = workCamera->getPosition();
    RotateYTransformation y(Math::ToRadians(-dx) / 2, Vec3(0, 0, 0));
    workCamera->transform(y);

    if (Math::Abs(cameraPos.x()) > Math::Abs(cameraPos.z()))
    {
        RotateZTransformation z(Math::ToRadians(-dy) / 2, Vec3(0, 0, 0));
        workCamera->transform(z);
    }
    else
    {
        RotateXTransformation x(Math::ToRadians(-dy) / 2, Vec3(0, 0, 0));
        workCamera->transform(x);
    }

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
    int32 elapsed = time.elapsed();
    time.start();
    float delta = elapsed / 1000.0;
    actionManager->update(delta);
    int32 w = width(), h = height();
    renderer->start(w, h);
    scene->render(renderer);
    renderer->finish();
    uchar *buffer = renderer->getRendered();
    image = QImage(buffer, w, h, QImage::Format_RGB32);
    this->repaint();
}

void ModelView2::sceneSetup()
{
    CameraFactory::PerspectiveData data;
    data.fovX = Math::ToRadians(120);
    data.fovY = Math::ToRadians(120);
    data.near = 0.01;
    data.far = 10000;
    CameraFactory cameraFactory(Vec3(4.5, 4.5, 0), Vec3(0, 0, 0), Vec3(0, -1, 0),
                                data);
    auto camera = cameraFactory.create();
    scene->add(camera);
    scene->setActiveCamera(camera);
    {
        ObjLoader loader(":/obj/conveor.obj");
        Mesh mesh = loader.load();
        ModelFactory modelFactory(Vec3(0, 0, 0), mesh);
        auto model = modelFactory.create();
        scene->add(model);
    }
    {
        ObjLoader loader(":/obj/band.obj");
        Mesh mesh = loader.load();
        ModelFactory modelFactory(Vec3(0, 0, 0.08), mesh);
        auto model = modelFactory.create();
        scene->add(model);
    }
    {
        ObjLoader loader(":/obj/cylinder.obj");
        Mesh mesh = loader.load();
        ModelFactory modelFactory(Vec3(3.5, 1.01, 0.3), mesh);
        auto model = modelFactory.create();
        RotateYTransformation rot(40, Vec3(3.5, 1.01, 0.3));
        model->transform(rot);
        scene->add(model);
        auto act = make_unique<RepeatMoveAction>(7, model, Vec3(-3.5, 1.01,
                   0.3));
        actionManager->add(std::move(act));
    }
    AmbientLightFactory ambientFactory(0.4);
    auto ambient = ambientFactory.create();
    scene->add(ambient);
    scene->add(ambient);
    {
        PointLightFactory pointFactory(Vec3(5, 5, -5), 2);
        auto point = pointFactory.create();
        scene->add(point);
    }
    {
        PointLightFactory pointFactory(Vec3(-5, 5, 5), 1.5);
        auto point = pointFactory.create();
        scene->add(point);
    }
}
