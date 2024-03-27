#ifndef SECONDLR_H
#define SECONDLR_H

#include <QMainWindow>
#include <QVector>
#include <QTextStream>
#include <algorithm>

namespace Ui {
class firstLR;
}

class firstLR : public QMainWindow
{
    Q_OBJECT

public:
    explicit firstLR(QWidget *parent = nullptr);
    void PrintFruits();
    ~firstLR();

private slots:
    void on_addFruitBtn_clicked();
    void SortByAsc();
    void SortByDesc();

private:
    Ui::firstLR *ui;
    QVector<QString> favoriteFruits;
};

#endif // SECONDLR_H
