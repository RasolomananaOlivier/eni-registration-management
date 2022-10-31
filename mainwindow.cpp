#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include <QSqlTableModel>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <newstudent.h>

#define ACCESS "DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=C:\\Users\\RASOLOMANANA Olivier\\Documents\\Eni-Registration.mdb"

QString style_active = "\
    background-color : rgb(35, 50, 60);\
    color : white;\
    border: none;\
    border-radius: 5px";
QString style_inactive = "\
    background-color :rgb(26, 32, 41);\
    color : white;\
    border: none;\
    border-radius: 5px";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(0);
    ui->pushButton->setStyleSheet(style_active);

    mDatabase = QSqlDatabase::addDatabase("QODBC");
    mDatabase.setDatabaseName(ACCESS);

    if(!mDatabase.open()) {
        QMessageBox::critical(this,"Error",mDatabase.lastError().text());
        return;
    }

    initInvitedStudentTable();
    initAdmitedStudentTable();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

    ui->pushButton->setStyleSheet(style_active);
    ui->pushButton_2->setStyleSheet(style_inactive);
    ui->pushButton_3->setStyleSheet(style_inactive);
    ui->pushButton_4->setStyleSheet(style_inactive);
    ui->pushButton_5->setStyleSheet(style_inactive);
    ui->pushButton_6->setStyleSheet(style_inactive);
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton_2->setStyleSheet(style_active);
    ui->pushButton->setStyleSheet(style_inactive);
    ui->pushButton_3->setStyleSheet(style_inactive);
    ui->pushButton_4->setStyleSheet(style_inactive);
    ui->pushButton_5->setStyleSheet(style_inactive);
    ui->pushButton_6->setStyleSheet(style_inactive);
}



void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->pushButton->setStyleSheet(style_inactive);
    ui->pushButton_2->setStyleSheet(style_inactive);
    ui->pushButton_3->setStyleSheet(style_active);
    ui->pushButton_4->setStyleSheet(style_inactive);
    ui->pushButton_5->setStyleSheet(style_inactive);
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->pushButton_4->setStyleSheet(style_active);
    ui->pushButton->setStyleSheet(style_inactive);
    ui->pushButton_2->setStyleSheet(style_inactive);
    ui->pushButton_3->setStyleSheet(style_inactive);
    ui->pushButton_5->setStyleSheet(style_inactive);
    ui->pushButton_6->setStyleSheet(style_inactive);
}



void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->pushButton_5->setStyleSheet(style_active);
    ui->pushButton->setStyleSheet(style_inactive);
    ui->pushButton_2->setStyleSheet(style_inactive);
    ui->pushButton_3->setStyleSheet(style_inactive);
    ui->pushButton_4->setStyleSheet(style_inactive);
    ui->pushButton_6->setStyleSheet(style_inactive);
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->pushButton_6->setStyleSheet(style_active);
    ui->pushButton->setStyleSheet(style_inactive);
    ui->pushButton_2->setStyleSheet(style_inactive);
    ui->pushButton_3->setStyleSheet(style_inactive);
    ui->pushButton_4->setStyleSheet(style_inactive);
    ui->pushButton_5->setStyleSheet(style_inactive);
}



void MainWindow::on_pushButton_10_clicked()
{
    MainWindow::close();

    Login *loginPage=0;
    loginPage = new Login();
    loginPage->show();

}


void MainWindow::on_addStudent_clicked()
{
    NewStudent *newStudentDialog;
    newStudentDialog = new NewStudent();
    newStudentDialog->show();
}


void MainWindow::on_l1ProInvitedTable_clicked(const QModelIndex &index)
{
    QMessageBox::information(this,"hey","");
}



