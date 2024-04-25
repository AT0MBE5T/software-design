#include "gamearea.h"
#include "ui_gamearea.h"
#include "mainarea.h"
#include "QScreen"

GameArea::GameArea(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameArea)
    , field(Field(int(),int(),int()))
    , LCDtimer(new QTimer)
    , isRead(false)
{
    ui->setupUi(this);
    setConnects();
    setCounters();
    setStyles();
}

void GameArea::setLang(QVector<QString> *_lang)
{
    lang = _lang;
}

void GameArea::setReadField(Field _field)
{
    field = _field;
    isRead=true;
}

void GameArea::spawnField()
{
    defaultButtonsArray();
    QPushButton* tempBtn;
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j){
            tempBtn = new QPushButton;
            buttonSettings(tempBtn);
            buttons[i].push_back(tempBtn);
            ui->playField->addWidget(tempBtn, i, j);
            tempBtn->setProperty("X", i);
            tempBtn->setProperty("Y", j);
            connect(tempBtn, &QPushButton::clicked, this, &GameArea::cellClick);
        }
    if(isRead)openReadCells();
    centerWindow();
    tempBtn=nullptr;
}

void GameArea::setFieldParams(int _rows, int _cols, int _mines)
{
    rows=_rows;
    cols=_cols;
    mines=_mines;
}

void GameArea::loseByMine()
{
    setSmileState(true);
    isGameEnded=true;
    stopField();
    field.showAllField(buttons);
    QMessageBox::information(this, lang->at(Language::getIndex("mineSweeper")), lang->at(Language::getIndex("lose")));
}

bool GameArea::winCondition()
{
    bool isWin=true;
    for(const auto&i:field.getMatrix()){
        for(const auto &j:i){
            if(!j.getOpen() && !j.getFlag()){
                isWin=false;
            }
        }
    }
    return isWin;
}

void GameArea::win()
{
    stopField();
    QMessageBox::information(this, lang->at(Language::getIndex("mineSweeper")), lang->at(Language::getIndex("win")));
    isGameEnded=true;
}

void GameArea::setDefaultSettings()
{
    setDefaultVariables();
    setText();
    ui->switchFlag->setStyleSheet("image: url(:/img/img/bomb.png);");
    setSmileState(false);
    ui->minesLeft->display(availableFlags);
    ui->timePassed->display("00:00:00");
}

void GameArea::setText()
{
    this->setWindowTitle(lang->at(Language::getIndex("mineSweeper")));
    ui->saveButton->setText(lang->at(Language::getIndex("save")));
    ui->backToMenuButton->setText(lang->at(Language::getIndex("backToMenu")));
}

void GameArea::centerWindow(const QPoint& _point)
{
    this->hide();
    this->show();
    this->resize(0, 0);
    this->setFixedSize(this->size());
    int widthGrid = ui->playField->sizeHint().width();
    int heightGrid = ui->playField->sizeHint().height();
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = std::abs(screenGeometry.center().x()-widthGrid/2);
    int y = std::abs(screenGeometry.center().y()-heightGrid/1.5);
    this->move(x, y);
    if(_point!=QPoint())this->move(_point.x(), _point.y());
}

void GameArea::buttonSettings(QPushButton* _btn)
{
    _btn->setStyleSheet(StyleHandler::getDefaultCellStyle());
    _btn->setSizePolicy(getButtonPolicy());
    _btn->setFixedSize(buttonSize,buttonSize);
}

QMessageBox* GameArea::getThreeButtonWindow(const QString& _text, const QString& _btnNameFirst, const QString& _btnNameSecond, const QString& _btnNameThird)
{
    QMessageBox* msgBox = new QMessageBox;
    msgBox->setWindowIcon(QIcon(":/img/img/logo.png"));
    msgBox->setWindowTitle(lang->at(Language::getIndex("mineSweeper")));
    msgBox->setText(_text);
    msgBox->addButton(_btnNameFirst, QMessageBox::ActionRole);
    msgBox->addButton(_btnNameSecond, QMessageBox::ActionRole);
    msgBox->addButton(_btnNameThird, QMessageBox::ActionRole);
    return msgBox;
}

QVector<Cell> GameArea::getRow(const QStringList& _rowString, int _currentRow, int _cols, int& _mines)
{
    QVector<Cell> row;
    for(int i = 0; i < _cols; ++i)
        row.push_back(getCell(_rowString[i], _currentRow, i, _mines));
    return row;
}

