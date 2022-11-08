#include "newstudent.h"
#include "ui_newstudent.h"
#include "mainwindow.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

NewStudent::NewStudent(QWidget *parent,MainWindow *dashboard) :
    QDialog(parent),
    ui(new Ui::NewStudent)
{
    ui->setupUi(this);
    this->dashboard = dashboard;
}

NewStudent::~NewStudent()
{
    delete ui;
}

void NewStudent::on_cancelBtn_clicked()
{
    this->close();
}


void NewStudent::on_saveBtn_clicked()
{
    QString level = ui->level->currentText();
    if(level.compare("Nouveau") == 0){
        level = "New";
    }

    QSqlQuery query;

    query.prepare("INSERT INTO "
                  "Student (firstName,  lastName,  cin,  phoneNumber,  cinDeliveranceDate,    "
                  "birthplace,  birthday,  fatherName,  motherName,  situation , category,  bac,  "
                  "inscriptionYear,   studyLevel, email)"
                  "VALUES  (:firstName, :lastName, :cin, :phoneNumber,  :cinDeliveranceDate,  "
                  ":birthplace, :birthday, :fatherName, :motherName, :situation, :category, "
                  ":bac, :inscriptionYear, :lvl,        :email)");
    query.bindValue(":firstName", ui->firstname->text());
    query.bindValue(":lastName",ui->lastname->text());
    query.bindValue(":cin",ui->cin->text());
    query.bindValue(":situation","invited");
    query.bindValue(":phoneNumber",ui->phone->text());
    query.bindValue(":cinDeliveranceDate", ui->deliveranceDate->text());
    query.bindValue(":category", ui->category->currentText());
    query.bindValue(":birthplace",  ui->birthplace->text());
    query.bindValue(":birthday", ui->birthday->text());
    query.bindValue(":motherName", ui->motherName->text());
    query.bindValue(":fatherName", ui->fatherName->text());
    query.bindValue(":bac",  ui->bac->currentText());
    query.bindValue(":inscriptionYear",  ui->inscriptionYear->text());
    query.bindValue(":lvl",level );
    query.bindValue(":email",  ui->email->text());

    if(query.exec()){
        QMessageBox::information(this, "Succes", "Vous avez enregistee les donnees avec succes !");
        this->dashboard->refreshAllTables();
     }else{
        QMessageBox::critical(this, "Echec", "L'enregistrement a echoue !");
    }
}

