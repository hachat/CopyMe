#include "drawarea.h"

#include <QtGui>


//! [0]
DrawArea::DrawArea(int width, int height, QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    myPenWidth = 10;
    myPenColor = Qt::black;
    image = new QImage(width, height, QImage::Format_RGB16);
    clearImage();
    straightLine = true;
    gridSnap =5.0;
    initClick = false;
    finClick = false;
	
}
//! [0]

//! [1]
bool DrawArea::openImage(const QString &fileName)
//! [1] //! [2]
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = new QImage(loadedImage);
    modified = false;
    update();
    return true;
}
//! [2]

//! [3]
bool DrawArea::saveImage(const QString &fileName, const char *fileFormat)
//! [3] //! [4]
{
    QImage visibleImage = *image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}
//! [4]

//! [5]
void DrawArea::setPenColor(const QColor &newColor)
//! [5] //! [6]
{
    myPenColor = newColor;
}
//! [6]

//! [7]
void DrawArea::setPenWidth(int newWidth)
//! [7] //! [8]
{
    myPenWidth = newWidth;
}
//! [8]

//! [9]
void DrawArea::clearImage()
//! [9] //! [10]
{
    image->fill(qRgb(255, 255, 255));
    modified = true;
    update();
}
//! [10]

//! [11]
void DrawArea::mousePressEvent(QMouseEvent *event)
//! [11] //! [12]
{
    if (event->button() == Qt::LeftButton && !initClick ) {
        lastPoint = snapPoint(event->pos());
        scribbling = true;
        initClick = true;
        drawLineTo(snapPoint(event->pos()));
    }else if(event->button() == Qt::LeftButton && initClick ){
        initClick = false;

        drawLineTo(snapPoint(event->pos()));
    }
}

void DrawArea::mouseMoveEvent(QMouseEvent *event)
{
//    if ((event->buttons() & Qt::LeftButton) && scribbling)
//        drawLineTo(event->pos());
}

void DrawArea::mouseReleaseEvent(QMouseEvent *event)
{
//    if (event->button() == Qt::LeftButton && scribbling) {
//        drawLineTo(event->pos());
//        scribbling = false;
//    }
}

//! [12] //! [13]
void DrawArea::paintEvent(QPaintEvent *event)
//! [13] //! [14]
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, *image, dirtyRect);
}
//! [14]

//! [15]
void DrawArea::resizeEvent(QResizeEvent *event)
//! [15] //! [16]
{
//    if (width() > image->width() || height() > image->height()) {
//        int newWidth = qMax(width() + 128, image->width());
//        int newHeight = qMax(height() + 128, image->height());
//        resizeImage(image, QSize(newWidth, newHeight));
//        update();
//    }

//    resizeImage(image,QSize(width(), height()));
//    QWidget::resizeEvent(event);
}
//! [16]

//! [17]
void DrawArea::drawLineTo(const QPoint &endPoint)
//! [17] //! [18]
{
    QPainter painter(image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}
//! [18]

//! [19]
void DrawArea::resizeImage(QImage *image, const QSize &newSize)
//! [19] //! [20]
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}
//! [20]

//! [21]
void DrawArea::print()
{
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);

    QPrintDialog *printDialog = new QPrintDialog(&printer, this);
//! [21] //! [22]
    if (printDialog->exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = image->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(image->rect());
        painter.drawImage(0, 0, *image);
    }
#endif // QT_NO_PRINTER
}

QImage* DrawArea::getImage()
{
    return image;
}
QPoint DrawArea::snapPoint(QPoint pnt, bool doSnap)
{
    QPoint tmpPoint;
    if(doSnap){
        tmpPoint.setX(qFloor(pnt.rx()+gridSnap));
        tmpPoint.setY(qFloor(pnt.ry()+gridSnap));
    }
    return tmpPoint;
}
