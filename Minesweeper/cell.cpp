#include "cell.h"
#include <stylehandler.h>

bool Cell::getFlag() const
{
    return isFlag;
}

void Cell::setFlag(bool _isFlag)
{
    isFlag = _isFlag;
}

bool Cell::getOpen() const
{
    return isOpen;
}

void Cell::setOpen(bool _isOpen)
{
    isOpen = _isOpen;
}

Cell::Cell() : isMine(false), isFlag(false), adjacentMines(-1), isOpen(false), location(Coordinate{-1, -1}) {}

Cell::Cell(Coordinate _location) : isMine(false), isFlag(false), adjacentMines(-1), isOpen(false), location(_location) {}

int Cell::getAdjacentMines()
{
    return adjacentMines;
}

bool Cell::getMine()
{
    return isMine;
}

Coordinate Cell::getLocation()
{
    return location;
}

void Cell::setAdjacentMines(int _minesAround)
{
    adjacentMines = _minesAround;
}

void Cell::setMine(bool _isMine)
{
    isMine = _isMine;
}

void Cell::setLocation(Coordinate _cord)
{
    location = _cord;
}

bool Cell::openCell(QPushButton* _btn)
{
    isOpen=true;
    QString style;
    if(isMine){
        style=StyleHandler::getMineStyle();
    }
    switch(adjacentMines){
    case 0:
        style=StyleHandler::getZeroMinesStyle();
        break;
    case 1:
        style=StyleHandler::getOneMineStyle();
        break;
    case 2:
        style=StyleHandler::getTwoMinesStyle();
        break;
    case 3:
        style=StyleHandler::getThreeMinesStyle();
        break;
    case 4:
        style=StyleHandler::getFourMinesStyle();
        break;
    case 5:
        style=StyleHandler::getFiveMinesStyle();
        break;
    case 6:
        style=StyleHandler::getSixMinesStyle();
        break;
    case 7:
        style=StyleHandler::getSevenMinesStyle();
        break;
    case 8:
        style=StyleHandler::getEightMinesStyle();
        break;
    }
    setStyle(_btn, style);
    return true;
}

void Cell::setStyle(QPushButton* _btn, const QString &_style)
{
    _btn->setStyleSheet(_style);
}
