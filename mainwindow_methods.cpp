#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "studentdetails.h"
#include "changestaggering.h"

#include "string.h"

void MainWindow::refreshAllTables() {
    QSqlTableModel *invitedModels[10] = {
        newProModel,newIgModel,
        l1ProModel,l1IgModel,
        l2GbModel,l2SrModel,
        l3GbModel,l3SrModel,
        m1GbModel,m1SrModel,
    };
    QSqlTableModel *admitedModels[10] = {
        l1ProAdmitedModel,l1IgAdmitedModel,
        l2GbAdmitedModel,l2SrAdmitedModel,
        l3GbAdmitedModel,l3SrAdmitedModel,
        m1GbAdmitedModel,m1SrAdmitedModel,
        m2GbAdmitedModel,m2SrAdmitedModel
    };
    QSqlTableModel *unpaidModels[10] = {
        newProUnpaidModel,newIgUnpaidModel,
        l1ProUnpaidModel,l1IgUnpaidModel,
        l2GbUnpaidModel,l2SrUnpaidModel,
        l3GbUnpaidModel,l3SrUnpaidModel,
        m1GbUnpaidModel,m1SrUnpaidModel
    };

    for (int i = 0 ; i < 10 ; i++ ) {
        invitedModels[i]->select();
        admitedModels[i]->select();
        unpaidModels[i]->select();
    }

}

void MainWindow::refreshStaggeringTable(){
    staggeringModel->clear();
    initStaggeringTable();
}

void MainWindow::hideColumn(QTableView *tableView) {
    QList<int> blackListColumn = {0,4,5,6,7,8,10,11,13,14,15,16};

    for (int i = 0 ; i < blackListColumn.size() ; i++ ) {
        tableView->setColumnHidden(blackListColumn[i],true);
    }
}

