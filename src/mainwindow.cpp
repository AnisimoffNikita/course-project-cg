#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardPaths>
#include <QImageReader>
#include <QImageWriter>
#include <QMessageBox>
#include <QScreen>
#include <QString>
#include <QDialog>

#include "src/image/imageconverter.h"
#include "src/animation/sceneobjectfactory.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    state(0),
    loaded(false)
{
    ui->setupUi(this);
    resize(QGuiApplication::primaryScreen()->availableSize() * 0.8);
    updateActions();
    debug_setScene();
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

    while (dialog.exec() == QDialog::Accepted &&
            !loadFile(dialog.selectedFiles().first())) {}
}

bool MainWindow::loadFile(const QString &filename)
{
    QImageReader reader(filename);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();

    if (newImage.isNull())
    {
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
    loaded = true;
    ui->imageView->setImage(image);
    updateActions();
}

void MainWindow::initFileDialog(QFileDialog &dialog,
                                QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog)
    {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(
                QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() :
                            picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
            ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();

    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
    {
        mimeTypeFilters.append(mimeTypeName);
    }

    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/png");

    if (acceptMode == QFileDialog::AcceptSave)
    {
        dialog.setDefaultSuffix("png");
    }
}



void MainWindow::updateActions()
{
}

void MainWindow::debug_setScene()
{
}


void MainWindow::on_btnCalibrate_clicked()
{
    if (!loaded)
    {
        return;
    }

    if (ui->rbnStandard->isChecked())
    {
        Image work = ImageConverter::QImageToImage(image);
        GaussianBlur gauss(ui->lblSigma->text().toDouble(),
                           ui->lblKernel->text().toInt());
        CannyEdgeDetector canny(ui->lblMinThresh->text().toInt(),
                                ui->lblMaxThresh->text().toInt());
        HoughTransform hough(ui->lblThresh->text().toInt());
        gauss.process(work);
        canny.process(work);
        auto lines = hough.process(work);
        bool res = calc.calibrate(lines,
                                  ui->edtDist->text().toDouble(),
                                  ui->edtR->text().toDouble(),
                                  ui->edtH->text().toDouble());

        if (!res)
        {
            QMessageBox msgBox;
            msgBox.setText("Калибровка не удалась");
            msgBox.exec();
            return;
        }

        ui->imageView->setImage(ImageConverter::ImageToQImage(work));
    }
    else if (ui->rbnDiag->isChecked())
    {
        calc.calibrate(
            ui->edtDist->text().toDouble(),
            ui->edtScale->text().toDouble());
    }
}

void MainWindow::on_btnEval_clicked()
{
    if (!loaded)
    {
        return;
    }

    Image work = ImageConverter::QImageToImage(image);
    GaussianBlur gauss(ui->lblSigma->text().toDouble(),
                       ui->lblKernel->text().toInt());
    CannyEdgeDetector canny(ui->lblMinThresh->text().toInt(),
                            ui->lblMaxThresh->text().toInt());
    HoughTransform hough(ui->lblThresh->text().toInt());
    gauss.process(work);
    canny.process(work);
    auto lines = hough.process(work);
    auto temp = ImageConverter::ImageToQImage(work);
    auto size = calc.evaluate(lines);

    if (size.getHeight() == -1)
    {
        QMessageBox msgBox;
        msgBox.setText("Цилиндр не найден");
        msgBox.exec();
        return;
    }

    if (size.getHeight() == -2)
    {
        QMessageBox msgBox;
        msgBox.setText("Цилиндр не найден однозначно");
        msgBox.exec();
        return;
    }

    ui->lblResH->setText(QString::number(size.getHeight()));
    ui->lblResR->setText(QString::number(size.getRadius()));
    ui->imageView->setImage(temp);
}

void MainWindow::on_sldSigma_valueChanged(int value)
{
    if (!loaded)
    {
        return;
    }

    ui->lblSigma->setText(QString::number(value / 10.0, 'g', 2));
    bool flag = state == 1;
    on_btnGaussApply_clicked();

    if (flag)
    {
        on_btnCannyApply_clicked();
    }
}

void MainWindow::on_sldKernelSize_valueChanged(int value)
{
    if (!loaded)
    {
        return;
    }

    ui->lblKernel->setText(QString::number(value * 2 - 1));
    bool flag = state == 1;
    on_btnGaussApply_clicked();

    if (flag)
    {
        on_btnCannyApply_clicked();
    }
}


void MainWindow::on_sldMinThresh_valueChanged(int value)
{
    if (!loaded)
    {
        return;
    }

    ui->lblMinThresh->setText(QString::number(value));

    if (value > ui->sldMaxThresh->value())
    {
        ui->lblMaxThresh->setText(QString::number(value + 1));
        ui->sldMaxThresh->setValue(value + 1);
    }

    on_btnCannyApply_clicked();
}

void MainWindow::on_sldMaxThresh_valueChanged(int value)
{
    if (!loaded)
    {
        return;
    }

    ui->lblMaxThresh->setText(QString::number(value));

    if (value < ui->sldMinThresh->value())
    {
        ui->lblMinThresh->setText(QString::number(value - 1));
        ui->sldMinThresh->setValue(value - 1);
    }

    on_btnCannyApply_clicked();
}

void MainWindow::on_sldThresh_valueChanged(int value)
{
    if (!loaded)
    {
        return;
    }

    ui->lblThresh->setText(QString::number(value));
    on_btnHoughApply_clicked();
}

void MainWindow::on_actRestore_triggered()
{
    if (!loaded)
    {
        return;
    }

    ui->imageView->setImage(image);
}

void MainWindow::on_btnGaussApply_clicked()
{
    if (!loaded)
    {
        return;
    }

    Image work = ImageConverter::QImageToImage(image);
    GaussianBlur gauss(ui->lblSigma->text().toDouble(),
                       ui->lblKernel->text().toInt());
    gauss.process(work);
    auto temp = ImageConverter::ImageToQImage(work);
    ui->imageView->setImage(temp);
    state = 0;
}


void MainWindow::on_btnCannyApply_clicked()
{
    if (!loaded)
    {
        return;
    }

    Image work = ImageConverter::QImageToImage(image);
    GaussianBlur gauss(ui->lblSigma->text().toDouble(),
                       ui->lblKernel->text().toInt());
    CannyEdgeDetector canny(ui->lblMinThresh->text().toInt(),
                            ui->lblMaxThresh->text().toInt());
    gauss.process(work);
    canny.process(work);
    auto temp = ImageConverter::ImageToQImage(work);
    ui->imageView->setImage(temp);
    state = 1;
}

void MainWindow::on_btnHoughApply_clicked()
{
    if (!loaded)
    {
        return;
    }

    Image work = ImageConverter::QImageToImage(image);
    GaussianBlur gauss(ui->lblSigma->text().toDouble(),
                       ui->lblKernel->text().toInt());
    CannyEdgeDetector canny(ui->lblMinThresh->text().toInt(),
                            ui->lblMaxThresh->text().toInt());
    HoughTransform hough(ui->lblThresh->text().toInt());
    gauss.process(work);
    canny.process(work);
    hough.process(work);
    auto temp = ImageConverter::ImageToQImage(work);
    ui->imageView->setImage(temp);
}

void MainWindow::on_rbnStandard_toggled(bool checked)
{
    if (!loaded)
    {
        return;
    }

    ui->edtH->setEnabled(checked);
    ui->edtR->setEnabled(checked);
    ui->edtScale->setEnabled(!checked);
}

void MainWindow::on_rbnDiag_toggled(bool checked)
{
    if (!loaded)
    {
        return;
    }

    ui->edtH->setEnabled(!checked);
    ui->edtR->setEnabled(!checked);
    ui->edtScale->setEnabled(checked);
}

void MainWindow::on_actAnimation_triggered()
{
    w.show();
}
