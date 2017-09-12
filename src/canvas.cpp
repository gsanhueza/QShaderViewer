#include <QApplication>
#include <QMouseEvent>
#include <QPainter>

#include "canvas.h"

Canvas::Canvas(QWidget* parent) : QWidget(parent)
{
    setMinimumSize(1100, 1100);
}

void Canvas::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    doPainting();
}

void Canvas::doPainting()
{
    QPainter painter(this);
    QPen pen(Qt::black, 2);

    pen.setStyle(Qt::SolidLine);
    pen.setBrush(Qt::blue);
    painter.setPen(pen);

    painter.drawEllipse(QPoint(768, 1100 - 703), 5, 5);
    pen.setBrush(Qt::black);
    painter.setPen(pen);
    painter.drawEllipse(QPoint(404, 1100 - 161), 5, 5);
    pen.setBrush(Qt::red);
    painter.setPen(pen);
    painter.drawEllipse(QPoint(894, 1100 - 325), 5, 5);
    painter.drawEllipse(QPoint(503, 1100 - 711), 5, 5);
    painter.drawEllipse(QPoint(711, 1100 - 410), 5, 5);
    painter.drawEllipse(QPoint(690, 1100 - 905), 5, 5);
    painter.drawEllipse(QPoint(841, 1100 -  88), 5, 5);
    painter.drawEllipse(QPoint(461, 1100 - 300), 5, 5);
}
