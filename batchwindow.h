#ifndef BATCHWINDOW_H
#define BATCHWINDOW_H

#include <windows.h>
#include <QDialog>
#include <QString>
#include <QDir>
#include <QListWidgetItem>


namespace Ui {
class Batchwindow;
}

class Batchwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Batchwindow(QWidget *parent = nullptr);
    ~Batchwindow();

private slots:
    void SelectInputDir();
    void SelectOutputDir();
    void clean();
    void ShowResult();
    void on_ImagePathBox_itemDoubleClicked(QListWidgetItem *item);
    void BatchProcess();

private:
    Ui::Batchwindow *ui;
    QDir dir;
    int ImageCount;
};


#endif // BATCHWINDOW_H
