#ifndef LINECROSSPAINT_H
#define LINECROSSPAINT_H

#include "paint-stratagy.h"

// Ax + By + C = 0
// A1x + B1y + C1 = A2x + B2y + C2
// A1 B1
// A2 B2
// A1*B2 - A2*B1
//
//example
//    int edgeCrossCount = 0;
//    int dim;
//    QPoint traceNorm(0, 0 - p.y());
//    int size = this->triangle.size();
//    for(int i = 0; i < size; i++)
//    {
//        QPoint edgeNorm(this->triangle[i].y() - this->triangle[(i + 1)%size].y(),
//                        this->triangle[(i + 1)%size].x() - this->triangle[i].x());
//        dim = traceNorm.x() * edgeNorm.y() - edgeNorm.x() * traceNorm.y();
//        edgeCrossCount += (dim < 0);
//    }
//    if (edgeCrossCount == 0 || edgeCrossCount%2 != 0)
//    {
//        return false;
//    }
//    return true;
//    QPoint traceNorm(0, 0 - inspectPoint.y());
//
class LineCrossPaint : public PaintStratagy
{
public:
    LineCrossPaint(QPolygon &triangle);
    void draw(QPainter &painter) override {}
    void forward() override {}
    bool isDone() override {return true;}
    void reset() override {}
    void setInespectPoint(const QPoint &inspectPoint) override {}
};

#endif // LINECROSSPAINT_H
