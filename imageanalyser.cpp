#include "imageanalyser.h"
#include <math.h>
#include <QDebug>


ImageAnalyser::ImageAnalyser(QObject *parent)
   : QObject(parent)
{
}

double ImageAnalyser::compareImage(QImage *drawnImg, QImage *orgImg)
{
    return correlation(drawnImg, orgImg);
}

double ImageAnalyser::correlation(QImage *drawnImg, QImage *orgImg)
{
    int q,p;
    long int Ex =0, Ey =0,Ex2sum =0, Ey2sum =0, Exm = 0, Eym = 0,Exysum = 0;


        for(p= 0; p<orgImg->width();p++){
            for(q= 0; q<orgImg->height();q++){

                Exm += qGray(orgImg->pixel(p,q));
                Eym += qGray(drawnImg->pixel(p,q));
            }
        }
        Exm = Exm/(orgImg->height()*orgImg->width());
        Eym = Eym/(drawnImg->height()*drawnImg->width());


        qDebug() << "Exm " << Exm;
        qDebug() << "Eym " << Eym;
        for(p= 0; p<orgImg->width();p++){
            for(q= 0; q<orgImg->height();q++){

                Ex =  qGray(orgImg->pixel(p, q)) - Exm;
                Ey =  qGray(drawnImg->pixel(p, q)) - Eym;
                Ex2sum +=(Ex*Ex);
                Ey2sum +=(Ey*Ey);
                Exysum += Ex*Ey;
            }
        }

        qDebug() << "Ex2sum " << Ex2sum ;
        qDebug() << "Ey2sum " << Ey2sum ;

        qDebug() << "Ex2sum " << sqrt((double)Ex2sum) ;
        qDebug() << "Ey2sum " << sqrt((double)Ey2sum) ;
    //    float r = Exysum/((double)sqrt((double)Ex2sum) * (double)sqrt((double)Ey2sum));
       double r = Exysum/(sqrt((double)Ex2sum) * (double)sqrt((double)Ey2sum));
        qDebug() << "Correlation" << r;

        return r;
}

