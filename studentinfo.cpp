#include "studentinfo.h"
#include "ui_studentinfo.h"
#include <QDebug>

studentInfo::studentInfo(QWidget *parent,QList<QString> data) :
    QDialog(parent),
    ui(new Ui::studentInfo)
{
    ui->setupUi(this);
    this->data = data;

    ui->firstName->setText(data[1]);
    ui->lastName->setText(data[2]);
    ui->cin->setText(data[3]);
    ui->deliveranceDate->setText(data[4]);
    ui->duplicata->setText(data[5]);
    ui->duplicataDeliverance->setText(data[6]);
    ui->birthday->setText(data[7]);
    ui->birthplace->setText(data[8]);
    ui->phoneNumber->setText(data[9]);
    ui->motherName->setText(data[10]);
    ui->fatherName->setText(data[11]);
    ui->bac->setText(data[12]);
    ui->inscriptionYear->setText(data[14]);;
    ui->studyLevel->setText(data[15]);
    ui->email->setText(data[16]);
}

studentInfo::~studentInfo()
{
    delete ui;
}
