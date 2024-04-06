#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QResizeEvent>
#include <QPushButton>

#include "paintscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PaintScene *scene;
    QTimer *timer;
    QVector<PaintScene::FigureTypes> figureTypes = {PaintScene::RombType, PaintScene::SquareType, PaintScene::TriangleType};

private:
    void resizeEvent(QResizeEvent * event);
    void connectButtons();

private slots:
    void slotTimer();
    void setFigure(PaintScene::FigureTypes figure);
    PaintScene::FigureTypes defineType(QPushButton*);
    void clickFigureButton();
};

#endif
