#include "imageview.h"

#include <QStyle>

ImageView::ImageView(QWidget *parent) :
    QGraphicsView(parent),
    scene(new QGraphicsScene())
{
    this->setStyleSheet("border: none;outline: none;");
    this->setBackgroundBrush(QBrush(QColor(236,232,228)));
    this->setScene(scene);
}

void ImageView::setImage(const QImage &image)
{
    scene->addPixmap(QPixmap::fromImage(image));
    this->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void ImageView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    this->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}
