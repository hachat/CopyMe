#ifndef IMAGEANALYSER_H
#define IMAGEANALYSER_H

#include <QImage>

class ImageAnalyser: public QObject
{
    Q_OBJECT
public:
    ImageAnalyser(QObject *parent = 0);
    double compareImage(QImage *drawnImg, QImage *orgImg);
    double correlation(QImage *drawnImg, QImage *orgImg);
};

#endif // IMAGEANALYSER_H
