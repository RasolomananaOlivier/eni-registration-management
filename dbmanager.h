#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QWidget>
#include <QSqlDatabase>

#include "mainwindow.h"

class DbManager
{
public:
    DbManager(QWidget *parent = nullptr);
    DbManager(MainWindow *parent = nullptr);
    QSqlDatabase getDb();
private:
    QSqlDatabase myDatabase =  QSqlDatabase::addDatabase("QODBC","AppConnection");
    QWidget *parent;

    void openDb();
};

#endif // DBMANAGER_H
