#ifndef WIDGET_H
#define WIDGET_H

#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

    enum DrawState {};

    bool isInside;
    QPoint pinPoint;
    QPolygon triangle;

    virtual void paintEvent(QPaintEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    bool isPointInside(QPoint &p);
    bool vectorProdAlgorithm(QPoint &p);

public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H
