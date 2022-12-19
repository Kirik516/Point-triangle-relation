#include <paint-state.h>

void PaintState::addPaintOperation(PaintState::PaintOpP op)
{
    if (op)
    {
        this->stateOperations << op;
    }
}

void PaintState::paint(QPainter &p)
{
    int size = this->stateOperations.size();
    for (int i = 0; i < size; i++)
    {
        this->stateOperations[i]->paint(p);
    }
}
