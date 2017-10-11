#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <QResizeEvent>

#include "src/algorithm/edgedetector/cannyedgedetector.h"
#include "src/algorithm/linetransform/houghtransform.h"
#include "src/algorithm/blur/gaussianblur.h"
#include "src/algorithm/cylindersizecalculator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *);

private slots:
    void on_actOpenImage_triggered();

    void on_btnCanny_clicked();

    void on_btnHough_clicked();

    void on_btnCalibrate_clicked();

    void on_btnEval_clicked();

private:
    void openFile();
    bool loadFile(const QString &filename);
    void setImage(const QImage &newImage);
    void initFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode);
    void fitToWindow();
    void updateActions();

    Ui::MainWindow *ui;
    QImage image;

    GaussianBlur gauss;
    CannyEdgeDetector canny;
    HoughTransform hough;
    CylinderSizeCalculator calc;
};

#endif // MAINWINDOW_H
