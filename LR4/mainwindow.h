#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPainter>
#include <QTime>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateRotate();

private:
    Ui::MainWindow *ui;
    QPainter painter;
    QTimer* timer;
    qreal squareX;
    qreal squareY;
    qreal speed;
    qreal rotationAngle;
    int squareWidth;
    int squareHeight;
    bool isLeftToRight;

protected:
    void paintEvent(QPaintEvent *) override;
};
#endif // MAINWINDOW_H
