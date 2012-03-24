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

    drawnImgPtr = drawArea->getImage();
    drawGrid(drawnImgPtr);
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
         drawGrid(&orgImage);

         label->setPixmap(QPixmap::fromImage(orgImage));


    }

}

void MainWindow::on_actionClear_triggered()
{
    drawArea->clearImage();
    drawGrid(drawnImgPtr);
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


void MainWindow::drawGrid(QImage *img)
{
    int widthGrid = img->width()/3;
    int heightGrid = img->height()/3;

    int heightGrid2 = heightGrid *2;
    int widthGrid2 = widthGrid *2;
    for(int x = 0; x < img->width(); x++){
        img->setPixel(x, heightGrid, qRgb(200,200,200));
        img->setPixel(x, heightGrid2, qRgb(200,200,200));
    }
    for(int y = 0; y < img->width(); y++){
        img->setPixel(widthGrid, y, qRgb(200,200,200));
        img->setPixel(widthGrid2, y, qRgb(200,200,200));
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



