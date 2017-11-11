#include "modelview.h"

#include <QStyle>

ModelView::ModelView(QWidget *parent) :
    QGraphicsView(parent),
    scene(new QGraphicsScene())
{
    this->setStyleSheet("border: none;outline: none;");
    this->setBackgroundBrush(QBrush(QColor(236,232,228)));
    this->setScene(scene);
    this->setSizeAdjustPolicy(AdjustIgnored);
    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

void ModelView::setImage(const QImage &image)
{
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(image));
    this->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void ModelView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    this->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void ModelView::mouseMoveEvent(QMouseEvent *event)
{
}
