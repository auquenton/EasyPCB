/********************************************************************************

** author:	Qing
** Date:	2022-03-10
** desc:	图片预览窗口实现

********************************************************************************/
#pragma execution_character_set("utf-8")
#include "imgshowwindow.h"
#include "ui_imgshowwindow.h"
#include <QString>
#include <QImage>
#include <QFileInfo>
#include <QtDebug>

ImgShowWindow::ImgShowWindow(QWidget *parent,QListWidgetItem* item) :
    QDialog(parent),
    ui(new Ui::ImgShowWindow)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    this->setWindowTitle(tr("图片预览"));
    setFixedSize(this->width(), this->height());
    QString ImgPath = item->text();
    QImage image;
    ImgPath.replace("/", "\\");
    if(ImgPath !=""){
        if(image.load(ImgPath))
        {
            ui->ImgBox->setPixmap(QPixmap::fromImage((image).scaled(ui->ImgBox->size())));
        }
        QFileInfo OpenFileInfo;
        OpenFileInfo = QFileInfo(ImgPath);
}
}

ImgShowWindow::~ImgShowWindow()
{
    delete ui;
}
