#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <secondlr.h>

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
    void radioClick();

    void on_radioButton_5_clicked(bool checked);

    void on_radioButton_6_clicked(bool checked);

    void on_comboBox_activated(int index);

private:
    Ui::MainWindow *ui;
    QString BGStyle;
    QRadioButton* radioButtonPtr;
    SecondLR *secondLR;
};
#endif // MAINWINDOW_H
