/********************************************************************************
** Form generated from reading UI file 'gamearea.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEAREA_H
#define UI_GAMEAREA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameArea
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QLCDNumber *minesLeft;
    QPushButton *switchFlag;
    QPushButton *smile;
    QLCDNumber *timePassed;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *backToMenuButton;
    QPushButton *saveButton;
    QGridLayout *playField;

    void setupUi(QWidget *GameArea)
    {
        if (GameArea->objectName().isEmpty())
            GameArea->setObjectName("GameArea");
        GameArea->resize(1435, 783);
        gridLayout = new QGridLayout(GameArea);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        minesLeft = new QLCDNumber(GameArea);
        minesLeft->setObjectName("minesLeft");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(minesLeft->sizePolicy().hasHeightForWidth());
        minesLeft->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(minesLeft);

        switchFlag = new QPushButton(GameArea);
        switchFlag->setObjectName("switchFlag");
        sizePolicy.setHeightForWidth(switchFlag->sizePolicy().hasHeightForWidth());
        switchFlag->setSizePolicy(sizePolicy);
        switchFlag->setMinimumSize(QSize(50, 50));

        horizontalLayout_3->addWidget(switchFlag);

        smile = new QPushButton(GameArea);
        smile->setObjectName("smile");
        sizePolicy.setHeightForWidth(smile->sizePolicy().hasHeightForWidth());
        smile->setSizePolicy(sizePolicy);
        smile->setMinimumSize(QSize(50, 50));

        horizontalLayout_3->addWidget(smile);

        timePassed = new QLCDNumber(GameArea);
        timePassed->setObjectName("timePassed");
        sizePolicy.setHeightForWidth(timePassed->sizePolicy().hasHeightForWidth());
        timePassed->setSizePolicy(sizePolicy);
        timePassed->setMinimumSize(QSize(0, 0));

        horizontalLayout_3->addWidget(timePassed);


        gridLayout->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        backToMenuButton = new QPushButton(GameArea);
        backToMenuButton->setObjectName("backToMenuButton");

        horizontalLayout_5->addWidget(backToMenuButton);

        saveButton = new QPushButton(GameArea);
        saveButton->setObjectName("saveButton");

        horizontalLayout_5->addWidget(saveButton);


        gridLayout->addLayout(horizontalLayout_5, 2, 0, 1, 1);

        playField = new QGridLayout();
        playField->setObjectName("playField");

        gridLayout->addLayout(playField, 1, 0, 1, 1);


        retranslateUi(GameArea);

        QMetaObject::connectSlotsByName(GameArea);
    } // setupUi

    void retranslateUi(QWidget *GameArea)
    {
        GameArea->setWindowTitle(QCoreApplication::translate("GameArea", "Form", nullptr));
        switchFlag->setText(QString());
        smile->setText(QString());
        backToMenuButton->setText(QCoreApplication::translate("GameArea", "Exit", nullptr));
        saveButton->setText(QCoreApplication::translate("GameArea", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameArea: public Ui_GameArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEAREA_H
