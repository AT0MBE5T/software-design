#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "figure.h"

class PaintScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(int typeFigure
               READ typeFigure WRITE setTypeFigure
               NOTIFY typeFigureChanged)

public:
    explicit PaintScene(QObject *parent = 0);
    ~PaintScene();

    int typeFigure() const;
    void setTypeFigure(const int type);
    void setFigure(QGraphicsSceneMouseEvent *event);

    enum FigureTypes {
        SquareType,
        RombType,
        TriangleType,
        RectangleType
    };

signals:
    void typeFigureChanged();

private:
    Figure *tempFigure;
    int m_typeFigure;
    QVector<Figure*> figures;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};

#endif
