#include "gamearea.h"
#include "ui_gamearea.h"
#include "mainarea.h"

GameArea::GameArea(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameArea)
    , field(Field(int(),int(),int()))
    , LCDtimer(new QTimer)
    , isRead(false)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/img/logo.png"));
    setConnects();
    setCounters();
    setStyles();
}

void GameArea::setLang(QVector<QString> *_lang)
{
    lang = _lang;
}

void GameArea::setField(Field _field, bool _isRead)
{
    field = _field;
    if(_isRead){
        isRead=true;
    }else{
        field.fillFieldWithNumbers();
    }
}

void GameArea::spawnField()
{    
    defaultButtonsArray();
    ui->playField->setVerticalSpacing(0);
    ui->playField->setHorizontalSpacing(0);
    QPushButton* tempBtn;
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            tempBtn = new QPushButton;
            tempBtn->setStyleSheet(StyleHandler::getDefaultCellStyle());
            tempBtn->setSizePolicy(getButtonPolicy());
            buttons[i].push_back(tempBtn);
            ui->playField->addWidget(tempBtn, i, j);
            tempBtn->setProperty("X", i);
            tempBtn->setProperty("Y", j);
            connect(tempBtn, &QPushButton::clicked, this, &GameArea::cellClick);
        }
    }
    if(isRead)openReadCells();
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

void GameArea::stopField()
{
    LCDtimer->stop();
    for(auto &i:buttons){
        for(auto &j:i){
            j->setDisabled(true);
        }
    }
    ui->saveButton->setDisabled(true);
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
    isSaved=true;
    if(isRead){
        LCDtimer->start(1000);
    }
    else timeElapsed=0;
    ui->saveButton->setDisabled(true);
    isGameEnded=false;
    isFirstMove=!isRead;
    availableFlags=mines;
}

void GameArea::flagAction(int _x, int _y, QPushButton *_btn)
{
    if(!availableFlags && !field.getMatrix()[_x][_y].getFlag())return;
    if(isRead){
        availableFlags--;
        field.getMatrix()[_x][_y].setFlag(true);
        _btn->setStyleSheet(StyleHandler::getFlagStyle());
    }else{
        ui->minesLeft->display(field.getMatrix()[_x][_y].getFlag()?++availableFlags:--availableFlags);
        field.getMatrix()[_x][_y].setFlag(!field.getMatrix()[_x][_y].getFlag());
        _btn->setStyleSheet(field.getMatrix()[_x][_y].getFlag()?StyleHandler::getFlagStyle():StyleHandler::getDefaultCellStyle());
    }
}



void GameArea::openAction(int _x, int _y)
{
    if(field.getMatrix()[_x][_y].getMine()){
        loseByMine();
        return;
    }
    field.openCell(field.getMatrix()[_x][_y], buttons);
}

void GameArea::setMainAreaPointer(MainArea *_mainArea)
{
    mainArea = _mainArea;
}

