#include "widget.h"

void Widget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    p.setRenderHint(QPainter::Antialiasing, true);
    this->algo->draw(p);
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "Grab point";
    this->algo->setInespectPoint(event->pos());
    this->algo->reset();
    this->algo->forward();
    this->update();
    this->timer.start();
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->timer.setInterval(1000);
    this->timer.setSingleShot(false);
    connect(&this->timer, &QTimer::timeout, this, &Widget::timerTick);
}

void Widget::setDrawAlgo(QSharedPointer<PaintStratagy> algo)
{
    this->algo = algo;
}

void Widget::timerTick()
{
    qDebug() << "tick";
    this->algo->forward();
    if (this->algo->isDone())
    {
        this->timer.stop();
    }
    this->update();
}
