#ifndef IMGSHOWWINDOW_H
#define IMGSHOWWINDOW_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class ImgShowWindow;
}

class ImgShowWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ImgShowWindow(QWidget *parent = nullptr,QListWidgetItem* item = new QListWidgetItem());
    ~ImgShowWindow();

private:
    Ui::ImgShowWindow *ui;
};

#endif // IMGSHOWWINDOW_H
