#ifndef STUDENTINFO_H
#define STUDENTINFO_H

#include <QDialog>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>

#include "mainwindow.h"
#include "updatestudent.h"

namespace Ui {
class studentInfo;
}

class studentInfo : public QDialog
{
    Q_OBJECT

public:
    explicit studentInfo(QWidget *parent = nullptr, QList<QString> data = {}, MainWindow *dashboard = nullptr);
    ~studentInfo();

private slots:
    void on_updateBtn_clicked();

    void on_admitedBtn_clicked();

private:
    Ui::studentInfo *ui;
    QWidget *parent;
    MainWindow *dashboard;

    QList<QString> data;
    QString nextStudyLevel;
    QString studentId;

    void admitStudent();
};

#endif // STUDENTINFO_H
