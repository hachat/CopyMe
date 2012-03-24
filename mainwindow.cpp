#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QFileDialog>
#include <QDesktopServices>
#include <QImage>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    WIDTH  = 400;
    HEIGHT = 400;
    drawArea = new DrawArea(WIDTH, HEIGHT, centralWidget);
    vbox = new QVBoxLayout(centralWidget);
    hbox = new QHBoxLayout();
    label = new QLabel(centralWidget);
    hbox->addWidget(drawArea);
    hbox->addWidget(label);
    vbox->addLayout(hbox);
    compareButton = new QPushButton("Compare", this);
    vbox->addWidget(compareButton);

    setWindowTitle("CopyMe");
    imageAnalyser = new ImageAnalyser(this);
    PRGRM_NAME = "CopyMe";

    connect(compareButton, SIGNAL(clicked()), this, SLOT(compareImage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::compareImage()
{
    double corelation;
    drawnImgPtr =  drawArea->getImage();
    if(!orgImage.isNull() && !drawnImgPtr->isNull()){
        corelation = imageAnalyser->compareImage(&orgImage, drawnImgPtr);
        QMessageBox::information(this, PRGRM_NAME, QString("<b> Correlation : %1 <b>").arg(corelation) );
    }
}


void MainWindow::on_actionLoad_Image_triggered()
{
    filepath =  QFileDialog::getOpenFileName(this, "Open File",
                                                       QDesktopServices::storageLocation(QDesktopServices::PicturesLocation));

    if(!filepath.isEmpty()){
         orgImage.load(filepath);
         if (orgImage.isNull()) {
             QMessageBox::information(this, PRGRM_NAME,"Cannot load image");
             return;
         }
         orgImage = orgImage.scaled(WIDTH,HEIGHT);
         label->setPixmap(QPixmap::fromImage(orgImage));

    }

}

void MainWindow::on_actionClear_triggered()
{
    drawArea->clearImage();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
//    if(!orgImage.isNull()){
//        WIDTH = drawArea->width();
//        HEIGHT = drawArea->height();
//        orgImage = orgImage.scaled(WIDTH,HEIGHT);
//        label->setPixmap(QPixmap::fromImage(orgImage));
//        QMainWindow::resizeEvent(event);
//    }
}

void MainWindow::on_actionSave_triggered()
{
    filepath = QFileDialog::getSaveFileName(this, "Save File",
                                                       QDesktopServices::storageLocation(QDesktopServices::PicturesLocation));
    if(!filepath.isEmpty()){
        drawArea->saveImage(filepath);
    }else {
        QMessageBox::information(this, PRGRM_NAME,"Cannot save image");
        return;
    }

}

void MainWindow::on_actionCompare_triggered()
{
    compareImage();
}

void MainWindow::on_actionSave_2_triggered()
{
    on_actionSave_triggered();
}

void MainWindow::on_actionLoad_Image_2_triggered()
{
    on_actionLoad_Image_triggered();
}

void MainWindow::on_actionClear_2_triggered()
{
    on_actionClear_triggered();
}
