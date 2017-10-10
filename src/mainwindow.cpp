#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardPaths>
#include <QImageReader>
#include <QImageWriter>
#include <QMessageBox>
#include <QScreen>

#include "src/image/imageconverter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    gauss(1.4, 3),
    canny(60, 100)
{
    ui->setupUi(this);
    resize(QGuiApplication::primaryScreen()->availableSize() * 0.8);
    updateActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *)
{

}


void MainWindow::on_actOpenImage_triggered()
{
    openFile();
}

void MainWindow::openFile()
{
    QFileDialog dialog(this, tr("Open File"));
    initFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

bool MainWindow::loadFile(const QString &filename)
{
    QImageReader reader(filename);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(filename), reader.errorString()));
        return false;
    }

    setImage(newImage);

    const QString message = tr("Opened \"%1\", %2x%3")
        .arg(QDir::toNativeSeparators(filename)).arg(image.width()).arg(image.height());
    statusBar()->showMessage(message);
    return true;
}

void MainWindow::setImage(const QImage &newImage)
{
    image = newImage;

    ui->imageView->setImage(image);

    updateActions();
}

void MainWindow::initFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/png");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("png");
}



void MainWindow::updateActions()
{
}

void MainWindow::on_btnCanny_clicked()
{
    Image work = ImageConverter::QImageToImage(image);

    canny.process(work);

    auto temp = ImageConverter::ImageToQImage(work);

    ui->imageView->setImage(temp);
}


void MainWindow::on_btnHough_clicked()
{
    Image work = ImageConverter::QImageToImage(image);

    gauss.process(work);
    canny.process(work);
    hough.process(work);

    auto temp = ImageConverter::ImageToQImage(work);

    ui->imageView->setImage(temp);

}
