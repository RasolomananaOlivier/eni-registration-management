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

void NewStudent::on_buttonBox_accepted()
{
    QString firstName = ui->firstname->text();
    QString lastName = ui->lastname->text();
    QString level = ui->level->currentText();
    QString cin = ui->cin->text();
    QString cinDeliveranceDate = ui->deliveranceDate->text();
    QString birthday = ui->birthday->text();
    QString birthplace = ui->birthplace->text();
    QString phoneNumber = ui->phone->text();
    QString motherName= ui->motherName->text();
    QString fatherName = ui->fatherName->text();
    QString bac = ui->bac->currentText();
    QString category = ui->category->currentText();
    QString inscriptionYear = ui->inscriptionYear->text();


    QSqlQuery query;

    query.prepare("INSERT INTO Student (firstName,  lastName,  cin,  phoneNumber,  cinDeliveranceDate,    birthplace,  birthday,  fatherName,  motherName,  situation , category,  bac,  inscriptionYear,   studyLevel)"
                              "VALUES  (:firstName, :lastName, :cin, :phoneNumber,  :cinDeliveranceDate,  :birthplace, :birthday, :fatherName, :motherName, :situation, :category, :bac, :inscriptionYear, :lvl)");
    query.bindValue(":firstName", firstName);
    query.bindValue(":lastName",lastName);
    query.bindValue(":cin",cin);
    query.bindValue(":situation","invited");
    query.bindValue(":phoneNumber",phoneNumber);
    query.bindValue(":cinDeliveranceDate",cinDeliveranceDate);
    query.bindValue(":category", category);
    query.bindValue(":birthplace", birthplace);
    query.bindValue(":birthday", birthday);
    query.bindValue(":motherName",motherName);
    query.bindValue(":fatherName", fatherName);
    query.bindValue(":bac", bac);
    query.bindValue(":inscriptionYear", inscriptionYear);
    query.bindValue(":lvl", level);

    if(query.exec()){
        QMessageBox::information(this, "Succes", "Vous avez enregistee les donnees avec succes !");
        this->dashboard->refreshAllTables();
     }else{
        qDebug() << query.lastError().text();
        QMessageBox::critical(this, "Echec", "L'enregistrement a echoue !");
    }
}


void NewStudent::on_buttonBox_rejected()
{
    qDebug() << "Rejected";
}