void MainWindow::initInvitedStudentTable(QString year){
    QString yearFilter = " AND inscriptionYear = ";

    // L1 Pro invited
    l1ProModel = new QSqlTableModel(this);
    l1ProModel->setTable("Student");
    QString queryl1Pro =" level = 'L1' AND category = 'Pro' AND situation = 'invited' ";
    l1ProModel->setFilter(queryl1Pro+ yearFilter + year);
    l1ProModel->select();
    ui->l1ProInvitedTable->setModel(l1ProModel);

//    // L1 Ig invited
//    l1IgModel = new QSqlTableModel(this);
//    l1IgModel->setTable("Student");
//    QString queryL1Ig =" level = 'L1' AND category = 'Ig' AND situation = 'invited' ";
//    l1ProModel->setFilter(queryL1Ig + yearFilter + year );
//    l1IgModel->select();

//    ui->l1IgInvitedTable->setModel(l1IgModel);

//    // L2 Gb invited
//    l2GbModel = new QSqlTableModel(this);
//    l2GbModel->setTable("Student");
//    QString queryL2Gb =" level = 'L2' AND category = 'Gb' AND situation = 'invited' ";
//    l1ProModel->setFilter(queryL2Gb + yearFilter + year );
//    l2GbModel->select();

//    ui->l2GbInvitedTable->setModel(l2GbModel);

//    // L2 Sr invited
//    l2SrModel = new QSqlTableModel(this);
//    l2SrModel->setTable("Student");
//    QString queryL2Sr =" level = 'L2' AND category = 'Sr' AND situation = 'invited' ";
//    l1ProModel->setFilter(queryL2Sr + yearFilter + year );
//    l2SrModel->select();

//    ui->l2SrInvitedTable->setModel(l2SrModel);

//    // L3 Gb invited
//    l3GbModel = new QSqlTableModel(this);
//    l3GbModel->setTable("Student");
//    QString queryL3Gb =" level = 'L3' AND category = 'Gb' AND situation = 'invited' ";
//    l1ProModel->setFilter(queryL3Gb + yearFilter + year );
//    l3GbModel->select();

//    ui->l3GbInvitedTable->setModel(l3GbModel);

//    // L3 SR invited
//    l3SrModel = new QSqlTableModel(this);
//    l3SrModel->setTable("Student");
//    QString queryL3Sr =" level = 'L3' AND category = 'Sr' AND situation = 'invited' ";
//    l1ProModel->setFilter(queryL3Sr + yearFilter + year );
//    l3SrModel->select();

//    ui->l3SrInvitedTable->setModel(l3SrModel);

//    // TODOL
//    // M1 Gb invited
//    m1GbModel = new QSqlTableModel(this);
//    m1GbModel->setTable("Student");
//    m1GbModel->setFilter(" level = 'M1' AND category = 'Gb' AND situation = 'invited' ");
//    m1GbModel->select();

//    ui->m1GbInvitedTable->setModel(m1GbModel);

//    // M1 Sr invited
//    m1SrModel = new QSqlTableModel(this);
//    m1SrModel->setTable("Student");
//    m1SrModel->setFilter(" level = 'M1' AND category = 'Sr' AND situation = 'invited' ");
//    m1SrModel->select();

//    ui->m1SrInvitedTable->setModel(m1SrModel);


//    // M2 Gb invited
//    m2GbModel = new QSqlTableModel(this);
//    m2GbModel->setTable("Student");
//    m2GbModel->setFilter(" level = 'M2' AND category = 'Gb' AND situation = 'invited' ");
//    m2GbModel->select();

//    ui->m2GbInvitedTable->setModel(m2GbModel);

//    // M2 Sr invited
//    m2SrModel = new QSqlTableModel(this);
//    m2SrModel->setTable("Student");
//    m2SrModel->setFilter(" level = 'M2' AND category = 'Gb' AND situation = 'invited' ");
//    m2SrModel->select();

//    ui->m2SrInvitedTable->setModel(m2SrModel);
}