void MainWindow::setupTableModelRelation(
        QSqlTableModel *model, QTableView *tableView,QString dbTableName,
        QString studyLevel, QString category, QString year, QString situation
) {

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

    // Hide unnecessary column
    hideColumn(tableView);

    // Expand the row to the available parent space
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


void MainWindow::openStudentInfo(const QModelIndex &index, QTableView *tableView){
    int row = index.row();

    QList<QString> data;

    for (int i = 0; i < 18; i++ ) {
        data.append(tableView->model()->data(tableView->model()->index(row, i),Qt::DisplayRole).toString());
    }

    StudentDetails *studentDetails = new StudentDetails(nullptr,data,this);
    studentDetails->show();
}


void MainWindow::openChangeStaggering(const QModelIndex &index){
    int row = index.row();

    map<QString,QString> data;
    QAbstractItemModel *model = ui->staggeringTable->model();

    int totalAmount = model->data(model->index(row,20),Qt::DisplayRole).toInt();
    int amountPaid = model->data(model->index(row,21),Qt::DisplayRole).toInt();

    data["studentId"] = model->data(model->index(row, 0),Qt::DisplayRole).toString();

    QString str;
    data["remainAmount"] = str.setNum(totalAmount - amountPaid);
    data["amountPaid"] = str.setNum(amountPaid);

    data["fullname"] = model->data(model->index(row,1),Qt::DisplayRole).toString()
            + " " + model->data(model->index(row,2),Qt::DisplayRole).toString();

    ChangeStaggering *studentDetails = new ChangeStaggering(nullptr,this,data);
    studentDetails->show();
}

void MainWindow::isInscriptionDateEnd()
{
    QDate endDate = ui->inscriptionEndDate->date();
    QDate currentDate = QDate::currentDate();

    if(endDate.operator<=(currentDate)){
        updateStudentsSituationToUnpaid();
    }
}

void MainWindow::updateStudentsSituationToUnpaid() {
    QSqlQuery query;
    query.prepare("UPDATE Student "
                  "SET situation='unpaid' "
                  "WHERE situation='invited'");

    if(query.exec()){
        QMessageBox::information(this,"Information", "L'inscription est terminée pour cette année, "
                                                     "les étudiants invités à s'inscrire et les demandes d'échelonnement sont désormais dans la "
                                                     "liste de problème de paiement");
        refreshAllTables();
        refreshStaggeringTable();
    }else {
        QMessageBox::critical(this,"Echec", "Une erreur interne est survenue");
    }
}

map<QString, QList<int>> MainWindow::getSituationCountBasedOnYear(QString year) {
    // ("invited" , { 15, 18 ,20, 10, 20 } )
    // ("admited" , { 15, 18 ,20, 10, 20 } )
    // ("unpaid" , { 15, 18 ,20, 10, 20 } )
    map<QString, QList<int>> result;

    //                         new,l1,l2,l3,M1
    QList<int> invitedCount = {0,  0, 0, 0, 0};
    QList<int> unpaidCount =  {0,  0, 0, 0, 0};

    //                        l1,l2,l3,m1,m2
    QList<int> admitedCount = {0,0, 0, 0, 0};



    QSqlQuery query;
    query.prepare("SELECT * FROM Student "
                  "WHERE inscriptionYear=:year");
    query.bindValue(":year", year);

    if(query.exec()){
        while(query.next()){
            QString situation = query.value(13).toString();
            QString studyLevel = query.value(16).toString();

            if(situation.compare("invited") == 0){
                if(studyLevel.compare("New") == 0){
                    invitedCount[0] += 1;
                }else if(studyLevel.compare("L1") == 0) {
                    invitedCount[1] += 1;
                }else if(studyLevel.compare("L2") == 0){
                    invitedCount[2] += 1;
                }else if(studyLevel.compare("L3") == 0) {
                    invitedCount[3] += 1;
                }else if(studyLevel.compare("M1") == 0){
                    invitedCount[4] += 1;
                }
            }else if(situation.compare("unpaid") == 0){
                if(studyLevel.compare("New") == 0){
                    unpaidCount[0] += 1;
                }else if(studyLevel.compare("L1") == 0) {
                    unpaidCount[1] += 1;
                }else if(studyLevel.compare("L2") == 0){
                    unpaidCount[2] += 1;
                }else if(studyLevel.compare("L3") == 0) {
                    unpaidCount[3] += 1;
                }else if(studyLevel.compare("M1") == 0){
                    unpaidCount[4] += 1;
                }
            }else {
                if(studyLevel.compare("L1") == 0){
                    admitedCount[0] += 1;
                }else if(studyLevel.compare("L2") == 0) {
                    admitedCount[1] += 1;
                }else if(studyLevel.compare("L3") == 0){
                    admitedCount[2] += 1;
                }else if(studyLevel.compare("M1") == 0) {
                    admitedCount[3] += 1;
                }else if(studyLevel.compare("M2") == 0){
                    admitedCount[4] += 1;
                }
            }


        }
    }else{
        qDebug() << "Query not executed";
    }

    result["invited"] = invitedCount;
    result["admited"] = admitedCount;
    result["unpaid"] = unpaidCount;

    return result;
}

void MainWindow::setResumeStudentTable(QString year) {
    map<QString, QList<int>> data  = getSituationCountBasedOnYear(year);
    QStringList situations = {"invited", "admited", "unpaid"};

    for (int row = 0; row < situations.size() ; row++ ) {
        for (int col = 0; col < 5 ; col++ ) {
            QString str;

            if(row == 1){
                qDebug() << col;
                ui->resumeStudentTable->setItem(1,col+1, new QTableWidgetItem( str.setNum(data[situations[1]][col]) ));
            }else{
                ui->resumeStudentTable->setItem(row,col, new QTableWidgetItem( str.setNum(data[situations[row]][col]) ));
            }
        }
    }
}


void MainWindow::setResumeAmountTable(QString year){
    int inscriptionCount = 0, l2AndL3 = 0, m1AndM2 = 0;

    QSqlQuery query;
    query.prepare("SELECT * FROM Student "
                  "WHERE inscriptionYear=:year AND situation='admited'");
    query.bindValue(":year", year);

    if(query.exec()){
        while(query.next()){
            QString lvl = query.value(16).toString();
            if(lvl.compare("L1") == 0){
                inscriptionCount++;
            }else{
                if(lvl.compare("L2") == 0 || lvl.compare("L3")){
                    l2AndL3++;
                }else if(lvl.compare("M2") == 0 || lvl.compare("M1")){
                    m1AndM2++;
                }
            }
        }
    }else{
        qDebug() << "Query failed";
    }

    map<QString, int> result;
    int inscriptionAmount = inscriptionCount * 450000;
    int reinscriptionAmount = l2AndL3 * 472500 + m1AndM2 * 682500;

    QString str;
    ui->resumeAmountTable->setItem(0,0,new QTableWidgetItem(str.setNum(inscriptionAmount)));
    ui->resumeAmountTable->setItem(0,1,new QTableWidgetItem(str.setNum(reinscriptionAmount)));

}


void MainWindow::admitStudent(QString cat,QString nextStudyLevel, QString studentId){
    QSqlQuery query;
    query.prepare("UPDATE Student "
                  "SET studyLevel=:studyLevel, category=:category,situation='admited' "
                  "WHERE studentId=:studentId");
    query.bindValue(":studyLevel", nextStudyLevel);
    query.bindValue(":studentId", studentId);
    query.bindValue(":category", cat);

    if(query.exec()){
        refreshAllTables();
        QMessageBox::information(this, "Admission effectuée", "Admission de l'élève a bien été effectuée !");

    }else{
        QMessageBox::warning(this, "Echec", "La requete a echouee !");
    }
}



















