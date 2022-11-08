#include "categorychoice.h"
#include "ui_categorychoice.h"

#include "studentdetails.h"
#include "changestaggering.h"

CategoryChoice::CategoryChoice(QWidget *parent,StudentDetails *studentInfoDialog) :
    QDialog(parent),
    ui(new Ui::CategoryChoice)
{
    ui->setupUi(this);

    this->studentInfoDialog = studentInfoDialog;
}

CategoryChoice::CategoryChoice(QWidget *parent,ChangeStaggering *changeStaggeringDialog) :
    QDialog(parent),
    ui(new Ui::CategoryChoice)
{
    ui->setupUi(this);

    this->changeStaggeringDialog = changeStaggeringDialog;
}

CategoryChoice::~CategoryChoice()
{
    delete ui;
}

void CategoryChoice::on_srCheckBox_stateChanged(int arg1)
{
    if(arg1 == 2){
        isGb = false;
        ui->gbCheckBox->setChecked(false);
    }else {
        isGb = true;
        ui->gbCheckBox->setChecked(true);
    }

}


void CategoryChoice::on_gbCheckBox_stateChanged(int arg1)
{
    if(arg1 == 2){
        isGb = true;
        ui->srCheckBox->setChecked(false);
    }else {
        isGb = false;
        ui->srCheckBox->setChecked(true);
    }
}


void CategoryChoice::on_buttonBox_accepted()
{
    if(studentInfoDialog != nullptr){
        if(isGb) {
            this->studentInfoDialog->dashboard->admitStudent(
                        "Gb",
                        this->studentInfoDialog->nextStudyLevel,
                        this->studentInfoDialog->studentId
            );

            this->studentInfoDialog->close();
        }else{
            this->studentInfoDialog->dashboard->admitStudent(
                        "Sr",
                        this->studentInfoDialog->nextStudyLevel,
                        this->studentInfoDialog->studentId
            );

            this->studentInfoDialog->close();
        }
    }else{
        if(isGb) {
            this->changeStaggeringDialog->dashboard->admitStudent(
                        "Gb",
                        this->changeStaggeringDialog->nextStudyLevel,
                        this->changeStaggeringDialog->studentId
            );
//            QMessageBox::information(this,"Succès", "Changement effectué !");
//            this->changeStaggeringDialog->close();
        }else{
            this->changeStaggeringDialog->dashboard->admitStudent(
                        "Sr",
                        this->changeStaggeringDialog->nextStudyLevel,
                        this->changeStaggeringDialog->studentId
            );
            QMessageBox::information(this,"Succès", "Changement effectué !");
            this->changeStaggeringDialog->close();
        }
    }

}