Cell GameArea::getCell(const QString& _cellString, int _currentRow, int _currentCol, int& _mines)
{
    const int flagIndex = 2;
    const int openIndex = 4;
    const int adjacentMinesIndex = 0;
    const int bombStringSize = 6;
    const int noBombStringSize = 5;
    Cell tempCell;
    QChar tempChr;
    tempCell.setLocation({_currentRow, _currentCol});
    if(_cellString.size() < noBombStringSize || _cellString.size() > bombStringSize) throw QString(lang->at(Language::getIndex("readingError")));
    if(_cellString.size()==bombStringSize){
        tempCell.setAdjacentMines(-1);
        tempCell.setMine(true);
        tempChr = _cellString[flagIndex+1];
        if(!tempChr.isDigit()) throw QString(lang->at(Language::getIndex("readingError")));
        tempCell.setFlag(tempChr.digitValue());
        tempChr = _cellString[openIndex+1];
        if(!tempChr.isDigit()) throw QString(lang->at(Language::getIndex("readingError")));
        tempCell.setOpen(tempChr.digitValue());
        _mines++;
    }else{
        tempChr = _cellString[adjacentMinesIndex];
        if(!tempChr.isDigit()) throw QString(lang->at(Language::getIndex("readingError")));
        tempCell.setAdjacentMines(tempChr.digitValue());
        tempCell.setMine(false);
        tempChr = _cellString[flagIndex];
        if(!tempChr.isDigit()) throw QString(lang->at(Language::getIndex("readingError")));
        tempCell.setFlag(tempChr.digitValue());
        tempChr = _cellString[openIndex];
        if(!tempChr.isDigit()) throw QString(lang->at(Language::getIndex("readingError")));
        tempCell.setOpen(tempChr.digitValue());
    }
    return tempCell;
}

void GameArea::setSmileEnable(bool _isEnable)
{
    ui->smile->setEnabled(_isEnable);
    isSmileActive=_isEnable;
}

void GameArea::setSaved(bool _isSaved)
{
    ui->saveButton->setDisabled(_isSaved);
    isSaved=_isSaved;
}

void GameArea::stopField()
{
    LCDtimer->stop();
    setSaved(true);
}

void GameArea::defaultButtonsArray()
{
    if(!buttons.empty())buttons.clear();
    buttons.resize(rows);
}

void GameArea::setDefaultVariables()
{
    isFlag=false;
    isStartTimer=false;
    if(isRead)LCDtimer->start(1000);
    else timeElapsed=0;
    setSaved(true);
    isGameEnded=false;
    isFirstMove=!isRead;
    availableFlags=mines;
    setSmileEnable(isRead);
}

void GameArea::flagAction(int _x, int _y, QPushButton *_btn)
{
    static QIcon emptyIcon;
    if(!availableFlags && !field.getMatrix()[_x][_y].getFlag())return;
    if(isRead){
        availableFlags--;
        field.getMatrix()[_x][_y].setFlag(true);
        _btn->setIcon(StyleHandler::getFlagStyle());
    }else{
        ui->minesLeft->display(field.getMatrix()[_x][_y].getFlag()?++availableFlags:--availableFlags);
        field.getMatrix()[_x][_y].setFlag(!field.getMatrix()[_x][_y].getFlag());
        _btn->setIcon(field.getMatrix()[_x][_y].getFlag()?StyleHandler::getFlagStyle():emptyIcon);
    }
    _btn->setIconSize(_btn->size());
}

void GameArea::openAction(int _x, int _y)
{
    if(!field.getMatrix()[_x][_y].getFlag()){
        if(field.getMatrix()[_x][_y].getMine()){
            loseByMine();
            return;
        }
        field.openCell(field.getMatrix()[_x][_y], buttons);
    }
}

void GameArea::setMainAreaPointer(MainArea *_mainArea)
{
    mainArea = _mainArea;
}

void GameArea::openReadCells()
{
    for(auto&i:field.getMatrix())
        for(auto&j:i){
            if(j.getOpen())field.openCell(j,buttons);
            if(j.getFlag()){
                flagAction(j.getLocation().x, j.getLocation().y, buttons[j.getLocation().x][j.getLocation().y]);
            }
        }
    isRead=false;
    ui->minesLeft->display(availableFlags);
}

void GameArea::setSmileState(bool _isLose)
{
    ui->smile->setStyleSheet(_isLose?StyleHandler::getLoseSmileStyle():StyleHandler::getSmileStyle());
}

