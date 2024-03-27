#include "secondlr.h"
#include "ui_secondlr.h"

SecondLR::SecondLR(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SecondLR)
{
    ui->setupUi(this);
    connect(ui->printAsc, &QPushButton::clicked, this, &SecondLR::SortByAsc);
    connect(ui->printDesc, &QPushButton::clicked, this, &SecondLR::SortByDesc);
}

SecondLR::~SecondLR()
{
    delete ui;
}

void SecondLR::PrintFruits()
{
    ui->fruitList->clear();
    for (const auto& i : favoriteFruits) ui->fruitList->addItem(i);
}

void SecondLR::SortByAsc()
{
    std::sort(std::begin(favoriteFruits),std::end(favoriteFruits));
    PrintFruits();
    qDebug() << "Успіх!";
}

void SecondLR::SortByDesc()
{
    std::sort(favoriteFruits.rbegin(), favoriteFruits.rend());
    PrintFruits();
    qDebug() << "Успіх!";
}

void SecondLR::on_addFruitBtn_clicked()
{
    if(ui->inputLabel_2->text()==QString())return;
    favoriteFruits.push_back(ui->inputLabel_2->text());
    qDebug() << ui->inputLabel_2->text() << " успішно доданий!";
    ui->inputLabel_2->clear();
}
