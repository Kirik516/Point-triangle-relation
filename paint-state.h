#ifndef PAINTSTATE_H
#define PAINTSTATE_H

#include <QPainter>
#include <QSharedPointer>
#include <QVector>

#include <paint-opetations/paint-operation.h>

class PaintState
{
    using PaintStateP = QSharedPointer<PaintState>;
    using PaintOpP = QSharedPointer<PaintOperation>;
    QVector<PaintOpP> stateOperations;
    PaintStateP next;

public:
    PaintState() {}
    PaintState(PaintStateP next) : next(next) {}
    inline PaintStateP nextState() {return this->next;}
    void addPaintOperation(PaintOpP op);
    inline void setNext(PaintStateP next) {this->next = next;}
    void paint(QPainter &p);
};

#endif // PAINTSTATE_H
