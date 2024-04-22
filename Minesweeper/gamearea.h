#ifndef GAMEAREA_H
#define GAMEAREA_H

#include <QWidget>
#include <language.h>
#include <field.h>
#include <QPushButton>
#include <QTimer>
#include <stylehandler.h>
#include <times.h>

class MainArea;

namespace Ui {
class GameArea;
}

class GameArea : public QWidget
{
    Q_OBJECT

public:
    explicit GameArea(QWidget *parent = nullptr);
    void setLang(QVector<QString>* _lang);
    void setField(Field _field, bool _isRead);
    void spawnField();
    void setFieldParams(int _rows, int _cols, int _mines);
    void loseByMine();
    bool winCondition();
    void win();
    void setDefaultSettings();
    void setText();
    void stopField();
    void defaultButtonsArray();
    void setDefaultVariables();
    void flagAction(int _x, int _y, QPushButton* _btn);
    void openAction(int _x, int _y);
    void setMainAreaPointer(MainArea* _mainArea);
    void openReadCells();
    void setSmileState(bool _isLose);
    void firstMove(int _x, int _y);
    void setStyles();
    void clearField();
    QSizePolicy getButtonPolicy();
    QPalette getPaletteForLCDNumber();
    Field createField(int _rows, int _cols, int _mines, int xStart, int yStart, QVector<QVector<Cell>> _matrix=QVector<QVector<Cell>>());
    Field readMatrixFromFile();
    QVector<QVector<Cell>> generateMatrix(int _rows, int _cols, int _mines);
    ~GameArea();

private slots:
    void cellClick();
    void switcherClick();
    void updateTime();
    void smileClick();
    void saveClick();
    void backToMenuClick();

private:
    void setCounters();
    void setConnects();
    Ui::GameArea *ui;
    QVector<QString>* lang;
    Field field;
    QVector<QVector<QPushButton*>> buttons;
    MainArea* mainArea;
    QTimer* LCDtimer;
    bool isFlag;
    bool isStartTimer;
    int timeElapsed;
    int availableFlags;
    bool isGameEnded;
    bool isFirstMove;
    bool isRead;
    bool isSaved;
    int rows;
    int cols;
    int mines;
};

#endif // GAMEAREA_H
