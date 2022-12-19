#ifndef PAINTOPERATION_H
#define PAINTOPERATION_H

#include <QPainter>

/*!
 * \brief The PaintOperation class of paint operation for QPainter.
 */
class PaintOperation
{
public:
    virtual ~PaintOperation() = default;
    virtual void paint(QPainter &p) = 0;
};

#endif // PAINTOPERATION_H
