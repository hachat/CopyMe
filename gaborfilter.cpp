#include "gaborfilter.h"
#include <qmath.h>

GaborFilter::GaborFilter(QWidget *parent) :
    QWidget(parent)
{
    mSizeY = 16;
    mSizeX = 16;
    mSigma = M_PI;
    mAngle = 0;
    mPhase = 0;
    mFrequency = 1.0;
}

// set up the filter
void GaborFilter::initialize( int sizey, int sizex, float a, float f, float s, float p )
{
        float x, y, exponential, sincos;

// set internal variables
        mSizeY = sizey;
        mSizeX = sizex;
        mSigma = s;
        mAngle = a;
        mPhase = p;
        mFrequency = f * M_PI / 2.0;

// find origin of filter
        mYO = mSizeY / 2;
        mXO = mSizeX / 2;

// allocate memory for filter
        mReal 	   = new float*[mSizeY];		// real part of filter
        mImaginary = new float*[mSizeY];		// imaginary part of filter

// initialize filter values
        for ( int i = 0; i < mSizeY; i++ )
        {
                mReal[i] 	  = new float[mSizeX];
                mImaginary[i] = new float[mSizeX];

                for ( int j = 0; j < mSizeX; j++ )
                {
                // offset from origin
                        y = (float)( i - mYO );
                        x = (float)( j - mXO );
                // calculate exponential part
                        exponential = exp( - ( x*x + y*y ) / mSigma );
                // calculate sin-cos sum
                        sincos = mFrequency * ( y * cos( mAngle ) - x * sin( mAngle ) );
                        mReal[i][j] 	 = exponential * sin( sincos );
                        mImaginary[i][j] = exponential * ( cos( sincos ) - exp((-1.0*M_PI*M_PI)/2.0) );
                }
        }
}

QImage* GaborFilter::applyFilter(QImage *source)
{



    QImage* resultImg = new QImage(source->width(),source->height(),QImage::Format_ARGB32);

    int i=0,j=0,p=0,q=0;
    float sum = 0;
    for(i=0;i<source->height();i++){
        for(j=0;j<source->width();j++){

            if((i<mSizeY || i>(source->height()-1)-mSizeY)|| (j<mSizeX || j>(source->width()-1)-mSizeX))
            {
                continue;
            }

            sum = 0;
            for(p=i-mSizeY;p<i+mSizeY;p++){
                for(q=i-mSizeX;q<i+mSizeX;q++){

                    sum += qGray(resultImg->pixel(p,q)) * this->getReal(p,q);
                }
            }

            resultImg->setPixel(i,j,qFloor(sum/(mSizeX*mSizeY)));
        }
    }

    return source;
}
