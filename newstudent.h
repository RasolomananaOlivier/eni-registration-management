#ifndef NEWSTUDENT_H
#define NEWSTUDENT_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class NewStudent;
}

class NewStudent : public QDialog
{
    Q_OBJECT

public:
    explicit NewStudent(QWidget *parent = nullptr,MainWindow *dashboard= nullptr);
    ~NewStudent();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::NewStudent *ui;
    MainWindow *dashboard;
};

#endif // NEWSTUDENT_H
