#ifndef STYLEHANDLER_H
#define STYLEHANDLER_H

#include <QString>
#include <QPixmap>

class StyleHandler
{
public:
    StyleHandler();
    static QString getDefaultCellStyle();
    static QString getZeroMinesStyle();
    static QString getOneMineStyle();
    static QString getTwoMinesStyle();
    static QString getThreeMinesStyle();
    static QString getFourMinesStyle();
    static QString getFiveMinesStyle();
    static QString getSixMinesStyle();
    static QString getSevenMinesStyle();
    static QString getEightMinesStyle();
    static QString getNineMinesStyle();
    static QString getMineStyle();
    static QString getFlagStyle();
    static QString getSmileStyle();
    static QString getLoseSmileStyle();
    static QString getTimerStyle();

    static QString getButtonStyle();
    static QString getTextStyle();
    static QString getComboBoxStyle();
    static QString getCreateFieldActiveStyle();
    static QString getCreateFieldPassiveStyle();
    static QString getInputStyle();
    static QString getBGStyle();

    static void setFonts();
};

#endif // STYLEHANDLER_H
