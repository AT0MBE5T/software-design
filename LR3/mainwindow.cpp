#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    first=new firstLR;
    for(int i = 0; i < ui->verticalLayout->count(); ++i){
        radioButton = qobject_cast<QRadioButton*>(ui->verticalLayout->itemAt(i)->widget());
        radioButton->setProperty("Number",i+1);
        connect(radioButton, &QRadioButton::clicked, this, &MainWindow::radioClick);
    }
}

MainWindow::~MainWindow()
{
    delete first;
    delete radioButton;
    delete ui;
}


void MainWindow::radioClick(){
    radioButton = qobject_cast<QRadioButton*>(sender());
    switch(radioButton->property("Number").toInt()){
    case 1:
        ui->image2->setStyleSheet("image: url(:/img/Number1.png);");
        break;
    case 2:
        ui->image2->setStyleSheet("image: url(:/img/Number2.png);");
        break;
    case 3:
        ui->image2->setStyleSheet("image: url(:/img/Number3.png);");
        break;
    case 4:
        ui->image2->setStyleSheet("image: url(:/img/Number4.png);");
        break;
    }
}


void MainWindow::on_radioButton_5_clicked(bool checked)
{
    if(checked) ui->image->setStyleSheet("background-color: rgb(219, 245, 214);");
}


void MainWindow::on_radioButton_6_clicked(bool checked)
{
    if(checked) ui->image->setStyleSheet("background: none;");
}


void MainWindow::on_comboBox_activated(int index)
{
    if(!index){
        first->show();
        this->close();
    }
}

