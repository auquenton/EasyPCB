/********************************************************************************
** Form generated from reading UI file 'batchwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BATCHWINDOW_H
#define UI_BATCHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_Batchwindow
{
public:
    QGroupBox *groupBox;
    QPushButton *input_opendir;
    QListWidget *ImagePathBox;
    QLineEdit *InputEdit;
    QGroupBox *groupBox_2;
    QTextBrowser *LogBox;
    QGroupBox *groupBox_3;
    QPushButton *save_opendir;
    QLineEdit *SaveEdit;
    QGroupBox *groupBox_4;
    QPushButton *Detection;
    QPushButton *ResultShow;
    QPushButton *CleanLog;

    void setupUi(QDialog *Batchwindow)
    {
        if (Batchwindow->objectName().isEmpty())
            Batchwindow->setObjectName(QString::fromUtf8("Batchwindow"));
        Batchwindow->resize(720, 500);
        groupBox = new QGroupBox(Batchwindow);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 320, 480));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        groupBox->setFont(font);
        input_opendir = new QPushButton(groupBox);
        input_opendir->setObjectName(QString::fromUtf8("input_opendir"));
        input_opendir->setGeometry(QRect(10, 20, 60, 30));
        ImagePathBox = new QListWidget(groupBox);
        ImagePathBox->setObjectName(QString::fromUtf8("ImagePathBox"));
        ImagePathBox->setGeometry(QRect(10, 60, 290, 410));
        InputEdit = new QLineEdit(groupBox);
        InputEdit->setObjectName(QString::fromUtf8("InputEdit"));
        InputEdit->setGeometry(QRect(70, 20, 230, 30));
        groupBox_2 = new QGroupBox(Batchwindow);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(360, 10, 340, 331));
        groupBox_2->setFont(font);
        LogBox = new QTextBrowser(groupBox_2);
        LogBox->setObjectName(QString::fromUtf8("LogBox"));
        LogBox->setGeometry(QRect(10, 20, 320, 301));
        groupBox_3 = new QGroupBox(Batchwindow);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(360, 340, 341, 61));
        groupBox_3->setFont(font);
        save_opendir = new QPushButton(groupBox_3);
        save_opendir->setObjectName(QString::fromUtf8("save_opendir"));
        save_opendir->setGeometry(QRect(10, 20, 60, 30));
        SaveEdit = new QLineEdit(groupBox_3);
        SaveEdit->setObjectName(QString::fromUtf8("SaveEdit"));
        SaveEdit->setGeometry(QRect(70, 20, 260, 30));
        groupBox_4 = new QGroupBox(Batchwindow);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(360, 400, 341, 91));
        groupBox_4->setFont(font);
        Detection = new QPushButton(groupBox_4);
        Detection->setObjectName(QString::fromUtf8("Detection"));
        Detection->setGeometry(QRect(10, 30, 81, 31));
        ResultShow = new QPushButton(groupBox_4);
        ResultShow->setObjectName(QString::fromUtf8("ResultShow"));
        ResultShow->setGeometry(QRect(130, 30, 81, 31));
        CleanLog = new QPushButton(groupBox_4);
        CleanLog->setObjectName(QString::fromUtf8("CleanLog"));
        CleanLog->setGeometry(QRect(250, 30, 81, 31));

        retranslateUi(Batchwindow);

        QMetaObject::connectSlotsByName(Batchwindow);
    } // setupUi

    void retranslateUi(QDialog *Batchwindow)
    {
        Batchwindow->setWindowTitle(QCoreApplication::translate("Batchwindow", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Batchwindow", "InputDir", nullptr));
        input_opendir->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("Batchwindow", "Log", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Batchwindow", "SaveDir", nullptr));
        save_opendir->setText(QString());
        groupBox_4->setTitle(QCoreApplication::translate("Batchwindow", "Button", nullptr));
        Detection->setText(QCoreApplication::translate("Batchwindow", "\346\243\200\346\265\213", nullptr));
        ResultShow->setText(QCoreApplication::translate("Batchwindow", "\347\273\223\346\236\234", nullptr));
        CleanLog->setText(QCoreApplication::translate("Batchwindow", "\346\270\205\347\251\272\346\227\245\345\277\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Batchwindow: public Ui_Batchwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BATCHWINDOW_H
