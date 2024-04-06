#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->scene = new PaintScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
    this->timer->start(100);
    this->connectButtons();
}

MainWindow::~MainWindow()
{
    delete scene;
    delete timer;
    delete ui;
}

void MainWindow::slotTimer()
{
    this->timer->stop();
    this->scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    this->timer->start(100);
    QMainWindow::resizeEvent(event);
}

void MainWindow::connectButtons()
{
    QPushButton* tempBtn;
    QList<QPushButton*> list = ui->centralWidget->findChildren<QPushButton*>();
    for(int i = 0; i < list.size(); ++i){
        tempBtn = qobject_cast<QPushButton*>(list[i]);
        tempBtn->setProperty("FigureType", QVariant::fromValue(figureTypes[i]));
        connect(tempBtn, &QPushButton::clicked, this, &MainWindow::clickFigureButton);
    }
    tempBtn=nullptr;
}

void MainWindow::setFigure(PaintScene::FigureTypes figure)
{
    this->scene->setTypeFigure(figure);
}

PaintScene::FigureTypes MainWindow::defineType(QPushButton*_clickedButton)
{
    return _clickedButton->property("FigureType").value<PaintScene::FigureTypes>();
}

void MainWindow::clickFigureButton()
{
    setFigure(defineType(qobject_cast<QPushButton*>(sender())));
}
