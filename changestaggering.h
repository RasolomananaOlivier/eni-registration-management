#ifndef CHANGESTAGGERING_H
#define CHANGESTAGGERING_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>

#include "mainwindow.h"
#include "categorychoice.h"

namespace Ui {
class ChangeStaggering;
}

class ChangeStaggering : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeStaggering(QWidget *parent = nullptr,MainWindow *dashboard = nullptr,map<QString,QString> data ={});
    ~ChangeStaggering();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ChangeStaggering *ui;

    MainWindow *dashboard;
    map<QString,QString> data;

    void saveChange();
    bool isAllAmountPaid(QString studentId);

    QString nextStudyLevel,studentId;

    friend class CategoryChoice;
};

#endif // CHANGESTAGGERING_H
