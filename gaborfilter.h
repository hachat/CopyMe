#ifndef GABORFILTER_H
#define GABORFILTER_H

#include <QWidget>

class GaborFilter : public QWidget
{
    Q_OBJECT
public:
    explicit GaborFilter(QWidget *parent = 0);
    void    initialize( int y, int x, float a, float f, float s, float p = 0 );
    QImage* applyFilter(QImage* source);

    inline float 	getReal( int x, int y ) { return mReal[x][y]; }
    inline float 	getImaginary( int x, int y ) { return mImaginary[x][y]; }

    int			mYO;			// vertical origin
    int			mXO;			// horizontal origin
    int			mSizeY;			// vertical size of filter
    int			mSizeX;			// horizontal size of filter
    float		mSigma;			// curve of gaussian (sually set to PI)
    float		mAngle;			// orientation of filter (theta)
    float		mPhase;			// phase of filter (rho)
    float		mFrequency;		// wavelengths of filter (omega)
    float**		mReal;			// real part of filter
    float**		mImaginary;		// imaginary part of filter

signals:

public slots:

};

#endif // GABORFILTER_H
