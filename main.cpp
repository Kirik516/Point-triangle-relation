#include "widget.h"
#include "paint-stratagy/vector-product-paint.h"

#include <QApplication>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>

using VectProdP = QSharedPointer<VectorProductPaint>;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // clockwise point set
    QPolygon triangle;
    triangle << QPoint(150, 150) << QPoint(300, 190) << QPoint(180, 330);

    Widget *drawWidget = new Widget;
    drawWidget->setStyleSheet("background-color: gray;");

    // init paint algorithm ----------------------------------------------------
    QPen pointPen;
    pointPen.setColor(Qt::black);
    pointPen.setWidth(4);
    pointPen.setCapStyle(Qt::RoundCap);
    VectProdP algo = VectProdP::create(triangle,
                                       pointPen,
                                       QColor("lemonchiffon"),
                                       QColor("indianred"),
                                       QColor("dodgerblue"),
                                       QColor("salmon"));
    drawWidget->setDrawAlgo(algo);
    // -------------------------------------------------------------------------

    // interface - layout ------------------------------------------------------
    QWidget w;
    w.resize(600, 480);

    QRadioButton *vectorProduct =
                               new QRadioButton("Vector prodact algorithm", &w);
    vectorProduct->setChecked(true);
    QRadioButton *lineCross = new QRadioButton("Line cross algorithm", &w);
    lineCross->setDisabled(true);
    lineCross->setToolTip("Coming soon");
    QPushButton *exitPush = new QPushButton("Exit", &w);
    QObject::connect(exitPush, &QPushButton::clicked, [&a]() {a.exit();});

    QButtonGroup *buttonGruop = new QButtonGroup(&w);
    buttonGruop->setExclusive(true);
    buttonGruop->addButton(vectorProduct);
    buttonGruop->addButton(lineCross);

    QVBoxLayout *radioLayout = new QVBoxLayout;
    radioLayout->addWidget(vectorProduct);
    radioLayout->addWidget(lineCross);
    radioLayout->addStretch(1);
    radioLayout->addWidget(exitPush);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(drawWidget, 1);
    mainLayout->addLayout(radioLayout, 0);

    w.setLayout(mainLayout);
    w.show();
    // -------------------------------------------------------------------------

    return a.exec();
}
