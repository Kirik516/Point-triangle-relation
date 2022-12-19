#ifndef VECTORPRODUCTPAINT_H
#define VECTORPRODUCTPAINT_H

#include "paint-stratagy.h"
#include "paint-state.h"
#include "paint-opetations/vector-product-operations.h"

/*!
 * \brief The VectorProductPaint class is the PaintStratagy realization for vector
 *vector product based calculation.
 */
class VectorProductPaint : public PaintStratagy
{
    // Draw plan
    // Draw tiangle every time
    // After mouse click draw point every time
    // -- Ctart calcukatoin visualisation --
    // Select triangle edge and hightlight it with color
    // Draw line from first vertex of selected edge to point
    // Draw result of vector prodution
    // Mark selected edge according to calculation result
    QPoint currentPoint;
    QPolygon &polygon;

    QSharedPointer<PaintCheckPoint> pointResultOp;
    QSharedPointer<PaintCheckPoint> pointInsideOp;
    QSharedPointer<PaintCheckPoint> pointOutsideOp;
    QSharedPointer<PaintState> startState;
    QSharedPointer<PaintState> currentState;

    bool isPointInside(QPoint &inspectPoint, QLine &triangleEdge);

public:
    VectorProductPaint(QPolygon &polygon,
                       const QPen &pointPen = QPen(Qt::black),
                       const QColor &lineHighlight = QColor(Qt::yellow),
                       const QColor &lineTrace = QColor(Qt::green),
                       const QColor &insideColor = QColor(Qt::blue),
                       const QColor &outsideColor = QColor(Qt::red));
    void draw(QPainter &painter) override;
    void forward() override;
    inline bool isDone() override
                 {return this->currentState == this->currentState->nextState();}
    inline void reset() override {this->currentState = startState;}
    void setInespectPoint(const QPoint &inspectPoint) override;
};

#endif // VECTORPRODUCTPAINT_H
