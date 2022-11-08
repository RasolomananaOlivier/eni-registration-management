#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include <QSqlTableModel>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <newstudent.h>

#include <QDateTime>
#include <QtCharts>

#include "newstaggering.h"
#include "ctime"


// Change the path to the correct path
#define ACCESS "DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=C:\\Users\\RASOLOMANANA Olivier\\Documents\\Eni-Registration.mdb"

QString style_active = "\
    background-color : rgb(35, 50, 60);\
    color : white;\
    border: none;\
    border-radius: 5px;\
    text-align: left; \
    padding : 10px 20px;";
QString style_inactive = "\
    background-color :rgb(26, 32, 41);\
    color : white;\
    border: none;\
    border-radius: 5px;\
    text-align: left;\
    padding : 10px 20px;";

MainWindow::MainWindow(QWidget *parent,QString username)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(0);
    ui->pushButton->setStyleSheet(style_active);
    ui->username_label->setText(username);

    ui->pageName->setText("Acceuil");

    mDatabase = QSqlDatabase::addDatabase("QODBC");

    mDatabase.setDatabaseName(ACCESS);

    if(!mDatabase.open()) {
        QMessageBox::critical(this,"Error",mDatabase.lastError().text());
        return;
    }

    // Invited model
    newProModel = new QSqlTableModel(this),
    newIgModel = new QSqlTableModel(this),
    l1ProModel = new QSqlTableModel(this),
    l1IgModel = new QSqlTableModel(this),
    l2GbModel = new QSqlTableModel(this),
    l2SrModel = new QSqlTableModel(this),
    l3GbModel = new QSqlTableModel(this),
    l3SrModel = new QSqlTableModel(this),
    m1GbModel = new QSqlTableModel(this),
    m1SrModel = new QSqlTableModel(this);


    // Admited model
    l1ProAdmitedModel = new QSqlTableModel(this),
            l1IgAdmitedModel = new QSqlTableModel(this),
            l2GbAdmitedModel = new QSqlTableModel(this),
            l2SrAdmitedModel = new QSqlTableModel(this),
            l3GbAdmitedModel = new QSqlTableModel(this),
            l3SrAdmitedModel = new QSqlTableModel(this),
            l3SrAdmitedModel = new QSqlTableModel(this),
            m1GbAdmitedModel = new QSqlTableModel(this),
            m1SrAdmitedModel = new QSqlTableModel(this),
            m2GbAdmitedModel = new QSqlTableModel(this),
            m2SrAdmitedModel = new QSqlTableModel(this);

    // Unpaid model
    newProUnpaidModel =  new QSqlTableModel(this),
            newIgUnpaidModel =  new QSqlTableModel(this),
            l1ProUnpaidModel = new QSqlTableModel(this),
            l1IgUnpaidModel = new QSqlTableModel(this),
            l2GbUnpaidModel = new QSqlTableModel(this),
            l2SrUnpaidModel = new QSqlTableModel(this),
            l3GbUnpaidModel = new QSqlTableModel(this),
            l3SrUnpaidModel = new QSqlTableModel(this),
            m1GbUnpaidModel = new QSqlTableModel(this),
            m1SrUnpaidModel = new QSqlTableModel(this);

    staggeringModel = new QSqlQueryModel(this);

    // Initialize QChartViews
    invitedChartView = new QChartView(ui->invitedChartView);
    admitedChartView = new QChartView(ui->admitedChartView);
    unpaidChartView = new QChartView(ui->unpaidChartView);

    // Init all table
    initInvitedStudentTable();
    initAdmitedStudentTable();
    initUnpaidStudentTable();
    initStaggeringTable();

    // ***
    amountSeries = new QLineSeries();
    displayChart();

    ui->resumeStudentTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->resumeAmountTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    isInscriptionDateEnd();
    setResumeStudentTable("2022");
    setResumeAmountTable("2022");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
     ui->pageName->setText("Acceuil");

    ui->pushButton->setStyleSheet(style_active);
    ui->pushButton_2->setStyleSheet(style_inactive);
    ui->pushButton_3->setStyleSheet(style_inactive);
    ui->pushButton_5->setStyleSheet(style_inactive);
    ui->pushButton_6->setStyleSheet(style_inactive);
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
     ui->pageName->setText("Invités");

    ui->pushButton_2->setStyleSheet(style_active);
    ui->pushButton->setStyleSheet(style_inactive);
    ui->pushButton_3->setStyleSheet(style_inactive);
    ui->pushButton_5->setStyleSheet(style_inactive);
    ui->pushButton_6->setStyleSheet(style_inactive);
}



