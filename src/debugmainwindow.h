#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <QResizeEvent>

#include "algorithm/edgedetector/cannyedgedetector.h"
#include "algorithm/linetransform/houghtransform.h"
#include "algorithm/blur/gaussianblur.h"
#include "algorithm/cylindersizecalculator.h"
#include "animation/scene.h"
#include "animation/renderer.h"

namespace Ui
{
class DebugMainWindow;
}

class DebugMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DebugMainWindow(QWidget *parent = 0);
    ~DebugMainWindow();

protected:
    void resizeEvent(QResizeEvent *);

private slots:
    void on_actOpenImage_triggered();

    void on_btnCalibrate_clicked();

    void on_btnEval_clicked();

    void on_sldSigma_valueChanged(int value);

    void on_sldKernelSize_valueChanged(int value);

    void on_sldMinThresh_valueChanged(int value);

    void on_sldMaxThresh_valueChanged(int value);

    void on_sldThresh_valueChanged(int value);

    void on_actRestore_triggered();

    void on_btnGaussApply_clicked();

    void on_btnCannyApply_clicked();

    void on_btnHoughApply_clicked();

    void on_rbnStandard_toggled(bool checked);

    void on_rbnDiag_toggled(bool checked);

private:
    void openFile();
    bool loadFile(const QString &filename);
    void setImage(const QImage &newImage);
    void initFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode);
    void fitToWindow();
    void updateActions();

    void debug_setScene();

    Ui::DebugMainWindow *ui;
    QImage image;

    CylinderSizeCalculator calc;

    int state;
};

#endif // MAINWINDOW_H