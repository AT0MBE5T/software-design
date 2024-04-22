#ifndef CREATEFIELD_H
#define CREATEFIELD_H

#include <QDialog>
#include <language.h>
#include <QIntValidator>
#include <QMessageBox>
#include <gamearea.h>

class MainArea;

namespace Ui {
class CreateField;
}

class CreateField : public QDialog
{
    Q_OBJECT
    const int minSize = 8;
    const int maxSize = 30;
    const double maxMinesRatio = 0.25;
    const double minMinesRatio = 0.1;
public:
    explicit CreateField(QWidget *parent = nullptr);
    void setLang(QVector<QString>* _lang);
    void setText();
    void setDefaultSettings();
    void setStateByCreateNew(bool _isCreateNew);
    void setMainAreaPointer(MainArea* _mainArea);
    void setValidators();
    void setStyles();
    void setConnects();
    ~CreateField();

private slots:
    void selectDefaultSize(int _index);

    void createButtonClicked();

private:
    Ui::CreateField *ui;
    QVector<QString>* lang;
    QIntValidator* validator;
    bool isCreateNew;
    GameArea* gameArea;
    MainArea* mainArea;
};

#endif // CREATEFIELD_H
