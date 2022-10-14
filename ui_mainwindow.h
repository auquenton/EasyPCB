/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *picture;
    QLabel *InputImgBox;
    QLabel *OutputImgBox;
    QGroupBox *Log;
    QTextBrowser *LogBox;
    QGroupBox *groupBox;
    QPushButton *select_button;
    QPushButton *UpLoad;
    QPushButton *BatchButton;
    QPushButton *CleanLog;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 580);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        picture = new QGroupBox(centralwidget);
        picture->setObjectName(QString::fromUtf8("picture"));
        picture->setGeometry(QRect(30, 20, 740, 340));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(10);
        picture->setFont(font);
        InputImgBox = new QLabel(picture);
        InputImgBox->setObjectName(QString::fromUtf8("InputImgBox"));
        InputImgBox->setGeometry(QRect(20, 20, 300, 300));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        font1.setItalic(true);
        InputImgBox->setFont(font1);
        InputImgBox->setAlignment(Qt::AlignCenter);
        OutputImgBox = new QLabel(picture);
        OutputImgBox->setObjectName(QString::fromUtf8("OutputImgBox"));
        OutputImgBox->setGeometry(QRect(420, 20, 300, 300));
        OutputImgBox->setFont(font1);
        OutputImgBox->setAlignment(Qt::AlignCenter);
        Log = new QGroupBox(centralwidget);
        Log->setObjectName(QString::fromUtf8("Log"));
        Log->setGeometry(QRect(30, 370, 520, 180));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        Log->setFont(font2);
        LogBox = new QTextBrowser(Log);
        LogBox->setObjectName(QString::fromUtf8("LogBox"));
        LogBox->setGeometry(QRect(10, 20, 500, 150));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(569, 370, 201, 180));
        groupBox->setFont(font2);
        select_button = new QPushButton(groupBox);
        select_button->setObjectName(QString::fromUtf8("select_button"));
        select_button->setGeometry(QRect(20, 20, 160, 31));
        UpLoad = new QPushButton(groupBox);
        UpLoad->setObjectName(QString::fromUtf8("UpLoad"));
        UpLoad->setGeometry(QRect(20, 60, 160, 31));
        BatchButton = new QPushButton(groupBox);
        BatchButton->setObjectName(QString::fromUtf8("BatchButton"));
        BatchButton->setGeometry(QRect(20, 100, 160, 31));
        CleanLog = new QPushButton(groupBox);
        CleanLog->setObjectName(QString::fromUtf8("CleanLog"));
        CleanLog->setGeometry(QRect(20, 140, 160, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        picture->setTitle(QCoreApplication::translate("MainWindow", "Picture", nullptr));
        InputImgBox->setText(QCoreApplication::translate("MainWindow", "Input Image", nullptr));
        OutputImgBox->setText(QCoreApplication::translate("MainWindow", "OutPut Image", nullptr));
        Log->setTitle(QCoreApplication::translate("MainWindow", "Log", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Options", nullptr));
        select_button->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\345\233\276\347\211\207", nullptr));
        UpLoad->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\274\240", nullptr));
        BatchButton->setText(QCoreApplication::translate("MainWindow", "\346\211\271\345\244\204\347\220\206", nullptr));
        CleanLog->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\346\227\245\345\277\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
