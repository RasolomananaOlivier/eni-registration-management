#ifndef STUDENTDETAILS_H
#define STUDENTDETAILS_H

#include <QDialog>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>

#include "mainwindow.h"
#include "updatestudent.h"

class CategoryChoice;

namespace Ui {
class StudentDetails;
}

class StudentDetails : public QDialog
{
    Q_OBJECT

public:
    explicit StudentDetails(QWidget *parent = nullptr,QList<QString> data = {}, MainWindow *dashboard = nullptr);
    ~StudentDetails();

private slots:
    void on_admitedBtn_clicked();

    void on_pushButton_clicked();

    void on_updateBtn_clicked();

private:
    Ui::StudentDetails *ui;


    QWidget *parent;
    MainWindow *dashboard;

    QList<QString> data;
    QString nextStudyLevel;
    QString studentId;
    QString studentCategory;
    QString currentStudyLevel;

    void admitStudent(QString cat);

    // Make CategoryChoice class have access to private field
    friend class CategoryChoice;
};

#endif // STUDENTDETAILS_H
