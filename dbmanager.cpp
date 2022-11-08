#include "dbmanager.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <QSqlError>

#define ACCESS "DRIVER={Microsoft Access Driver (*.mdb)};\
                FIL={MS Access};\
                DBQ=C:\\Users\\RASOLOMANANA Olivier\\Documents\\Eni-Registration.mdb"

DbManager::DbManager(QWidget *parent)
{
    this->parent = parent;
    openDb();
}

void DbManager::openDb() {
    myDatabase.setDatabaseName(ACCESS);
    if(!myDatabase.open()){
        QMessageBox::critical(parent,"Error",myDatabase.lastError().text());
    }
};

QSqlDatabase DbManager::getDb() {
    return myDatabase;
}
