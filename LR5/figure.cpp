#include "figure.h"
#include <QPainter>

Figure::Figure(const QPointF& point, QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    this->setStartPoint(mapFromScene(point));
    this->setEndPoint(mapFromScene(point));
    connect(this, &Figure::pointChanged, this, &Figure::updateFigure);
}

Figure::~Figure() {}

QRectF Figure::boundingRect() const
{
    return QRectF((this->endPoint().x() > this->startPoint().x() ? this->startPoint().x() : this->endPoint().x()) - 5,
                  (this->endPoint().y() > this->startPoint().y() ? this->startPoint().y() : this->endPoint().y()) - 5,
                  qAbs(this->endPoint().x() - this->startPoint().x()) + 10,
                  qAbs(this->endPoint().y() - this->startPoint().y()) + 10);
}

void Figure::updateFigure()
{
    this->update((this->endPoint().x() > this->startPoint().x() ? this->startPoint().x() : this->endPoint().x()) - 5,
                 (this->endPoint().y() > this->startPoint().y() ? this->startPoint().y() : this->endPoint().y()) - 5,
                 qAbs(this->endPoint().x() - this->startPoint().x()) + 10,
                 qAbs(this->endPoint().y() - this->startPoint().y()) + 10);
}

void Figure::setStartPoint(const QPointF& point)
{
    this->m_startPoint = mapFromScene(point);
    emit pointChanged();
}

void Figure::setEndPoint(const QPointF& point)
{
    this->m_endPoint = mapFromScene(point);
    emit this->pointChanged();
}

QPointF Figure::startPoint() const
{
    return this->m_startPoint;
}

QPointF Figure::endPoint() const
{
    return this->m_endPoint;
}