void GameArea::firstMove(int _x, int _y)
{
    if(!isFlag){
        field = createField(rows,cols,mines,_x,_y);
        isFirstMove = false;
        isStartTimer=true;
        setSmileEnable(true);
        LCDtimer->start(1000);
        setSaved(false);
        field.openCell(field.getMatrix()[_x][_y], buttons);
    }
    else QMessageBox::warning(this, lang->at(Language::getIndex("mineSweeper")), lang->at(Language::getIndex("firstMoveFlag")));
}

void GameArea::setStyles()
{
    ui->backToMenuButton->setStyleSheet(StyleHandler::getButtonStyle());
    ui->saveButton->setStyleSheet(StyleHandler::getButtonStyle());
    ui->timePassed->setStyleSheet(StyleHandler::getTimerStyle());
    ui->minesLeft->setStyleSheet(StyleHandler::getTimerStyle());
    this->setStyleSheet(StyleHandler::getBGStyle());
    this->setWindowIcon(QIcon(":/img/img/logo.png"));
}

void GameArea::clearField()
{
    QLayoutItem *item;
    while ((item = ui->playField->takeAt(0)) != nullptr) {
        if (QWidget *widget = item->widget())
            widget->deleteLater();
        delete item;
    }
}

QSizePolicy GameArea::getButtonPolicy()
{
    QSizePolicy sizePolicy = QPushButton().sizePolicy();
    sizePolicy.setVerticalPolicy(QSizePolicy::Expanding);
    sizePolicy.setHorizontalPolicy(QSizePolicy::Expanding);
    return sizePolicy;
}

QPalette GameArea::getPaletteForLCDNumber()
{
    QPalette palet = QLCDNumber().palette();
    palet.setColor(palet.WindowText, QColor(232, 72, 85));
    return palet;
}

Field GameArea::createField(int _rows, int _cols, int _mines, int xStart, int yStart)
{
    Field tempField(_rows, _cols, _mines);
    do{
        tempField.setMatrix(generateMatrix(_rows, _cols, _mines));
        tempField.fillFieldWithNumbers();
    }while(tempField.getMatrix()[xStart][yStart].getAdjacentMines());
    return tempField;
}

Field GameArea::readMatrixFromFile()
{
    const int rowIndex = 0;
    const int colIndex = 1;
    QVector<QVector<Cell>> matrix;
    int rows=0, cols=0, mines=0;
    int currentRow=0;
    QFile file("save.txt");
    QStringList rowString;
    if(file.open(QIODevice::ReadOnly)){
        QTextStream text(&file);
        QStringList rowsCols = text.readLine().split(':', Qt::SkipEmptyParts);
        if(rowsCols.size()!=2) throw QString(lang->at(Language::getIndex("readingError")));
        rows = rowsCols[rowIndex].toInt();
        cols = rowsCols[colIndex].toInt();
        rowsCols.clear();
        rowsCols = text.readLine().split(' ', Qt::SkipEmptyParts);
        if(rowsCols.size()!=1) throw QString(lang->at(Language::getIndex("readingError")));
        timeElapsed = rowsCols[0].toInt();
        while(!text.atEnd()){
            rowString = text.readLine().split(' ', Qt::SkipEmptyParts);
            if(rowString.size()!=cols) throw QString(lang->at(Language::getIndex("readingError")));
            try{
                matrix.push_back(getRow(rowString, currentRow, cols, mines));
            }catch(...){
                throw QString(lang->at(Language::getIndex("readingError")));
            }

            currentRow++;
            if(currentRow>rows) throw QString(lang->at(Language::getIndex("readingError")));
        }
    }else throw QString(lang->at(Language::getIndex("readingError")));
    file.close();
    return Field(rows,cols,mines,matrix);
}

QVector<QVector<Cell>> GameArea::generateMatrix(int _rows, int _cols, int _mines)
{
    QVector<QVector<Cell>> matrix(_rows);
    for(auto &i:matrix)i.resize(_cols);
    for(int i = 0; i < _rows; ++i)
        for(int j = 0; j < _cols; ++j)
            matrix[i][j].setLocation(Coordinate{i, j});
    int x, y;
    while(_mines){
        x = rand()%_rows;
        y = rand()%_cols;
        if(!matrix[x][y].getMine()){
            matrix[x][y].setMine(true);
            _mines--;
        }
    }
    return matrix;
}

GameArea::~GameArea()
{
    clearField();
    delete LCDtimer;
    delete ui;
}