void MainWindow::initAdmitedStudentTable(QString year){
    l1ProAdmitedModel = new QSqlTableModel(this);
    l1ProAdmitedModel->setTable("Student");
    l1ProAdmitedModel->setFilter(" level = 'L1' AND category = 'Pro' AND situation = 'Admited' ");
    l1ProAdmitedModel->select();
    ui->l1ProAdmitedTable->setModel(l1ProAdmitedModel);

    l1IgAdmitedModel = new QSqlTableModel(this);
    l1IgAdmitedModel->setTable("Student");
    l1IgAdmitedModel->setFilter(" level = 'L1' AND category = 'Ig' AND situation = 'Admited' ");
    l1IgAdmitedModel->select();
    ui->l1IgAdmitedTable->setModel(l1IgAdmitedModel);

    l2GbAdmitedModel = new QSqlTableModel(this);
    l2GbAdmitedModel->setTable("Student");
    l2GbAdmitedModel->setFilter(" level = 'L2' AND category = 'Gb' AND situation = 'Admited' ");
    l2GbAdmitedModel->select();
    ui->l2GbAdmitedTable->setModel(l2GbAdmitedModel);

    l2SrAdmitedModel = new QSqlTableModel(this);
    l2SrAdmitedModel->setTable("Student");
    l2SrAdmitedModel->setFilter(" level = 'L2' AND category = 'Gb' AND situation = 'Admited' ");
    l2SrAdmitedModel->select();
    ui->l2SrAdmitedTable->setModel(l2SrAdmitedModel);

    l3GbAdmitedModel = new QSqlTableModel(this);
    l3GbAdmitedModel->setTable("Student");
    l3GbAdmitedModel->setFilter(" level = 'L3' AND category = 'Gb' AND situation = 'Admited' ");
    l3GbAdmitedModel->select();
    ui->l3GbAdmitedTable->setModel(l3GbAdmitedModel);

    l3SrAdmitedModel = new QSqlTableModel(this);
    l3SrAdmitedModel->setTable("Student");
    l3SrAdmitedModel->setFilter(" level = 'L3' AND category = 'Sr' AND situation = 'Admited' ");
    l3SrAdmitedModel->select();
    ui->l3SrAdmitedTable->setModel(l3SrAdmitedModel);

    l3SrAdmitedModel = new QSqlTableModel(this);
    l3SrAdmitedModel->setTable("Student");
    l3SrAdmitedModel->setFilter(" level = 'L3' AND category = 'Sr' AND situation = 'Admited' ");
    l3SrAdmitedModel->select();
    ui->l3SrAdmitedTable->setModel(l3SrAdmitedModel);

    m1GbAdmitedModel = new QSqlTableModel(this);
    m1GbAdmitedModel->setTable("Student");
    m1GbAdmitedModel->setFilter(" level = 'M1' AND category = 'Gb' AND situation = 'Admited' ");
    m1GbAdmitedModel->select();
    ui->m1GbAdmitedTable->setModel(m1GbAdmitedModel);

    m1SrAdmitedModel = new QSqlTableModel(this);
    m1SrAdmitedModel->setTable("Student");
    m1SrAdmitedModel->setFilter(" level = 'M1' AND category = 'Sr' AND situation = 'Admited' ");
    m1SrAdmitedModel->select();
    ui->m1SrAdmitedTable->setModel(m1SrAdmitedModel);

    m2GbAdmitedModel = new QSqlTableModel(this);
    m2GbAdmitedModel->setTable("Student");
    m2GbAdmitedModel->setFilter(" level = 'M2' AND category = 'Gb' AND situation = 'Admited' ");
    m2GbAdmitedModel->select();
    ui->m2GbAdmitedTable->setModel(m2GbAdmitedModel);

    m2SrAdmitedModel = new QSqlTableModel(this);
    m2SrAdmitedModel->setTable("Student");
    m2SrAdmitedModel->setFilter(" level = 'M2' AND category = 'Sr' AND situation = 'Admited' ");
    m2SrAdmitedModel->select();
    ui->m2SrAdmitedTable->setModel(m2SrAdmitedModel);
}


void MainWindow::on_inscriptionYear_currentTextChanged(const QString &arg1)
{
    qDebug() << arg1;
}

