#include "newstaggering.h"
#include "ui_newstaggering.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include "dbmanager.h"


NewStaggering::NewStaggering(QWidget *parent,MainWindow *dashboard) :
    QDialog(parent),
    ui(new Ui::NewStaggering)
{
    ui->setupUi(this);
    this->dashboard = dashboard;

    DbManager dbManager = DbManager(this);
    QSqlDatabase db = dbManager.getDb();


    QSqlQuery query(QSqlDatabase::database("AppConnection"));

    query.prepare("SELECT * FROM Student WHERE studyLevel = 'L1' AND category = 'Pro'");

    if(query.exec()){
        while (query.next()) {
            QString firstname =  query.value(1).toString();
            QString lastname = query.value(2).toString();
            ui->studentCombobox->addItem(lastname + " " +firstname );
        }
    }else{
        qDebug() << query.lastError().text();
        QMessageBox::critical(this, "Error", "Query failed");
    }
}

NewStaggering::~NewStaggering()
{
    delete ui;
}


void NewStaggering::on_levelChoice_currentTextChanged(const QString &level)
{
    ui->studentCombobox->clear();
    QString category = ui->categoryChoice->currentText();

    QSqlQuery query(QSqlDatabase::database("AppConnection"));


    query.prepare("SELECT * FROM Student WHERE studyLevel = :studyLevel AND category = :category");
    query.bindValue(":studyLevel", level);
    query.bindValue(":category", category);

    if(query.exec()){
        while (query.next()) {
            QString firstname =  query.value(1).toString();
            QString lastname = query.value(2).toString();

            ui->studentCombobox->addItem(lastname + " " + firstname );
        }
    }else{
        qDebug() << query.lastError().text();
        QMessageBox::critical(this, "Error", "Query failed");
    }
}


void NewStaggering::on_categoryChoice_currentTextChanged(const QString &category)
{
    ui->studentCombobox->clear();
    QString level = ui->levelChoice->currentText();

    QSqlQuery query(QSqlDatabase::database("AppConnection"));

    query.prepare("SELECT * FROM Student WHERE studyLevel = :studyLevel AND category = :category");
    query.bindValue(":studyLevel", level);
    query.bindValue(":category", category);

    if(query.exec()){
        while (query.next()) {
            QString firstname =  query.value(1).toString();
            QString lastname = query.value(2).toString();

            ui->studentCombobox->addItem(lastname + " " +firstname );
        }
    }else{
        qDebug() << query.lastError().text();
        QMessageBox::critical(this, "Error", "Query failed");
    }
}


void NewStaggering::on_saveStaggeringbtn_accepted()
{
    QString fullname = ui->studentCombobox->currentText();
    QStringList list = fullname.split(" ");

    QString lastname = list.at(0).toLocal8Bit().constData();
    QString firstname = list.at(1).toLocal8Bit().constData();

    qDebug() << lastname << firstname ;

    QSqlQuery query;

    query.prepare("SELECT * FROM Student WHERE lastName = :last AND firstName = :first");
    query.bindValue(":last", lastname);
    query.bindValue(":first", firstname);

    if(query.exec()){
        bool isMatch = false;
        QString index;
        while (query.next() && !isMatch) {
            index =  query.value(0).toString();
            isMatch = true;
        }

        qDebug() << index;
        query.prepare("INSERT INTO Staggering (studentId, totalAmount, totalPaid, dueDate)"
                                    "VALUES    (:sId,      :tAmount,    0, :dDate)");
        query.bindValue(":sId", index);
        query.bindValue(":tAmount",ui->totalAmount->text());
        query.bindValue(":dDate", ui->dueDate->text());

        if(query.exec()){
            this->dashboard->refreshStaggeringTable();
            QMessageBox::information(this,"Succes", "Donnee enregistrer");
        }else{
            qDebug() << query.lastError().text();
            QMessageBox::critical(this, "Error", "Inserting failed");
        }
    }else{
        qDebug() << query.lastError().text();
        QMessageBox::critical(this, "Error", "Query failed");
    }
}




















