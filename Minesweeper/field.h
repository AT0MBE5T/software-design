#ifndef FIELD_H
#define FIELD_H

#include <QVector>
#include <cell.h>

class Field
{
public:
    Field();
    Field(int _rows, int _cols, int _minesAmount, QVector<QVector<Cell>> _matrix=QVector<QVector<Cell>>());
    bool setDefaultCellStyles();
    bool fillFieldWithNumbers();
    bool isValid(int x, int y);
    void showAllField(QVector<QVector<QPushButton*>> _buttons);
    void openCell(Cell& _cell, QVector<QVector<QPushButton*>> _buttons);
    int getRows();
    int getCols();
    int getMines();
    void setMatrix(QVector<QVector<Cell>> _matrix);
    QVector<QVector<Cell>>& getMatrix();
private:
    int getMinesAround(Cell _cell);
    void crossZeros(QVector<QVector<QPushButton*>> _buttons, Cell& _cell);
    int rows, cols, minesAmount;
    QVector<QVector<Cell>> matrix;
};

#endif // FIELD_H
