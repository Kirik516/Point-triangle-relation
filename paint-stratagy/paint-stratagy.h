#ifndef PAINTSTRATAGY_H
#define PAINTSTRATAGY_H

#include <QPainter>

/*!
 * \brief The PaintStratagy class base class for paint staratagies
 *(mothods of drawing).
 */
class PaintStratagy
{
public:
    virtual ~PaintStratagy() {}
    virtual void draw(QPainter &painter) = 0;
    virtual void forward() = 0;
    virtual bool isDone() = 0;
    virtual void reset() = 0;
    virtual void setInespectPoint(const QPoint &inspectPoint) = 0;
};

#endif // PAINTSTRATAGY_H
