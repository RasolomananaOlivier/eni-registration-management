#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlError>

void MainWindow::initInvitedStudentTable(QString year){

    // M2 Gb invited
      setupTableModelRelation(newProModel, ui->newProTable, "Student", "New","Pro",year,"invited");

    // M2 Sr invited
      setupTableModelRelation(newIgModel, ui->newIgTable, "Student", "New","Ig",year,"invited");

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
}



void MainWindow::initAdmitedStudentTable(QString year){
    // L1 Pro
    setupTableModelRelation(l1ProAdmitedModel, ui->l1ProAdmitedTable, "Student", "L1","Pro",year,"admited");

    // L1 Ig
    setupTableModelRelation(l1IgAdmitedModel, ui->l1IgAdmitedTable, "Student", "L1","Ig",year,"admited");

    // L2 Gb
    setupTableModelRelation(l2GbAdmitedModel, ui->l2GbAdmitedTable, "Student", "L2","Gb",year,"admited");

//    // L2 Sr
    setupTableModelRelation(l2SrAdmitedModel, ui->l2SrAdmitedTable, "Student", "L2","Sr",year,"admited");

//    // L3 Gb
     setupTableModelRelation(l3GbAdmitedModel, ui->l3GbAdmitedTable, "Student", "L3","Gb",year,"admited");

//    // L3 SR
     setupTableModelRelation(l3SrAdmitedModel, ui->l3SrAdmitedTable, "Student", "L3","Sr",year,"admited");

//    // M1 Gb
      setupTableModelRelation(m1GbAdmitedModel, ui->m1GbAdmitedTable, "Student", "M1","Gb",year,"admited");

//    // M1 Sr
      setupTableModelRelation(m1SrAdmitedModel, ui->m1SrAdmitedTable, "Student", "M1","Sr",year,"admited");

//    // M2 Gb
      setupTableModelRelation(m2GbAdmitedModel, ui->m2GbAdmitedTable, "Student", "M2","Gb",year,"admited");

//    // M2 Sr
      setupTableModelRelation(m2SrAdmitedModel, ui->m2SrAdmitedTable, "Student", "M2","Sr",year,"admited");
}



void MainWindow::initUnpaidStudentTable(QString year) {
    // L1 Pro
    setupTableModelRelation(l1ProUnpaidModel, ui->l1ProUnpaidTable, "Student", "L1","Pro",year,"unpaid");

    // L1 Ig
    setupTableModelRelation(l1IgUnpaidModel, ui->l1IgUnpaidTable, "Student", "L1","Ig",year,"unpaid");

    // L2 Gb
    setupTableModelRelation(l2GbUnpaidModel, ui->l2GbUnpaidTable, "Student", "L2","Gb",year,"unpaid");

     // L2 Sr
    setupTableModelRelation(l2SrUnpaidModel, ui->l2SrUnpaidTable, "Student", "L2","Sr",year,"unpaid");

     // L3 Gb
     setupTableModelRelation(l3GbUnpaidModel, ui->l3GbUnpaidTable, "Student", "L3","Gb",year,"unpaid");

      // L3 SR
     setupTableModelRelation(l3SrUnpaidModel, ui->l3SrUnpaidTable, "Student", "L3","Sr",year,"unpaid");

      // M1 Gb
     setupTableModelRelation(m1GbUnpaidModel, ui->m1GbUnpaidTable, "Student", "M1","Gb",year,"unpaid");

      // M1 Sr
     setupTableModelRelation(m1SrUnpaidModel, ui->m1SrUnpaidTable, "Student", "M1","Sr",year,"unpaid");

      // M2 Gb
     setupTableModelRelation(m2GbUnpaidModel, ui->m2GbUnpaidTable, "Student", "M2","Gb",year,"unpaid");

      // M2 Sr
     setupTableModelRelation(m2SrUnpaidModel, ui->m2SrUnpaidTable, "Student", "M2","Sr",year,"unpaid");
}


void MainWindow::initStaggeringTable(QString year){

    staggeringModel->setTable("Staggering");

    staggeringModel->select();

    ui->staggeringTable->setModel(staggeringModel);
}
