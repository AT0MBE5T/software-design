#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <QVector>
#include <QTextStream>
//#include <algorithm>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void PrintFruits();
    ~MainWindow();

private slots:
    void on_addFruitBtn_clicked();
    void SortByAsc();
    void SortByDesc();
private:
    Ui::MainWindow *ui;
    QVector<QString> favoriteFruits;
};
#endif // MAINWIN_H