void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->pageName->setText("Frais Non Payés");

    ui->pushButton->setStyleSheet(style_inactive);
    ui->pushButton_2->setStyleSheet(style_inactive);
    ui->pushButton_3->setStyleSheet(style_active);
    ui->pushButton_5->setStyleSheet(style_inactive);
    ui->pushButton_6->setStyleSheet(style_inactive);
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->pageName->setText("Admis");

    ui->pushButton_5->setStyleSheet(style_active);
    ui->pushButton->setStyleSheet(style_inactive);
    ui->pushButton_2->setStyleSheet(style_inactive);
    ui->pushButton_3->setStyleSheet(style_inactive);
    ui->pushButton_6->setStyleSheet(style_inactive);
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->pageName->setText("Demande d'échelonnement");

    ui->pushButton_6->setStyleSheet(style_active);
    ui->pushButton->setStyleSheet(style_inactive);
    ui->pushButton_2->setStyleSheet(style_inactive);
    ui->pushButton_3->setStyleSheet(style_inactive);
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

    // Pass the reference of the mainwindow object to student object
    newStudentDialog = new NewStudent(nullptr,this);
    newStudentDialog->show();
}


void MainWindow::on_l1ProInvitedTable_clicked(const QModelIndex &index)
{
//    QMessageBox::information(this,"hey","");
}



void MainWindow::on_inscriptionYear_currentTextChanged(const QString &selectedYear)
{
    initInvitedStudentTable(selectedYear);
    initAdmitedStudentTable(selectedYear);
    initUnpaidStudentTable(selectedYear);

    renderAllBarChart(selectedYear);
    setResumeStudentTable(selectedYear);
    setResumeAmountTable(selectedYear);
}



void MainWindow::on_add_staggering_clicked()
{
    NewStaggering *staggeringWindow;
    staggeringWindow = new NewStaggering(nullptr,this);
    staggeringWindow->show();
}



void MainWindow::on_l1ProInvitedTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index, ui->l1ProInvitedTable);
}

void MainWindow::on_l1IgUnpaidTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index, ui->l1IgUnpaidTable);
}


void MainWindow::on_l2GbUnpaidTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index, ui->l2GbUnpaidTable);
}


void MainWindow::on_l2SrUnpaidTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index, ui->l2SrUnpaidTable);
}


void MainWindow::on_l3GbUnpaidTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index, ui->l3GbUnpaidTable);
}


void MainWindow::on_l3SrUnpaidTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index,ui->l2SrUnpaidTable);
}


void MainWindow::on_m1GbUnpaidTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index, ui->m1GbUnpaidTable);
}


void MainWindow::on_m1SrUnpaidTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index, ui->m1SrUnpaidTable);
}


void MainWindow::on_m2GbUnpaidTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index,ui->m2GbAdmitedTable);
}


void MainWindow::on_m2SrUnpaidTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index,ui->m2SrAdmitedTable);
}


void MainWindow::on_l1IgInvitedTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index, ui->l1IgInvitedTable);
}


void MainWindow::on_comboBox_currentTextChanged(const QString &level)
{
    updateLineSeries(getDataOfQLineSeries(level), level);
}


void MainWindow::on_newIgTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index,ui->newIgTable);
}


void MainWindow::on_staggeringTable_doubleClicked(const QModelIndex &index)
{
    openChangeStaggering(index);
}

// Admited
void MainWindow::on_l1ProAdmitedTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index,ui->l1ProAdmitedTable);
}


void MainWindow::on_l1IgAdmitedTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index,ui->l1IgAdmitedTable);
}


void MainWindow::on_l2GbAdmitedTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index,ui->l2GbAdmitedTable);
}

void MainWindow::on_l2SrAdmitedTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index,ui->l2SrAdmitedTable);
}


void MainWindow::on_l3GbAdmitedTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index,ui->l3GbAdmitedTable);
}


void MainWindow::on_l3SrAdmitedTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index,ui->l3SrAdmitedTable);
}


void MainWindow::on_m1GbAdmitedTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index,ui->m1GbAdmitedTable);
}

void MainWindow::on_m1SrAdmitedTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index,ui->m1SrAdmitedTable);
}


void MainWindow::on_m2GbAdmitedTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index,ui->m2GbAdmitedTable);
}



void MainWindow::on_m2SrAdmitedTable_doubleClicked(const QModelIndex &index)
{
    openStudentInfo(index,ui->m2SrAdmitedTable);
}

