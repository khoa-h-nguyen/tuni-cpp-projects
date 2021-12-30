/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *numberOfPlayers;
    QTextBrowser *inTurn;
    QPushButton *resetButton;
    QPushButton *startGameButton;
    QPushButton *closeButton;
    QLabel *inTurnLabel;
    QPushButton *turnCardButton;
    QLCDNumber *lcdTimerSec;
    QLabel *timer;
    QLabel *cardNumLabel;
    QLineEdit *lineEditCardNum;
    QPushButton *playerNumConfirmButton;
    QLCDNumber *lcdTimerMin;
    QSpinBox *spinBoxPlayerNum;
    QLabel *label;
    QLineEdit *lineEditPlayerNames;
    QPushButton *pauseButton;
    QLineEdit *lineEditStatusBar;
    QPushButton *helpButton;
    QMenuBar *menubar;
    QMenu *menuPairs_Memory_Game;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 557);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        numberOfPlayers = new QLabel(centralwidget);
        numberOfPlayers->setObjectName(QString::fromUtf8("numberOfPlayers"));
        numberOfPlayers->setGeometry(QRect(10, 43, 122, 28));
        inTurn = new QTextBrowser(centralwidget);
        inTurn->setObjectName(QString::fromUtf8("inTurn"));
        inTurn->setEnabled(true);
        inTurn->setGeometry(QRect(279, 210, 172, 31));
        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(10, 9, 85, 28));
        startGameButton = new QPushButton(centralwidget);
        startGameButton->setObjectName(QString::fromUtf8("startGameButton"));
        startGameButton->setGeometry(QRect(10, 176, 442, 28));
        closeButton = new QPushButton(centralwidget);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(365, 9, 85, 28));
        inTurnLabel = new QLabel(centralwidget);
        inTurnLabel->setObjectName(QString::fromUtf8("inTurnLabel"));
        inTurnLabel->setGeometry(QRect(230, 210, 43, 28));
        turnCardButton = new QPushButton(centralwidget);
        turnCardButton->setObjectName(QString::fromUtf8("turnCardButton"));
        turnCardButton->setGeometry(QRect(10, 248, 443, 28));
        lcdTimerSec = new QLCDNumber(centralwidget);
        lcdTimerSec->setObjectName(QString::fromUtf8("lcdTimerSec"));
        lcdTimerSec->setGeometry(QRect(152, 210, 71, 31));
        timer = new QLabel(centralwidget);
        timer->setObjectName(QString::fromUtf8("timer"));
        timer->setGeometry(QRect(10, 210, 92, 28));
        cardNumLabel = new QLabel(centralwidget);
        cardNumLabel->setObjectName(QString::fromUtf8("cardNumLabel"));
        cardNumLabel->setGeometry(QRect(10, 142, 110, 28));
        lineEditCardNum = new QLineEdit(centralwidget);
        lineEditCardNum->setObjectName(QString::fromUtf8("lineEditCardNum"));
        lineEditCardNum->setGeometry(QRect(134, 142, 317, 28));
        playerNumConfirmButton = new QPushButton(centralwidget);
        playerNumConfirmButton->setObjectName(QString::fromUtf8("playerNumConfirmButton"));
        playerNumConfirmButton->setGeometry(QRect(10, 108, 441, 28));
        lcdTimerMin = new QLCDNumber(centralwidget);
        lcdTimerMin->setObjectName(QString::fromUtf8("lcdTimerMin"));
        lcdTimerMin->setGeometry(QRect(70, 210, 71, 31));
        spinBoxPlayerNum = new QSpinBox(centralwidget);
        spinBoxPlayerNum->setObjectName(QString::fromUtf8("spinBoxPlayerNum"));
        spinBoxPlayerNum->setGeometry(QRect(140, 43, 43, 28));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(200, 43, 251, 28));
        lineEditPlayerNames = new QLineEdit(centralwidget);
        lineEditPlayerNames->setObjectName(QString::fromUtf8("lineEditPlayerNames"));
        lineEditPlayerNames->setGeometry(QRect(10, 75, 441, 28));
        pauseButton = new QPushButton(centralwidget);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
        pauseButton->setGeometry(QRect(127, 9, 85, 28));
        lineEditStatusBar = new QLineEdit(centralwidget);
        lineEditStatusBar->setObjectName(QString::fromUtf8("lineEditStatusBar"));
        lineEditStatusBar->setGeometry(QRect(10, 282, 443, 28));
        helpButton = new QPushButton(centralwidget);
        helpButton->setObjectName(QString::fromUtf8("helpButton"));
        helpButton->setGeometry(QRect(247, 9, 85, 28));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuPairs_Memory_Game = new QMenu(menubar);
        menuPairs_Memory_Game->setObjectName(QString::fromUtf8("menuPairs_Memory_Game"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuPairs_Memory_Game->menuAction());

        retranslateUi(MainWindow);
        QObject::connect(closeButton, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::close));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        numberOfPlayers->setText(QCoreApplication::translate("MainWindow", "Number of players", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        startGameButton->setText(QCoreApplication::translate("MainWindow", "Start Game", nullptr));
        closeButton->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        inTurnLabel->setText(QCoreApplication::translate("MainWindow", "In turn", nullptr));
        turnCardButton->setText(QCoreApplication::translate("MainWindow", "Turn Cards Back (end turn)", nullptr));
        timer->setText(QCoreApplication::translate("MainWindow", "Timer", nullptr));
        cardNumLabel->setText(QCoreApplication::translate("MainWindow", "Number of cards", nullptr));
        playerNumConfirmButton->setText(QCoreApplication::translate("MainWindow", "Confirm players number", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "(enter player names, seperate by \",\")", nullptr));
        pauseButton->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        helpButton->setText(QCoreApplication::translate("MainWindow", "Help", nullptr));
        menuPairs_Memory_Game->setTitle(QCoreApplication::translate("MainWindow", "Pairs Memory Game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
