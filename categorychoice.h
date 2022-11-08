#ifndef CATEGORYCHOICE_H
#define CATEGORYCHOICE_H

#include <QDialog>
#include <QDebug>

#include "studentdetails.h"

namespace Ui {
class CategoryChoice;
}


class CategoryChoice : public QDialog
{
    Q_OBJECT

public:
    explicit CategoryChoice(QWidget *parent = nullptr,StudentDetails *studentInfo = nullptr);
    explicit CategoryChoice(QWidget *parent = nullptr,ChangeStaggering *changeStaggeringDialog = nullptr);
    ~CategoryChoice();

private slots:
    void on_srCheckBox_stateChanged(int arg1);

    void on_gbCheckBox_stateChanged(int arg1);

    void on_buttonBox_accepted();

private:
    Ui::CategoryChoice *ui;
    QWidget *parent;

    StudentDetails *studentInfoDialog;
    ChangeStaggering *changeStaggeringDialog;

    bool isGb = true;
};

#endif // CATEGORYCHOICE_H
