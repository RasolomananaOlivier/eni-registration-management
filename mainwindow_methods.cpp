#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlTableModel>
#include <QDebug>

void MainWindow::refreshAllTables() {
    l1ProModel->select();
    // TODO: reselect all models
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
