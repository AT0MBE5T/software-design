#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , squareX(-width()/2)
    , squareY(0)
    , speed(2)
    , rotationAngle(0)
    , isLeftToRight(true)
{
    ui->setupUi(this);
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateRotate()));
    timer->start(10);
    squareWidth = 100;
    squareHeight = 100;
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::updateRotate()
{
    if(isLeftToRight){
        squareX += speed;
        if (squareX > width()/2 + squareWidth/2) {
            squareX = -width()/2 - squareWidth/2;
            squareX = 0;
            squareY = -height()/2;
            isLeftToRight=false;
        }
    }
    else{
        squareY+=speed;
        if (squareY > height()/2 + squareHeight/2) {
            isLeftToRight=true;
            squareY=0;
            squareX = -width()/2;
        }
    }
    rotationAngle += 2;
    update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(squareX + width()/2, squareY + height()/2);
    painter.rotate(rotationAngle);
    painter.setPen(QPen(Qt::green, 5));
    painter.drawRect(-squareWidth/2, -squareHeight/2, squareWidth, squareHeight);
    painter.end();
}