void GameArea::openReadCells()
{
    for(auto&i:field.getMatrix()){
        for(auto&j:i){
            if(j.getOpen())field.openCell(j,buttons);
            if(j.getFlag()){
                flagAction(j.getLocation().x, j.getLocation().y, buttons[j.getLocation().x][j.getLocation().y]);
            }
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
    field = createField(rows,cols,mines,_x,_y);
    isFirstMove = false;
    isStartTimer=true;
    LCDtimer->start(1000);
    ui->saveButton->setDisabled(false);
}

void GameArea::setStyles()
{
    ui->backToMenuButton->setStyleSheet(StyleHandler::getButtonStyle());
    ui->saveButton->setStyleSheet(StyleHandler::getButtonStyle());
    ui->timePassed->setStyleSheet(StyleHandler::getTimerStyle());
    ui->minesLeft->setStyleSheet(StyleHandler::getTimerStyle());
    this->setStyleSheet(StyleHandler::getBGStyle());
}

void GameArea::clearField()
{
    QLayoutItem *item;
    while ((item = ui->playField->takeAt(0)) != nullptr) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
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

Field GameArea::createField(int _rows, int _cols, int _mines, int xStart, int yStart, QVector<QVector<Cell> > _matrix)
{
    bool isFieldDefault=Field::isMatrixDefault(_matrix);
    Field tempField(_rows, _cols, _mines);
    do{
        if(!isFieldDefault)break;
        _matrix=generateMatrix(_rows, _cols, _mines);
        tempField.setMatrix(_matrix);
        tempField.fillFieldWithNumbers();
    }while(tempField.getMatrix()[xStart][yStart].getAdjacentMines());
    return tempField;
}

Field GameArea::readMatrixFromFile()
{
    const int adjacentMinesIndex = 0;
    const int flagIndex = 2;
    const int openIndex = 4;
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
        if(rowsCols.size()!=2){
            throw QString(lang->at(Language::getIndex("readingError")));
        }
        rows = rowsCols[rowIndex].toInt();
        cols = rowsCols[colIndex].toInt();
        matrix.resize(rows);
        rowsCols.clear();
        rowsCols = text.readLine().split(' ', Qt::SkipEmptyParts);
        if(rowsCols.size()!=1){
            throw QString(lang->at(Language::getIndex("readingError")));
        }
        timeElapsed = rowsCols[0].toInt();
        while(!text.atEnd()){
            rowString = text.readLine().split(' ', Qt::SkipEmptyParts);
            if(rowString.size()!=cols){
                throw QString(lang->at(Language::getIndex("readingError")));
            }
            Cell tempCell;
            for(int i = 0; i < cols; ++i){
                tempCell.setLocation({currentRow, i});
                if(rowString[i].size()==6){
                    tempCell.setAdjacentMines(-1);
                    tempCell.setMine(true);
                    tempCell.setFlag(rowString[i][flagIndex+1].digitValue());
                    tempCell.setOpen(rowString[i][openIndex+1].digitValue());
                    mines++;
                }else{
                    tempCell.setAdjacentMines(rowString[i][adjacentMinesIndex].digitValue());
                    tempCell.setMine(false);
                    tempCell.setFlag(rowString[i][flagIndex].digitValue());
                    tempCell.setOpen(rowString[i][openIndex].digitValue());
                }
                matrix[currentRow].push_back(tempCell);
            }
            currentRow++;
            if(currentRow>rows){
                throw QString(lang->at(Language::getIndex("readingError")));
            }
        }
    }else{
        throw QString(lang->at(Language::getIndex("readingError")));
    }
    file.close();
    return Field(rows,cols,mines,matrix);
}

QVector<QVector<Cell>> GameArea::generateMatrix(int _rows, int _cols, int _mines)
{
    QVector<QVector<Cell>> matrix(_rows);
    for(auto &i:matrix)i.resize(_cols);

    for(int i = 0; i < _rows; ++i){
        for(int j = 0; j < _cols; ++j){
            matrix[i][j].setLocation(Coordinate{i, j});
        }
    }
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
    for(int i = 0; i < field.getRows(); ++i)
        for(int j = 0; j < field.getCols(); ++j)
            delete buttons[i][j];
    delete ui;
}

void GameArea::cellClick()
{
    auto btn = qobject_cast<QPushButton*>(sender());
    int x = btn->property("X").toInt();
    int y = btn->property("Y").toInt();
    if(isFirstMove && isFlag){
        QMessageBox::warning(this, lang->at(Language::getIndex("mineSweeper")), lang->at(Language::getIndex("firstMoveFlag")));
        return;
    }
    if(isFirstMove && !isFlag){
        firstMove(x,y);
    }
    if(!field.getMatrix()[x][y].getOpen()){
        if(isSaved){
            ui->saveButton->setDisabled(false);
            isSaved=false;
        }
        if(isFlag){
            flagAction(x, y, buttons[x][y]);
        }else if(!isFlag && !field.getMatrix()[x][y].getFlag()){
            openAction(x, y);
        }
        if(!isGameEnded && winCondition())win();
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
    LCDtimer->stop();
    if(!isFirstMove && !isGameEnded && !isSaved){
        QMessageBox msgBox;
        msgBox.setWindowTitle(lang->at(Language::getIndex("mineSweeper")));
        msgBox.setText(lang->at(Language::getIndex("wannaSaveQuestion")));
        msgBox.addButton(lang->at(Language::getIndex("save")), QMessageBox::ActionRole);
        msgBox.addButton(lang->at(Language::getIndex("createNoSave")), QMessageBox::ActionRole);
        msgBox.addButton(lang->at(Language::getIndex("cancel")), QMessageBox::ActionRole);
        int ret = msgBox.exec();
        if(ret==2){
            LCDtimer->start();
            return;
        }
        if(!ret)saveClick();
    }
    spawnField();
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
    isSaved=true;
    ui->saveButton->setDisabled(true);
    auto ans = QMessageBox::information(this, lang->at(Language::getIndex("mineSweeper")), lang->at(Language::getIndex("successSave")));
    if(ans==QMessageBox::StandardButton::Ok || ans == QMessageBox::StandardButton::Close)LCDtimer->start();
}

void GameArea::backToMenuClick()
{
    LCDtimer->stop();
    if(!isFirstMove && !isGameEnded && !isSaved){
        QMessageBox msgBox;
        msgBox.setWindowTitle(lang->at(Language::getIndex("mineSweeper")));
        msgBox.setText(lang->at(Language::getIndex("wannaSaveQuestion")));
        msgBox.addButton(lang->at(Language::getIndex("save")), QMessageBox::ActionRole);
        msgBox.addButton(lang->at(Language::getIndex("exitNoSave")), QMessageBox::ActionRole);
        msgBox.addButton(lang->at(Language::getIndex("cancel")), QMessageBox::ActionRole);
        int ret = msgBox.exec();
        if(ret==2){
            LCDtimer->start();
            return;
        }
        if(!ret)saveClick();
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
