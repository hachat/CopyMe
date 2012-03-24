#ifndef IMAGEANALYSER_H
#define IMAGEANALYSER_H

#include <QImage>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define SELF 4

class ImageAnalyser: public QObject
{
    Q_OBJECT
public:
    ImageAnalyser(QObject *parent = 0);
    double  compareImage(QImage *drawnImg, QImage *orgImg);
    double  correlation(QImage *drawnImg, QImage *orgImg);
    double  correlation(QImage *drawnImg, QImage *orgImg,int offsetX,int offsetY);
    double  optimizedCorrelation(QImage *drawnImg, QImage *orgImg,int steps);
    int     optimize(QImage *drawnImg, QImage *orgImg,int offsetX,int offsetY);
};

#endif // IMAGEANALYSER_H
