#include "widget.h"

void Widget::paintEvent(QPaintEvent *)
{
    QVector<QPen> penForPoint = QVector<QPen>(2);
    penForPoint[0] = QPen(Qt::red);
    penForPoint[0].setWidth(3);
    penForPoint[1] = QPen(Qt::blue);
    penForPoint[1].setWidth(3);

    QPainter p(this);
    p.setPen(QPen(Qt::black));

    int size = this->triangle.size();
    for(int i = 0; i < size; i++)
    {
        p.drawLine(this->triangle[i], this->triangle[(i + 1)%size]);
    }

    if (this->pinPoint.x() > -1)
    {
        p.setPen(penForPoint[this->isInside]);
        p.drawPoint(this->pinPoint);
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    this->pinPoint = event->pos();
    this->isInside = this->isPointInside(this->pinPoint);
    this->update();
}

bool Widget::isPointInside(QPoint &p)
{
    return vectorProdAlgorithm(p);
}

// Ax + By + C = 0
// A1x + B1y + C1 = A2x + B2y + C2
// A1 B1
// A2 B2
// A1*B2 - A2*B1
bool Widget::isPointInside(QPoint &p)
{
    int edgeCrossCount = 0;
    int dis;
    QPoint traceNorm(0, 0 - p.y());
    int size = this->triangle.size();
    for(int i = 0; i < size; i++)
    {
        QPoint edgeNorm(this->triangle[i].y() - this->triangle[(i + 1)%size].y(),
                        this->triangle[(i + 1)%size].x() - this->triangle[i].x());
        dis = traceNorm.x() * edgeNorm.y() - edgeNorm.x() * traceNorm.y();
        edgeCrossCount += (dis != 0);
    }
    if (edgeCrossCount == 0 || edgeCrossCount%2 == 0)
    {
        return false;
    }
    return true;
}

// i  j   k
// 33 -14 0
// 150 40 0
// 33 * 40 - 150 * 40 = 1320 - 6000 = -4680
bool Widget::vectorProdAlgorithm(QPoint &p)
{
    int rightTripleCount = 0;
    int z;
    int size = this->triangle.size();
    for(int i = 0; i < size; i++)
    {
        QPoint pointVector(p.x() - this->triangle[i].x(), p.y() - this->triangle[i].y());
        QPoint edgeVector(this->triangle[(i + 1)%size].x() - this->triangle[i].x(),
                        this->triangle[(i + 1)%size].y() - this->triangle[i].y());
        z = pointVector.x() * edgeVector.y() - pointVector.y() * edgeVector.x();
        rightTripleCount += (z < 0);
    }
    if (rightTripleCount == size)
    {
        return true;
    }
    return false;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , isInside(false)
    , pinPoint(-1, -1)
{
    this->triangle << QPoint(200, 150) << QPoint(350, 190) << QPoint(230, 330);
}

Widget::~Widget() {}
