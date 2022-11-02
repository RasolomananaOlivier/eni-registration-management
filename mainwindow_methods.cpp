#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlError>
#include "studentinfo.h"

void MainWindow::refreshAllTables() {
    QSqlTableModel *invitedModels[10] = {
          l1ProModel,l1IgModel,
        l2GbModel,l2SrModel,
        l3GbModel,l3SrModel,
        m1GbModel,m1SrModel,
        m2GbModel,m2SrModel
    };
    QSqlTableModel *admitedModels[10] = {
          l1ProAdmitedModel,l1IgAdmitedModel,
        l2GbAdmitedModel,l2SrAdmitedModel,
        l3GbAdmitedModel,l3SrAdmitedModel,
        m1GbAdmitedModel,m1SrAdmitedModel,
        m2GbAdmitedModel,m2SrAdmitedModel
    };

    for (int i = 0 ; i < 10 ; i++ ) {
        invitedModels[i]->select();
        admitedModels[i]->select();
    }

}

void MainWindow::refreshStaggeringTable(){
    qDebug() << "staggering refresh";
    staggeringModel->select();
}

void MainWindow::hideColumn(QTableView *tableView) {
    QList<int> blackListColumn = {0,4,5,6,7,8,10,11,13,14,15,16};

    for (int i = 0 ; i < blackListColumn.size() ; i++ ) {
        tableView->setColumnHidden(blackListColumn[i],true);
    }
}

void MainWindow::setupTableModelRelation(QSqlTableModel *model, QTableView *tableView,QString dbTableName, QString studyLevel, QString category, QString year, QString situation) {
    QString filterLvl ="studyLevel=";
    QString filterCat = " AND category=";
    QString filterSit = " AND situation=";
    QString filterYear = " AND inscriptionYear=";

    studyLevel.prepend('\'');
    studyLevel.append('\'');

    category.prepend('\'');
    category.append('\'');

    situation.prepend('\'');
    situation.append('\'');

    model->setTable(dbTableName);

    QString filter = filterLvl + studyLevel + filterCat + category + filterSit + situation + filterYear + year ;

    model->setFilter(filter);
    model->select();
    tableView->setModel(model);
    qDebug() << model->lastError().text();
    hideColumn(tableView);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


void MainWindow::openStudentInfo(const QModelIndex &index){
    int row = index.row();

    QList<QString> data;

    for (int i = 0; i < 18; i++ ) {
        data.append(ui->l1ProInvitedTable->model()->data(ui->l1ProInvitedTable->model()->index(row, i),Qt::DisplayRole).toString());
    }

    studentInfo *studentInfoDialog = new studentInfo(nullptr,data);
    studentInfoDialog->show();
}






















