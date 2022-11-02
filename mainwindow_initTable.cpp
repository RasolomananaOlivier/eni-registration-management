#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlError>

void MainWindow::initInvitedStudentTable(QString year){
    // L1 Pro invited
    setupTableModelRelation(l1ProModel, ui->l1ProInvitedTable, "Student", "L1","Pro",year,"invited");

    // L1 Ig invited
    setupTableModelRelation(l1IgModel, ui->l1IgInvitedTable, "Student", "L1","Ig",year,"invited");

    // L2 Gb invited
    setupTableModelRelation(l2GbModel, ui->l2GbInvitedTable, "Student", "L2","Gb",year,"invited");

    // L2 Sr invited
    setupTableModelRelation(l2SrModel, ui->l2SrInvitedTable, "Student", "L2","Sr",year,"invited");

    // L3 Gb invited
     setupTableModelRelation(l3GbModel, ui->l3GbInvitedTable, "Student", "L3","Gb",year,"invited");

    // L3 SR invited
     setupTableModelRelation(l3SrModel, ui->l3SrInvitedTable, "Student", "L3","Sr",year,"invited");

    // M1 Gb invited
      setupTableModelRelation(m1GbModel, ui->m1GbInvitedTable, "Student", "M1","Gb",year,"invited");

    // M1 Sr invited
      setupTableModelRelation(m1SrModel, ui->m1SrInvitedTable, "Student", "M1","Sr",year,"invited");

    // M2 Gb invited
      setupTableModelRelation(m2GbModel, ui->m2GbInvitedTable, "Student", "M2","Gb",year,"invited");

    // M2 Sr invited
      setupTableModelRelation(m2SrModel, ui->m2SrInvitedTable, "Student", "M2","Sr",year,"invited");
}



void MainWindow::initAdmitedStudentTable(QString year){

    l1ProAdmitedModel->setTable("Student");
    l1ProAdmitedModel->setFilter(" level = 'L1' AND category = 'Pro' AND situation = 'Admited' ");
    l1ProAdmitedModel->select();
    ui->l1ProAdmitedTable->setModel(l1ProAdmitedModel);


    l1IgAdmitedModel->setTable("Student");
    l1IgAdmitedModel->setFilter(" level = 'L1' AND category = 'Ig' AND situation = 'Admited' ");
    l1IgAdmitedModel->select();
    ui->l1IgAdmitedTable->setModel(l1IgAdmitedModel);

    l2GbAdmitedModel->setTable("Student");
    l2GbAdmitedModel->setFilter(" level = 'L2' AND category = 'Gb' AND situation = 'Admited' ");
    l2GbAdmitedModel->select();
    ui->l2GbAdmitedTable->setModel(l2GbAdmitedModel);


    l2SrAdmitedModel->setTable("Student");
    l2SrAdmitedModel->setFilter(" level = 'L2' AND category = 'Gb' AND situation = 'Admited' ");
    l2SrAdmitedModel->select();
    ui->l2SrAdmitedTable->setModel(l2SrAdmitedModel);


    l3GbAdmitedModel->setTable("Student");
    l3GbAdmitedModel->setFilter(" level = 'L3' AND category = 'Gb' AND situation = 'Admited' ");
    l3GbAdmitedModel->select();
    ui->l3GbAdmitedTable->setModel(l3GbAdmitedModel);


    l3SrAdmitedModel->setTable("Student");
    l3SrAdmitedModel->setFilter(" level = 'L3' AND category = 'Sr' AND situation = 'Admited' ");
    l3SrAdmitedModel->select();
    ui->l3SrAdmitedTable->setModel(l3SrAdmitedModel);


    l3SrAdmitedModel->setTable("Student");
    l3SrAdmitedModel->setFilter(" level = 'L3' AND category = 'Sr' AND situation = 'Admited' ");
    l3SrAdmitedModel->select();
    ui->l3SrAdmitedTable->setModel(l3SrAdmitedModel);


    m1GbAdmitedModel->setTable("Student");
    m1GbAdmitedModel->setFilter(" level = 'M1' AND category = 'Gb' AND situation = 'Admited' ");
    m1GbAdmitedModel->select();
    ui->m1GbAdmitedTable->setModel(m1GbAdmitedModel);


    m1SrAdmitedModel->setTable("Student");
    m1SrAdmitedModel->setFilter(" level = 'M1' AND category = 'Sr' AND situation = 'Admited' ");
    m1SrAdmitedModel->select();
    ui->m1SrAdmitedTable->setModel(m1SrAdmitedModel);


    m2GbAdmitedModel->setTable("Student");
    m2GbAdmitedModel->setFilter(" level = 'M2' AND category = 'Gb' AND situation = 'Admited' ");
    m2GbAdmitedModel->select();
    ui->m2GbAdmitedTable->setModel(m2GbAdmitedModel);


    m2SrAdmitedModel->setTable("Student");
    m2SrAdmitedModel->setFilter(" level = 'M2' AND category = 'Sr' AND situation = 'Admited' ");
    m2SrAdmitedModel->select();
    ui->m2SrAdmitedTable->setModel(m2SrAdmitedModel);
}



