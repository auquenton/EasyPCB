/********************************************************************************
** Form generated from reading UI file 'imgshowwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMGSHOWWINDOW_H
#define UI_IMGSHOWWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_ImgShowWindow
{
public:
    QLabel *ImgBox;

    void setupUi(QDialog *ImgShowWindow)
    {
        if (ImgShowWindow->objectName().isEmpty())
            ImgShowWindow->setObjectName(QString::fromUtf8("ImgShowWindow"));
        ImgShowWindow->resize(500, 500);
        ImgBox = new QLabel(ImgShowWindow);
        ImgBox->setObjectName(QString::fromUtf8("ImgBox"));
        ImgBox->setGeometry(QRect(11, 11, 478, 478));

        retranslateUi(ImgShowWindow);

        QMetaObject::connectSlotsByName(ImgShowWindow);
    } // setupUi

    void retranslateUi(QDialog *ImgShowWindow)
    {
        ImgShowWindow->setWindowTitle(QCoreApplication::translate("ImgShowWindow", "Dialog", nullptr));
        ImgBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ImgShowWindow: public Ui_ImgShowWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMGSHOWWINDOW_H