void GameArea::cellClick()
{
    if(isGameEnded)return;
    auto btn = qobject_cast<QPushButton*>(sender());
    int x = btn->property("X").toInt();
    int y = btn->property("Y").toInt();
    if(isFirstMove){
        firstMove(x,y);
        return;
    }
    if(!field.getMatrix()[x][y].getOpen()){
        if(isSaved) setSaved(false);
        if(isFlag)flagAction(x, y, buttons[x][y]);
        else openAction(x, y);
        if(!isGameEnded && !availableFlags && winCondition())win();
    }
}

void GameArea::switcherClick()
{
    isFlag = isFlag?false:true;
    QString str = isFlag?":/img/img/flag.png":":/img/img/bomb.png";
    ui->switchFlag->setStyleSheet("image: url(" + str + ");");
}

void GameArea::updateTime()
{
    ++timeElapsed;
    Times times = Times::getTime(timeElapsed);
    QString timeString = QString("%1:%2:%3")
                             .arg(times.getHours(), 2, 10, QChar('0'))
                             .arg(times.getMinutes(), 2, 10, QChar('0'))
                             .arg(times.getSeconds(), 2, 10, QChar('0'));
    ui->timePassed->display(timeString);
}

void GameArea::smileClick()
{
    qDebug() << "smile";
    LCDtimer->stop();
    if(!isFirstMove && !isGameEnded && !isSaved){
        QMessageBox* msgBox = getThreeButtonWindow(lang->at(Language::getIndex("wannaSaveQuestion")), lang->at(Language::getIndex("save")), lang->at(Language::getIndex("createNoSave")), lang->at(Language::getIndex("cancel")));
        int ret = msgBox->exec();
        if(ret==2){
            LCDtimer->start();
            return;
        }
        if(!ret)saveClick();
        delete msgBox;
    }
    QPoint point = this->pos();
    spawnField();
    centerWindow(point);
    setDefaultSettings();
}

void GameArea::saveClick()
{
    LCDtimer->stop();
    QString str;
    QFile file("save.txt");
    if(file.open(QIODevice::WriteOnly)){
        QTextStream record(&file);
        record << field.getRows() << ":" << field.getCols() << '\n';
        record << timeElapsed << '\n';
        for(auto &i:field.getMatrix()){
            str.clear();
            for(auto &j:i){
                str+=QString::number(j.getAdjacentMines()) + ":" + QString::number(j.getFlag()) + ":" + QString::number(j.getOpen()) + ' ';
            }
            record << str << '\n';
        }
    }
    else qWarning("Could not open file");
    file.close();
    setSaved(true);
    auto ans = QMessageBox::information(this, lang->at(Language::getIndex("mineSweeper")), lang->at(Language::getIndex("successSave")));
    if(ans==QMessageBox::StandardButton::Ok || ans == QMessageBox::StandardButton::Close)LCDtimer->start();
}

void GameArea::backToMenuClick()
{
    LCDtimer->stop();
    if(!isFirstMove && !isGameEnded && !isSaved){
        QMessageBox* msgBox = getThreeButtonWindow(lang->at(Language::getIndex("wannaSaveQuestion")), lang->at(Language::getIndex("save")), lang->at(Language::getIndex("exitNoSave")), lang->at(Language::getIndex("cancel")));
        int ret = msgBox->exec();
        if(ret==2){
            LCDtimer->start();
            return;
        }
        if(!ret)saveClick();
        delete msgBox;
    }
    this->close();
    clearField();
    mainArea->show();
}

void GameArea::setCounters()
{
    ui->timePassed->setSegmentStyle(QLCDNumber::Flat);
    ui->minesLeft->setSegmentStyle(QLCDNumber::Flat);
    ui->timePassed->setPalette(getPaletteForLCDNumber());
    ui->minesLeft->setPalette(getPaletteForLCDNumber());
    ui->timePassed->setDigitCount(8);
    ui->minesLeft->setDigitCount(2);
}

void GameArea::setConnects()
{
    connect(ui->backToMenuButton, &QPushButton::clicked, this, &GameArea::backToMenuClick);
    connect(ui->switchFlag, &QPushButton::clicked, this, &GameArea::switcherClick);
    connect(ui->smile, &QPushButton::clicked, this, &GameArea::smileClick);
    connect(ui->saveButton, &QPushButton::clicked, this, &GameArea::saveClick);
    connect(LCDtimer, &QTimer::timeout, this, &GameArea::updateTime);
}
