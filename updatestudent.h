#ifndef UPDATESTUDENT_H
#define UPDATESTUDENT_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class UpdateStudent;
}

class UpdateStudent : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateStudent(QWidget *parent = nullptr,QList<QString> data = {},MainWindow *dashboard = nullptr);
    ~UpdateStudent();

private slots:
    void on_saveBtn_clicked();

private:
    Ui::UpdateStudent *ui;
    QList<QString> data;
    QWidget *parent;
    MainWindow *dashboard ;
};

#endif // UPDATESTUDENT_H
