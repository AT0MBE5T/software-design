#include "paintscene.h"
#include "romb.h"
#include "triangle.h"
#include "square.h"
#include "rectangle.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent), m_typeFigure(FigureTypes::RectangleType){}

PaintScene::~PaintScene()
{
    this->tempFigure=nullptr;
    for(auto&i:this->figures) delete i;
}

int PaintScene::typeFigure() const
{
    return this->m_typeFigure;
}

void PaintScene::setTypeFigure(const int type)
{
    this->m_typeFigure = type;
}

void PaintScene::setFigure(QGraphicsSceneMouseEvent *event)
{
    this->figures.last()->setPos(event->pos());
    this->tempFigure = this->figures.last();
    this->addItem(this->tempFigure);
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->tempFigure->setEndPoint(event->scenePos());
    this->update(QRectF(0,0,this->width(), this->height()));
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->m_typeFigure) {
        case SquareType: this->figures.push_back(new Square(event->scenePos())); break;
        case RombType: this->figures.push_back(new Romb(event->scenePos())); break;
        case TriangleType: this->figures.push_back(new Triangle(event->scenePos())); break;
        default: this->figures.push_back(new Rectangle(event->scenePos()));
    }
    setFigure(event);
}
