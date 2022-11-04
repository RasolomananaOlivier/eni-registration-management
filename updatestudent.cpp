#include "updatestudent.h"
#include "ui_updatestudent.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>

UpdateStudent::UpdateStudent(QWidget *parent,QList<QString> data,MainWindow *dashboard) :
    QDialog(parent),
    ui(new Ui::UpdateStudent)
{
    ui->setupUi(this);
    this->data = data;
    this->parent = parent;
    this->dashboard = dashboard;

    ui->firstname->setText(data[1]);
    ui->lastname->setText(data[2]);
    ui->cin->setText(data[3]);
    ui->deliveranceDate->setDate(QDate::fromString(data[4]));
    ui->duplicata->setText(data[5]);
    ui->duplicataDate->setDate(QDate::fromString( data[6]));
    ui->birthday->setDate(QDate::fromString(data[7]));
    ui->birthplace->setText(data[8]);
    ui->phone->setText(data[9]);
    ui->motherName->setText(data[10]);
    ui->fatherName->setText(data[11]);
    ui->bac->setCurrentText(data[12]);
    ui->inscriptionYear->setValue(data[14].toInt());
    ui->level->setCurrentText(data[15]);
    ui->email->setText(data[17]);
    qDebug() << data[17];

}

UpdateStudent::~UpdateStudent()
{
    delete ui;
}

void UpdateStudent::on_saveBtn_clicked()
{
        QSqlQuery query;
        query.prepare("UPDATE Student "
                      "SET firstName=:firstName,  lastName=:lastName, "
                      "cin=:cin,  phoneNumber=:phoneNumber,  "
                      "cinDeliveranceDate=:cinDeliveranceDate,    birthplace=:birthplace,  "
                      "birthday=:birthday,  fatherName=:fatherName,  "
                      "motherName=:motherName,  situation=:situation , "
                      "category=:category,  bac=:bac,  "
                      "inscriptionYear=:inscriptionYear, "
                      "studyLevel=:studyLevel, email=:email "
                      "WHERE studentId=:studentId");

        query.bindValue(":firstName", ui->firstname->text());
        query.bindValue(":lastName", ui->lastname->text());
        query.bindValue(":cin",ui->cin->text());
        query.bindValue(":phoneNumber",ui->phone->text());

        query.bindValue(":cinDeliveranceDate", ui->deliveranceDate->text());
        query.bindValue(":birthplace",ui->birthplace->text());
        query.bindValue(":birthday",  ui->birthday->text());

        query.bindValue(":fatherName",ui->fatherName->text());
        query.bindValue(":motherName",ui->motherName->text());
        query.bindValue(":category", ui->category->currentText());
        query.bindValue(":bac", ui->bac->currentText());
        query.bindValue(":inscriptionYear", ui->inscriptionYear->text());

        query.bindValue(":studyLevel", ui->level->currentText());
        query.bindValue(":email",   ui->email->text());
        query.bindValue(":inscriptionYear", ui->inscriptionYear->text());
        query.bindValue(":situation", ui->situation->currentText());

        query.bindValue(":studentId", data[0]);


        if(query.exec()){
             QMessageBox::information(this,"Query Succed","Update Successful");
             this->dashboard->refreshAllTables();
        }else{
            QMessageBox::critical(this,"Query failed", query.lastError().text());
        }
}

