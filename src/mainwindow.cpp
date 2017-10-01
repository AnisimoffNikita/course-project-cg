#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardPaths>
#include <QImageReader>
#include <QImageWriter>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateActions();
}

MainWindow::~MainWindow()
{
    delete ui;
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

    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(filename)).arg(image.width()).arg(image.height()).arg(image.depth());
    statusBar()->showMessage(message);
    return true;
}

void MainWindow::setImage(const QImage &newImage)
{
    image = newImage;
    ui->lblImage->setPixmap(QPixmap::fromImage(image));
    scaleFactor = 1.0;

    updateActions();

    ui->lblImage->adjustSize();
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
    dialog.selectMimeTypeFilter("image/jpeg");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
}

void MainWindow::fitToWindow()
{
}

void MainWindow::on_actFit_triggered()
{
    fitToWindow();
}

void MainWindow::updateActions()
{
    ui->actFit->setEnabled(!image.isNull());
}
