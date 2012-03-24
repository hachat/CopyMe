#ifndef DRAWAREA_H
#define DRAWAREA_H


#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <qmath.h>

class DrawArea : public QWidget
{
    Q_OBJECT
public:
    DrawArea(int width, int height, QWidget *parent = 0);

    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat = 0);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);

    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }
    QImage* getImage();
    void clearImage();
    QPoint snapPoint(QPoint pnt,bool doSnap = true);

public slots:

    void print();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);


private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified;
    bool scribbling;
    bool straightLine;
    int myPenWidth;
    QColor myPenColor;
    QImage *image;
    QPoint lastPoint;
	QPoint tmpPoint;
    double gridSnap;
    bool initClick;
    bool finClick;

};

#endif // DRAWAREA_H
