#include "secondlr.h"
#include "ui_firstlr.h"

firstLR::firstLR(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::firstLR)
{
    ui->setupUi(this);
    connect(ui->printAsc, &QPushButton::clicked, this, &firstLR::SortByAsc);
    connect(ui->printDesc, &QPushButton::clicked, this, &firstLR::SortByDesc);
}

void firstLR::PrintFruits()
{
    ui->fruitList->clear();
    for (const auto& i : favoriteFruits) ui->fruitList->addItem(i);
}

firstLR::~firstLR()
{
    delete ui;
}

void firstLR::on_addFruitBtn_clicked()
{
    if(ui->inputLabel_2->text()==QString())return;
    favoriteFruits.push_back(ui->inputLabel_2->text());
    qDebug() << ui->inputLabel_2->text() << " успішно доданий!";
    ui->inputLabel_2->clear();
}

void firstLR::SortByAsc()
{
    std::sort(std::begin(favoriteFruits),std::end(favoriteFruits));
    PrintFruits();
    qDebug() << "Успіх!";
}

void firstLR::SortByDesc()
{
    std::sort(favoriteFruits.rbegin(), favoriteFruits.rend());
    PrintFruits();
    qDebug() << "Успіх!";
}
