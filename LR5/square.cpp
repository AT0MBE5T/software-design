#include "square.h"
#include <QPainter>

Square::Square(const QPointF& point, QObject *parent) :
    Figure(point,parent)
{
    Q_UNUSED(point)
}

Square::~Square() {}

void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 2));
    int x = endPoint().x() > startPoint().x() ? startPoint().x() : endPoint().x();
    int y = endPoint().y() > startPoint().y() ? startPoint().y() : endPoint().y();
    int size = std::min(endPoint().x() - startPoint().x(), endPoint().y() - startPoint().y());
    QRectF rect(x, y, qAbs(size), qAbs(size));
    painter->drawRect(rect);
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

