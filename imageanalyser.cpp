#include "imageanalyser.h"
#include <math.h>
#include <QDebug>


ImageAnalyser::ImageAnalyser(QObject *parent)
   : QObject(parent)
{
}

double ImageAnalyser::compareImage(QImage *drawnImg, QImage *orgImg)
{
    return correlation(drawnImg, orgImg,20,-20);
    //return correlation(drawnImg, orgImg);
}

/**
  This is the basic correlation function
  */
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
        double r = Exysum/(sqrt((double)Ex2sum) * (double)sqrt((double)Ey2sum));
        qDebug() << "Correlation" << r;

        return r;
}

double ImageAnalyser::correlation(QImage *drawnImg, QImage *orgImg,int offsetX,int offsetY){


    //Check for conditions offests are larger than image dimentions

    int q,p;
    long int Ex =0, Ey =0,Ex2sum =0, Ey2sum =0, Exm = 0, Eym = 0,Exysum = 0;

        //Calculating the mean of each image
        for(p= 0; p<orgImg->width();p++){
            for(q= 0; q<orgImg->height();q++){

                /**
                  This is to avoid margins
                  Draw it in a papaer, so u'll figure out what it is.
                  */
                if(offsetX<0 && p >= orgImg->width()+offsetX || \
                        offsetY<0 && q >= orgImg->height()+offsetY || \
                        offsetX>0 && p <= offsetX || \
                        offsetY>0 && q <= offsetY)
                {
                    continue;
                }
                else
                {

                    Eym += qGray(drawnImg->pixel(p-offsetX,q-offsetY));
                    Exm += qGray(orgImg->pixel(p,q));
                }
            }
        }

        qDebug() << "ExmSum " << Exm;
        qDebug() << "EymSum " << Eym;

        Exm = Exm/(orgImg->height()*orgImg->width());
        Eym = Eym/(drawnImg->height()*drawnImg->width());
        /**
            This is not exactly correct, which includes all pixels
            But it will be enough as those will be equal over each offset
          */

        qDebug() << "Exm " << Exm;
        qDebug() << "Eym " << Eym;


        for(p= 0; p<orgImg->width();p++){
            for(q= 0; q<orgImg->height();q++){


                if(offsetX<0 && p >= orgImg->width()+offsetX || \
                        offsetY<0 && q >= orgImg->height()+offsetY || \
                        offsetX>0 && p <= offsetX || \
                        offsetY>0 && q <= offsetY)
                {
                    continue;
                }
                else
                {
                    Ex =  qGray(orgImg->pixel(p, q)) - Exm;
                    Ey =  qGray(drawnImg->pixel(p-offsetX, q-offsetY)) - Eym;
                    Ex2sum +=(Ex*Ex);
                    Ey2sum +=(Ey*Ey);
                    Exysum += Ex*Ey;
                    //orgImg->setPixel(p,q,qRgb(50,0,0)+orgImg->pixel(p,q));
                    //drawnImg->setPixel(p-offsetX, q-offsetY,qRgb(255,255,0));
                }
            }
        }


        qDebug() << "Ex2sum " << Ex2sum ;
        qDebug() << "Ey2sum " << Ey2sum ;

        qDebug() << "Ex2sum " << sqrt((double)Ex2sum) ;
        qDebug() << "Ey2sum " << sqrt((double)Ey2sum) ;
        double r = Exysum/(sqrt((double)Ex2sum) * (double)sqrt((double)Ey2sum));
        qDebug() << "Correlation" << r;

        return r;

}
