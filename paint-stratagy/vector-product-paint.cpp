#include "vector-product-paint.h"

bool VectorProductPaint::isPointInside(QPoint &inspectPoint, QLine &triangleEdge)
{
    int zCoef;

    QPoint pointVector(inspectPoint.x() - triangleEdge.x1(),
                       inspectPoint.y() - triangleEdge.y1());
    QPoint edgeVector(triangleEdge.x2() - triangleEdge.x1(),
                      triangleEdge.y2() - triangleEdge.y1());
    zCoef = pointVector.x() * edgeVector.y() - pointVector.y() * edgeVector.x();

    // zCoef < 0 - insside
    // zCoef > 0 - outside
    return zCoef < 0;
}

VectorProductPaint::VectorProductPaint(QPolygon &polygon,
                                       const QPen &pointPen,
                                       const QColor &lineHighlight,
                                       const QColor &lineTrace,
                                       const QColor &insideColor,
                                       const QColor &outsideColor)
    : polygon(polygon)
{
    using PaintPolyP = QSharedPointer<PaintPolygon>;
    using PaintPointP = QSharedPointer<PaintCheckPoint>;
    using PaintLineP = QSharedPointer<PaintLine>;
    using StateP = QSharedPointer<PaintState>;

    PaintPolyP polyOp = PaintPolyP::create(QPen(Qt::black), &this->polygon);
    PaintPointP pointOp = PaintPointP::create(pointPen, &this->currentPoint);
    this->pointResultOp = PaintPointP::create(pointPen, &this->currentPoint);
    QPen insidePen(pointPen);
    QPen outsidePen(pointPen);
    insidePen.setColor(insideColor);
    outsidePen.setColor(outsideColor);
    this->pointInsideOp = PaintPointP::create(insidePen, &this->currentPoint);
    this->pointOutsideOp = PaintPointP::create(outsidePen, &this->currentPoint);

    StateP start = StateP::create();
    start->addPaintOperation(polyOp);
    StateP pointSt = StateP::create();
    pointSt->addPaintOperation(polyOp);
    pointSt->addPaintOperation(pointOp);

    QVector<StateP> states;
    int sizePoly = this->polygon.size();
    states.reserve(sizePoly);
    for (int i = 0; i < sizePoly; i++)
    {
        StateP lineToPoint = StateP::create();
        lineToPoint->addPaintOperation(polyOp);
        lineToPoint->addPaintOperation(pointOp);
        PaintLineP highLOp = PaintLineP::create(lineHighlight, &this->polygon[i], &this->polygon[(i + 1)%sizePoly]);
        lineToPoint->addPaintOperation(highLOp);

        StateP productResult = StateP::create();
        productResult->addPaintOperation(polyOp);
        productResult->addPaintOperation(pointOp);
        productResult->addPaintOperation(highLOp);
        PaintLineP lineToPOp = PaintLineP::create(lineTrace, &this->polygon[i], &this->currentPoint);
        productResult->addPaintOperation(lineToPOp);

        states << lineToPoint << productResult;
    }
    StateP idle = StateP::create();
    idle->addPaintOperation(polyOp);
    idle->addPaintOperation(this->pointResultOp);


    start->setNext(pointSt);
    pointSt->setNext(states.first());
    int size = states.size() - 1;
    for (int i = 0; i < size; i++)
    {
        states[i]->setNext(states[i + 1]);
    }
    states.last()->setNext(idle);
    idle->setNext(idle);

    this->startState = start;
    this->currentState = start;
}

void VectorProductPaint::draw(QPainter &painter)
{
    painter.save();

    this->currentState->paint(painter);

    painter.restore();
}

void VectorProductPaint::forward()
{
    this->currentState = this->currentState->nextState();
}

void VectorProductPaint::setInespectPoint(const QPoint &inspectPoint)
{
    this->currentPoint = inspectPoint;
    bool isInside = true;
    int sizePoly = polygon.size();
    for (int i = 0; i < sizePoly; i++)
    {
        QLine edge(polygon[i], polygon[(i + 1)%sizePoly]);
        isInside = isInside && this->isPointInside(this->currentPoint, edge);
    }
    if (isInside == true)
    {
        *(this->pointResultOp) = *(this->pointInsideOp);
    }
    else
    {
        *(this->pointResultOp) = *(this->pointOutsideOp);
    }
}
