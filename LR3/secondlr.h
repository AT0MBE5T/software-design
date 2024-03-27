#ifndef SECONDLR_H
#define SECONDLR_H

#include <QWidget>
#include <QVector>

namespace Ui {
class SecondLR;
}

class SecondLR : public QWidget
{
    Q_OBJECT

public:
    explicit SecondLR(QWidget *parent = nullptr);
    void PrintFruits();
    ~SecondLR();

private slots:
    void SortByAsc();
    void SortByDesc();
    void on_addFruitBtn_clicked();

private:
    Ui::SecondLR *ui;
    QVector<QString> favoriteFruits;
};

#endif // SECONDLR_H
