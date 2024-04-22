#include "stylehandler.h"
#include <QFontDatabase>

StyleHandler::StyleHandler() {}

QString StyleHandler::getDefaultCellStyle()
{
    return "QPushButton{"
           "background-color: #f0f0f0;"
           "border: 1px solid #a0a0a0;"
           "}"
           "QPushButton::hover{"
           "background-color: rgb(200, 200, 200);"
          "}";
}

QString StyleHandler::getZeroMinesStyle()
{
    return "QPushButton{"
           "background-color: #CDCDCD;"
           "border: 1px solid #a0a0a0;"
           "}";
}

QString StyleHandler::getOneMineStyle()
{
    return "QPushButton{"
           "background-color: #CDCDCD;"
           "border: 1px solid #a0a0a0;"
           "image: url(:/img/img/one.png);"
           "}";
}

QString StyleHandler::getTwoMinesStyle()
{
    return "QPushButton{"
           "background-color: #CDCDCD;"
           "border: 1px solid #a0a0a0;"
           "image: url(:/img/img/two.png);"
           "}";
}

QString StyleHandler::getThreeMinesStyle()
{
    return "QPushButton{"
           "background-color: #CDCDCD;"
           "border: 1px solid #a0a0a0;"
           "image: url(:/img/img/three.png);"
           "}";
}

QString StyleHandler::getFourMinesStyle()
{
    return "QPushButton{"
           "background-color: #CDCDCD;"
           "border: 1px solid #a0a0a0;"
           "image: url(:/img/img/four.png);"
           "}";
}

QString StyleHandler::getFiveMinesStyle()
{
    return "QPushButton{"
           "background-color: #CDCDCD;"
           "border: 1px solid #a0a0a0;"
           "image: url(:/img/img/five.png);"
           "}";
}

QString StyleHandler::getSixMinesStyle()
{
    return "QPushButton{"
           "background-color: #CDCDCD;"
           "border: 1px solid #a0a0a0;"
           "image: url(:/img/img/six.png);"
           "}";
}

QString StyleHandler::getSevenMinesStyle()
{
    return "QPushButton{"
           "background-color: #CDCDCD;"
           "border: 1px solid #a0a0a0;"
           "image: url(:/img/img/seven.png);"
           "}";
}

QString StyleHandler::getEightMinesStyle()
{
    return "QPushButton{"
           "background-color: #CDCDCD;"
           "border: 1px solid #a0a0a0;"
           "image: url(:/img/img/eight.png);"
           "}";
}

QString StyleHandler::getMineStyle()
{
    return "QPushButton{"
           "background-color: #CDCDCD;"
           "border: 1px solid #a0a0a0;"
           "image: url(:/img/img/bomb.png);"
           "}";
}

QString StyleHandler::getFlagStyle()
{
    return "QPushButton{"
           "background-color: #f0f0f0;"
           "border: 1px solid #a0a0a0;"
           "image: url(:/img/img/flag.png);"
           "}";
}

QString StyleHandler::getSmileStyle()
{
    return "QPushButton{"
           "background: none;"
           "border: none;"
           "image: url(:/img/img/smile.png);"
           "}";
}

QString StyleHandler::getLoseSmileStyle()
{
    return "QPushButton{"
           "background: none;"
           "border: none;"
           "image: url(:/img/img/sadness.png);"
           "}";
}

QString StyleHandler::getTimerStyle()
{
    return "QLCDNumber {"
        "background-color: #2D3047;"
           "}";
}

QString StyleHandler::getButtonStyle()
{
    return
        "QPushButton {"
            "font-family: 'Exo 2', sans-serif;"
            "background-color: #DF7651;"
            "border-radius: 10%;"
            "color: white;"
            "font-size: 45px;"
            "font-weight: bold;"
            "text-align: center;"
            "text-decoration: none;"
        "}"
        "QPushButton:hover {"
            "background-color: #FF9671;"
        "}"
        "QPushButton:pressed{"
            "background-color: #BF5631;"
        "}";
}

QString StyleHandler::getTextStyle()
{
    return "QLabel{"
           "font-family: 'Exo 2', sans-serif;"
           "font-size: 20px;"
           "}";
}

QString StyleHandler::getComboBoxStyle()
{
    return
        "QComboBox {\
        font-family: 'Exo 2', sans-serif;\
        font-size: 20px;\
        border: 2px solid #DF7651;\
        border-radius: 5px;\
        background-color: #FFFFFF;\
    }";
}

QString StyleHandler::getCreateFieldActiveStyle()
{
    return "QPushButton {"
           "font-family: 'Exo 2', sans-serif;"
           "background-color: #DF7651;"
           "color: white;"
           "font-size: 20px;"
           "font-weight: bold;"
           "text-align: center;"
           "text-decoration: none;"
           "}"
           "QPushButton:hover {"
           "background-color: #FF9671;"
           "}"
           "QPushButton:pressed{"
           "background-color: #BF5631;"
           "}";
}

QString StyleHandler::getCreateFieldPassiveStyle()
{
    return "QPushButton {"
           "font-family: 'Exo 2', sans-serif;"
           "background-color: #BF5631;"
           "color: white;"
           "font-size: 20px;"
           "font-weight: bold;"
           "text-align: center;"
           "text-decoration: none;"
           "}"
           "QPushButton:hover {"
           "background-color: #DF7651;"
           "}"
           "QPushButton:pressed{"
           "background-color: #9F3611;"
           "}";
}

QString StyleHandler::getInputStyle()
{
    return
        "QLineEdit {"
        "background-color: #ffffff;"
        "border: 1px solid #FF9671;"
        "border-radius: 5px;"
        "padding: 5px;"
        "font-family: 'Exo 2', sans-serif;"
        "font-weight: bold;"
        "}"
        "QLineEdit:focus{"
        "border: 1px solid #DF7651;"
           "}";
}

QString StyleHandler::getBGStyle()
{
    return "background-color: #E3DCD2;";
}

void StyleHandler::setFonts()
{
    QFontDatabase::addApplicationFont(":/fonts/fonts/Exo2-VariableFont_wght.ttf");
}
