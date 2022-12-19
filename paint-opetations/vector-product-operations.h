#ifndef VECTORPRODUCTOPERATIONS_H
#define VECTORPRODUCTOPERATIONS_H

#include "paint-operation.h"

// paint operations for vector product calculation visualisation

class PaintPolygon : public PaintOperation
{
    QPen pen;
    QPolygon *poly;

public:
    inline PaintPolygon(const QPen &pen, QPolygon *poly)
                                                    : pen(pen), poly(poly) {}
    inline void paint(QPainter &p) override {p.setPen(this->pen);
                                             p.drawPolygon(*this->poly);}
};

class PaintCheckPoint : public PaintOperation
{
    QPen pen;
    QPoint *point;

public:
    inline PaintCheckPoint(const QPen &pen, QPoint *point)
                                                    : pen(pen), point(point) {}
    inline void paint(QPainter &p) override {p.setPen(this->pen);
                                             p.drawPoint(*this->point);}
};

class PaintLine : public PaintOperation
{
    QPen pen;
    QPoint *point1;
    QPoint *point2;

public:
    inline PaintLine(const QPen &pen, QPoint *point1, QPoint *point2)
                                : pen(pen), point1(point1), point2(point2) {}
    inline void paint(QPainter &p) override {p.setPen(this->pen);
                                             p.drawLine(*point1, *point2);}
};

#endif // VECTORPRODUCTOPERATIONS_H
