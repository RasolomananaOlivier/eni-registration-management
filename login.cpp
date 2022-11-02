#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "dbmanager.h"

#include <QSqlTableModel>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>



Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_clicked()
{
    DbManager dbManager = DbManager(this);
    QSqlDatabase db = dbManager.getDb();

    QString userName = ui->userName->text();
    QString password = ui->password->text();


    QSqlQuery query(QSqlDatabase::database("AppConnection"));

    query.prepare("SELECT * FROM User WHERE userName = :userName AND password = :password");
    query.bindValue(":userName",userName);
    query.bindValue(":password",password);

    bool isFound = false;
    if(query.exec()){
        while(query.next()){
            QString userNameFromDb = query.value(1).toString();
            QString passwordFromDb = query.value(2).toString();

            if(userName == userNameFromDb && password == passwordFromDb) {
                isFound = true;
            }
        }
        if(isFound){
            Login::hide();

            MainWindow *dashboard ;
            dashboard = new MainWindow(nullptr, userName);
            // Make the window fullscreen
            dashboard->setWindowState(Qt::WindowMaximized);
            dashboard->show();
        }else{
            QMessageBox::critical(this, "Connection echouee", "Votre nom d'utilisateur ou mot de passe est incorrect");
        }

     }else{
        QMessageBox::information(this, "Failed","Hello query failed") ;

    }

}

