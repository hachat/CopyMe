#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "drawarea.h"
#include "imageanalyser.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void drawGrid(QImage *img);
    ~MainWindow();
protected:
    void resizeEvent(QResizeEvent *event);
private:
    QWidget *centralWidget;
    Ui::MainWindow *ui;
    QPushButton *compareButton;
    QVBoxLayout *vbox;
    QHBoxLayout *hbox;
    QWidget *messageWidget;
    QString PRGRM_NAME;

    DrawArea *drawArea;
    QLabel *label;
    ImageAnalyser *imageAnalyser;
    QString filepath;
    QImage orgImage;
    QImage *drawnImgPtr;
    int WIDTH, HEIGHT;

private slots:
    void compareImage();
    void on_actionLoad_Image_triggered();
    void on_actionClear_triggered();
    void on_actionSave_triggered();
    void on_actionCompare_triggered();
    void on_actionSave_2_triggered();
    void on_actionLoad_Image_2_triggered();
    void on_actionClear_2_triggered();
};

#endif // MAINWINDOW_H
