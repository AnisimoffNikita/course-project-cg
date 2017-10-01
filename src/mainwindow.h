#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actOpenImage_triggered();

    void on_actFit_triggered();

private:
    void openFile();
    bool loadFile(const QString &filename);
    void setImage(const QImage &newImage);
    void initFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode);
    void fitToWindow();
    void updateActions();

    float scaleFactor;
    QImage image;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
