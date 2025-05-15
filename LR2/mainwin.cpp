#include "mainwin.h"
#include "ui_mainwin.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->printAsc, &QPushButton::clicked, this, &MainWindow::SortByAsc);
    connect(ui->printDesc, &QPushButton::clicked, this, &MainWindow::SortByDesc);
}

void MainWindow::SortByDesc() {
    std::sort(favoriteFruits.rbegin(), favoriteFruits.rend());
    PrintFruits();
    qDebug() << "Успіх!";
}

void MainWindow::SortByAsc() {
    std::sort(std::begin(favoriteFruits),std::end(favoriteFruits));
    PrintFruits();
    qDebug() << "Успіх!";
}

void MainWindow::PrintFruits() {
    ui->fruitList->clear();
    for (const auto& i : favoriteFruits) ui->fruitList->addItem(i);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addFruitBtn_clicked()
{
    if(ui->inputLabel->text()==QString())return;
    favoriteFruits.push_back(ui->inputLabel->text());
    qDebug() << ui->inputLabel -> text() << " успішно доданий!";
    ui->inputLabel->clear();
}

