#ifndef WIDGET_H
#define WIDGET_H

#include <QDebug>
#include <QMap>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QStyleOption>
#include <QWidget>

#include "paint-stratagy/paint-stratagy.h"

/*!
 * \brief The Widget class is the widget-manager of visualization.
 */
class Widget : public QWidget
{
    Q_OBJECT

    QTimer timer;

    QSharedPointer<PaintStratagy> algo;

    void paintEvent(QPaintEvent *) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public:
    explicit Widget(QWidget *parent = 0);
    void setDrawAlgo(QSharedPointer<PaintStratagy> algo);

private slots:
    void timerTick();
};

#endif // WIDGET_H
