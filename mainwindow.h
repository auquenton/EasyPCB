#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "batchwindow.h"
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString imagepath = "";


private slots:
    void OpenImg();
    void OpenNewWindow();
    void LogClean();
    void Inference();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
