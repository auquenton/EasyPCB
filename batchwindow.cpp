/********************************************************************************

** author:	Qing
** Date:	2022-03-10
** desc:	批处理窗口实现

********************************************************************************/

#include "batchwindow.h"
#include "ui_batchwindow.h"
#include "imgshowwindow.h"
#include "ui_imgshowwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QString>
#include <QList>
#include <QProcess>
#include <QMessageBox>
#include <QImage>
#include <stdio.h>
#include <iostream>
#include <qdebug.h>
#include <string>

#pragma execution_character_set("utf-8")

using namespace std;

Batchwindow::Batchwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Batchwindow)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    this->setWindowTitle("批处理文件系统(By Qing)");
    ui->input_opendir->setIcon(QIcon(":/img/opendir.jpeg"));
    ui->save_opendir->setIcon(QIcon(":/img/opendir.jpeg"));
    connect(ui->input_opendir,SIGNAL(clicked(bool)),this,SLOT(SelectInputDir()));
    connect(ui->save_opendir,SIGNAL(clicked(bool)),this,SLOT(SelectOutputDir()));
    connect(ui->CleanLog,SIGNAL(clicked(bool)),this,SLOT(clean()));
    connect(ui->ResultShow,SIGNAL(clicked(bool)),this,SLOT(ShowResult()));
    connect(ui->Detection, SIGNAL(clicked(bool)), this, SLOT(BatchProcess()));
}

Batchwindow::~Batchwindow()
{
    delete ui;
}

void Batchwindow::SelectInputDir(){
    ui->ImagePathBox->clear();
    QString InputDirPath = QFileDialog::getExistingDirectory(this,"选择输入路径","./",QFileDialog::ShowDirsOnly);
    if(InputDirPath.isEmpty()){
        return ;
    }else{
        ui->InputEdit->setText(InputDirPath+'/');
        dir.setPath(InputDirPath);
        QStringList ImageList;
        ImageList<<"*.jpg"<<"*.png";
        dir.setNameFilters(ImageList);
        ImageCount = dir.count(); //图片个数
        if(ImageCount==0){
            ui->LogBox->append("<font color=\"#C0392B\">无图片，请检查输入路径</font>");
            ui->LogBox->append("-----------------------------");
            QMessageBox::warning(NULL,tr("提示"),tr("输入路径中无图片，请检查输入路径"),QMessageBox::Yes);
            ui->InputEdit->clear();
            return;
        }
        ui->LogBox->append("已选择输入路径:"+InputDirPath+'/');
        ui->LogBox->append("<font color=\"#7B68EE\">输入路径中共有"+QString::number(ImageCount,10)+"张图片</font>");
        ui->LogBox->append("-----------------------------");
        QString Imagename;
        for(int i=0;i<ImageCount;i++){
            Imagename = InputDirPath+"/"+dir[i];
            ui->ImagePathBox->addItem(Imagename);
        }
        return;
    }
}

void Batchwindow::SelectOutputDir(){
    QString OutputDirPath = QFileDialog::getExistingDirectory(this,"请选择进行保存的目录","./",QFileDialog::ShowDirsOnly);
    if(OutputDirPath.isEmpty()){
        return ;
    }else{
        ui->SaveEdit->setText(OutputDirPath+'/');
        ui->LogBox->append("已选择保存路径:"+OutputDirPath+'/');
        ui->LogBox->append("-----------------------------");
    }
}

void Batchwindow::clean(){
    ui->LogBox->clear();
    QMessageBox::information(NULL,tr("提示"),tr("已经成功清除日志信息!"),QMessageBox::Yes);
}

void Batchwindow::ShowResult(){
    QString ResultPath = ui->SaveEdit->text();
    ResultPath.replace("/", "\\");
    QDir *temp = new QDir;
    bool flag = temp->exists(ResultPath);
    if(flag){
        QProcess::startDetached("explorer " + ResultPath);
        ui->LogBox->append("已打开结果所在文件夹");
        ui->LogBox->append("-----------------------------");
    }else{
        ui->LogBox->append("<font color=\"#C0392B\">输入保存路径错误！请检查结果保存路径</font>");
        ui->LogBox->append("-----------------------------");
        QMessageBox::warning(NULL,tr("警告"),tr("请检查保存路径是否正确！"),QMessageBox::Yes);
        ui->SaveEdit->clear();
    }
}


void Batchwindow::on_ImagePathBox_itemDoubleClicked(QListWidgetItem *item)
{
    ImgShowWindow* imgsw = new ImgShowWindow(0,item);
    imgsw->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    imgsw->setWindowIcon(QIcon(":/img/opendir.jpeg"));
    ui->LogBox->append("<font color=\"#7B68EE\">查看文件"+item->text()+"</font>");
    ui->LogBox->append("-----------------------------");
    imgsw->exec();
}

void Batchwindow::BatchProcess() {
    QString SavePath = ui->SaveEdit->text();
    QString DirPath = ui->InputEdit->text();
    if (DirPath == "") {
        QMessageBox::warning(NULL, tr("警告"), tr("未输入图片文件夹路径，请检查输入路径！"), QMessageBox::Yes);
        return;
    }
    DirPath.replace("/", "\\");
    QDir* temp = new QDir;
    bool flag = temp->exists(DirPath);
    if(!flag){
        QMessageBox::warning(NULL, tr("警告"), tr("图片输入路径不存在！重新输入图片路径"), QMessageBox::Yes);
        ui->InputEdit->clear();
        return;
    }


    if (SavePath == "") {
        QMessageBox::warning(NULL, tr("警告"), tr("未输入保存路径，请检查保存路径是否正确！"), QMessageBox::Yes);
        return;
    }
    SavePath.replace("/", "\\");
    flag = temp->exists(SavePath);
    if(!flag){
        QMessageBox::warning(NULL, tr("警告"), tr("保存路径不存在！请检查保存路径"), QMessageBox::Yes);
        ui->SaveEdit->clear();
        return;
    }
    string str_save_path = SavePath.toStdString();

    //保存路径与输入路径都存在
    int row = 0;
    QString file_path;
    int cnt[7] = { 0,0,0,0,0,0,0 }; //缺陷计数初始化
    
    /*for (int i = 0; i < num; i++) {
        file_path = ui->ImagePathBox->item(i)->text();
        ui->LogBox->append(file_path);
        
    }*/
    //遍历List
    QString line;
    while (ui->ImagePathBox->count())
    {
        QListWidgetItem* item = ui->ImagePathBox->takeItem(row);//指定删除
        /*qDebug() << item->text();*/
        line = item->text().replace("/","\\");
        string str_input_path = line.toStdString();


        //删除List中的名称
        ui->ImagePathBox->removeItemWidget(item);
        delete item;
    }
}

