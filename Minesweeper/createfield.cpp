#include "createfield.h"
#include "ui_createfield.h"
#include "mainarea.h"

CreateField::CreateField(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateField)
    , validator(new QIntValidator(0, 100))
    , isCreateNew(false)
    , gameArea(nullptr)
{
    ui->setupUi(this);
    setStyles();
    this->setWindowIcon(QIcon(":/img/img/logo.png"));
    setValidators();
    setConnects();
}

void CreateField::setLang(QVector<QString> *_lang)
{
    lang = _lang;
}

void CreateField::setText()
{
    ui->defaultSizes->setItemText(0, lang->at(Language::getIndex("selectStandartSize")));
    ui->generateLabel->setText(lang->at(Language::getIndex("howToCreateFieldLabel")));
    ui->readFileBtn->setText(lang->at(Language::getIndex("readFileChoice")));
    ui->createNewBtn->setText(lang->at(Language::getIndex("generateChoice")));
    ui->sizeLabel->setText(lang->at(Language::getIndex("sizeFieldInput")));
    ui->minesLabel->setText(lang->at(Language::getIndex("amountMinesInput")));
    ui->createButton->setText(lang->at(Language::getIndex("createButton")));
    this->setWindowTitle(lang->at(Language::getIndex("mineSweeper")));
}

void CreateField::setDefaultSettings()
{
    ui->heightInput->clear();
    ui->minesInput->clear();
    ui->widthInput->clear();
    ui->defaultSizes->setCurrentIndex(0);
    setStateByCreateNew(false);
}

void CreateField::setStateByCreateNew(bool _isCreateNew)
{
    ui->readFileBtn->setStyleSheet(_isCreateNew?StyleHandler::getCreateFieldPassiveStyle():StyleHandler::getCreateFieldActiveStyle());
    ui->createNewBtn->setStyleSheet(!_isCreateNew?StyleHandler::getCreateFieldPassiveStyle():StyleHandler::getCreateFieldActiveStyle());
    _isCreateNew?ui->defaultSizes->show():ui->defaultSizes->hide();
    _isCreateNew?ui->minesLabel->show():ui->minesLabel->hide();
    _isCreateNew?ui->sizeLabel->show():ui->sizeLabel->hide();
    _isCreateNew?ui->xLabel->show():ui->xLabel->hide();
    _isCreateNew?ui->heightInput->show():ui->heightInput->hide();
    _isCreateNew?ui->widthInput->show():ui->widthInput->hide();
    _isCreateNew?ui->minesInput->show():ui->minesInput->hide();
    ui->createButton->setText(lang->at(Language::getIndex(_isCreateNew?"createButton":"readButton")));
    isCreateNew = _isCreateNew;
}

void CreateField::setMainAreaPointer(MainArea *_mainArea)
{
    mainArea = _mainArea;
}

void CreateField::setValidators()
{
    ui->heightInput->setValidator(validator);
    ui->widthInput->setValidator(validator);
    ui->minesInput->setValidator(validator);
}

void CreateField::setStyles()
{
    ui->readFileBtn->setStyleSheet(StyleHandler::getCreateFieldActiveStyle());
    ui->createNewBtn->setStyleSheet(StyleHandler::getCreateFieldPassiveStyle());
    ui->defaultSizes->setStyleSheet(StyleHandler::getComboBoxStyle());
    ui->createButton->setStyleSheet(StyleHandler::getButtonStyle());
    ui->generateLabel->setStyleSheet(StyleHandler::getTextStyle());
    ui->minesLabel->setStyleSheet(StyleHandler::getTextStyle());
    ui->sizeLabel->setStyleSheet(StyleHandler::getTextStyle());
    ui->xLabel->setStyleSheet(StyleHandler::getTextStyle());
    ui->heightInput->setStyleSheet(StyleHandler::getInputStyle());
    ui->widthInput->setStyleSheet(StyleHandler::getInputStyle());
    ui->minesInput->setStyleSheet(StyleHandler::getInputStyle());
    this->setStyleSheet(StyleHandler::getBGStyle());
}

void CreateField::setConnects()
{
    connect(ui->createButton, &QPushButton::clicked, this, &CreateField::createButtonClicked);
    connect(ui->defaultSizes, &QComboBox::activated, this, &CreateField::selectDefaultSize);
    connect(ui->createNewBtn, &QPushButton::clicked, this, [&](){
        setStateByCreateNew(true);
    });
    connect(ui->readFileBtn, &QPushButton::clicked, this, [&](){
        setStateByCreateNew(false);
    });
}

CreateField::~CreateField()
{
    delete gameArea;
    delete validator;
    delete ui;
}

void CreateField::selectDefaultSize(int _index)
{
    if(!_index)return;
    const int widthIndex = 0;
    const int heightIndex = 2;
    const int minesIndex = 4;
    QStringList element = ui->defaultSizes->currentText().split(" ", Qt::SkipEmptyParts);
    ui->widthInput->setText(element[widthIndex]);
    ui->heightInput->setText(element[heightIndex]);
    ui->minesInput->setText(element[minesIndex]);
}


void CreateField::createButtonClicked()
{
    Field field;
    if(isCreateNew){
        int rows = ui->widthInput->text().toInt();
        int cols = ui->heightInput->text().toInt();
        if((rows < minSize || rows > maxSize) || (cols < minSize || cols > maxSize)){
            QMessageBox::warning(this, lang->at(Language::getIndex("mineSweeper")), lang->at(Language::getIndex("wrongSize")) + ' ' + QString::number(minSize) + " - " + QString::number(maxSize));
            return;
        }
        if(rows*cols*maxMinesRatio < ui->minesInput->text().toInt() || rows*cols*minMinesRatio > ui->minesInput->text().toInt()){
            QMessageBox::warning(this, lang->at(Language::getIndex("mineSweeper")), lang->at(Language::getIndex("wrongMines")) + ' ' + QString::number(minMinesRatio*100) + "% - " + QString::number(maxMinesRatio*100) + '%');
            return;
        }
    }
    this->close();
    mainArea->hide();
    if(!gameArea) gameArea = new GameArea;
    gameArea->setLang(lang);
    if(!isCreateNew){
        try{
            field = gameArea->readMatrixFromFile();
        }catch(const QString& e){
            QMessageBox::critical(this, lang->at(Language::getIndex("mineSweeper")), e);
            mainArea->show();
            return;
        }
        gameArea->setFieldParams(field.getRows(), field.getCols(), field.getMines());
        gameArea->setField(field,true);
    }
    else gameArea->setFieldParams(ui->widthInput->text().toInt(), ui->heightInput->text().toInt(), ui->minesInput->text().toInt());
    gameArea->setDefaultSettings();
    gameArea->spawnField();
    gameArea->setMainAreaPointer(mainArea);
    QMessageBox::information(this, lang->at(Language::getIndex("mineSweeper")), lang->at(Language::getIndex("fieldCreated")));
    gameArea->show();
}