void MainWindow::initUnpaidStudentTable(QString year) {
    QString yearFilter = " AND inscriptionYear = ";

    // L1 Pro invited
    l1ProUnpaidModel = new QSqlTableModel(this);
    l1ProUnpaidModel->setTable("Student");
     QString queryl1Pro =" level = 'L1' AND category = 'Pro' AND situation = 'Unpaid' ";
    l1ProUnpaidModel->setFilter(queryl1Pro + yearFilter + year);
    l1ProUnpaidModel->select();
    ui->l1ProUnpaidTable->setModel(l1ProUnpaidModel);

//    l1IgAdmitedModel = new QSqlTableModel(this);
//    l1IgAdmitedModel->setTable("Student");
//    l1IgAdmitedModel->setFilter(" level = 'L1' AND category = 'Ig' AND situation = 'Admited' ");
//    l1IgAdmitedModel->select();
//    ui->l1IgAdmitedTable->setModel(l1IgAdmitedModel);

//    l2GbAdmitedModel = new QSqlTableModel(this);
//    l2GbAdmitedModel->setTable("Student");
//    l2GbAdmitedModel->setFilter(" level = 'L2' AND category = 'Gb' AND situation = 'Admited' ");
//    l2GbAdmitedModel->select();
//    ui->l2GbAdmitedTable->setModel(l2GbAdmitedModel);

//    l2SrAdmitedModel = new QSqlTableModel(this);
//    l2SrAdmitedModel->setTable("Student");
//    l2SrAdmitedModel->setFilter(" level = 'L2' AND category = 'Gb' AND situation = 'Admited' ");
//    l2SrAdmitedModel->select();
//    ui->l2SrAdmitedTable->setModel(l2SrAdmitedModel);

//    l3GbAdmitedModel = new QSqlTableModel(this);
//    l3GbAdmitedModel->setTable("Student");
//    l3GbAdmitedModel->setFilter(" level = 'L3' AND category = 'Gb' AND situation = 'Admited' ");
//    l3GbAdmitedModel->select();
//    ui->l3GbAdmitedTable->setModel(l3GbAdmitedModel);

//    l3SrAdmitedModel = new QSqlTableModel(this);
//    l3SrAdmitedModel->setTable("Student");
//    l3SrAdmitedModel->setFilter(" level = 'L3' AND category = 'Sr' AND situation = 'Admited' ");
//    l3SrAdmitedModel->select();
//    ui->l3SrAdmitedTable->setModel(l3SrAdmitedModel);

//    l3SrAdmitedModel = new QSqlTableModel(this);
//    l3SrAdmitedModel->setTable("Student");
//    l3SrAdmitedModel->setFilter(" level = 'L3' AND category = 'Sr' AND situation = 'Admited' ");
//    l3SrAdmitedModel->select();
//    ui->l3SrAdmitedTable->setModel(l3SrAdmitedModel);

//    m1GbAdmitedModel = new QSqlTableModel(this);
//    m1GbAdmitedModel->setTable("Student");
//    m1GbAdmitedModel->setFilter(" level = 'M1' AND category = 'Gb' AND situation = 'Admited' ");
//    m1GbAdmitedModel->select();
//    ui->m1GbAdmitedTable->setModel(m1GbAdmitedModel);

//    m1SrAdmitedModel = new QSqlTableModel(this);
//    m1SrAdmitedModel->setTable("Student");
//    m1SrAdmitedModel->setFilter(" level = 'M1' AND category = 'Sr' AND situation = 'Admited' ");
//    m1SrAdmitedModel->select();
//    ui->m1SrAdmitedTable->setModel(m1SrAdmitedModel);

//    m2GbAdmitedModel = new QSqlTableModel(this);
//    m2GbAdmitedModel->setTable("Student");
//    m2GbAdmitedModel->setFilter(" level = 'M2' AND category = 'Gb' AND situation = 'Admited' ");
//    m2GbAdmitedModel->select();
//    ui->m2GbAdmitedTable->setModel(m2GbAdmitedModel);

//    m2SrAdmitedModel = new QSqlTableModel(this);
//    m2SrAdmitedModel->setTable("Student");
//    m2SrAdmitedModel->setFilter(" level = 'M2' AND category = 'Sr' AND situation = 'Admited' ");
//    m2SrAdmitedModel->select();
//    ui->m2SrAdmitedTable->setModel(m2SrAdmitedModel);
}


void MainWindow::initStaggeringTable(QString year){

    staggeringModel->setTable("Staggering");

    staggeringModel->select();

    ui->staggeringTable->setModel(staggeringModel);
}
