#ifndef CELL_H
#define CELL_H
#include <coordinate.h>
#include <QString>
#include <QPushButton>

class Cell
{
    bool isMine;
    bool isFlag;
    int adjacentMines;
    bool isOpen;
    Coordinate location;
public:
    Cell();
    Cell(Coordinate _location);

    int getAdjacentMines();
    bool getMine();
    Coordinate getLocation();

    void setAdjacentMines(int _minesAround);
    void setMine(bool _isMine);
    void setLocation(Coordinate _cord);

    bool openCell(QPushButton* _btn);
    void setStyle(QPushButton* _btn, const QString& _style);
    bool operator == (const Cell& _cell){
        return location.x == _cell.location.x && location.y == _cell.location.y;
    }
    bool operator != (const Cell& _cell){
        return location.x != _cell.location.x && location.y != _cell.location.y;
    }
    bool getFlag() const;
    void setFlag(bool _isFlag);
    bool getOpen() const;
    void setOpen(bool _isOpen);
};

#endif // CELL_H
