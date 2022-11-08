#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QTableView>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>


#include <QtCharts/QLineSeries>
#include <QDateTimeAxis>
#include <QDateTime>


#include <QSqlQuery>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QTableWidgetItem>

#include <QSqlError>
#include "utility.h"

#include <map>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


QT_CHARTS_USE_NAMESPACE

using namespace std;

class QSqlTableModel;
class ChangeStaggering;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,QString username = "");
    ~MainWindow();
    void refreshAllTables();
    void refreshStaggeringTable();
    void admitStudent(QString cat,QString nextStudyLevel, QString studentId);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_10_clicked();

    void on_addStudent_clicked();

    void on_l1ProInvitedTable_clicked(const QModelIndex &index);

    void on_inscriptionYear_currentTextChanged(const QString &arg1);

    void on_add_staggering_clicked();

    void on_l1ProInvitedTable_doubleClicked(const QModelIndex &index);

    void on_l1IgUnpaidTable_doubleClicked(const QModelIndex &index);

    void on_l2GbUnpaidTable_doubleClicked(const QModelIndex &index);

    void on_l2SrUnpaidTable_doubleClicked(const QModelIndex &index);

    void on_l3GbUnpaidTable_doubleClicked(const QModelIndex &index);

    void on_l3SrUnpaidTable_doubleClicked(const QModelIndex &index);

    void on_m1GbUnpaidTable_doubleClicked(const QModelIndex &index);

    void on_m1SrUnpaidTable_doubleClicked(const QModelIndex &index);

    void on_m2GbUnpaidTable_doubleClicked(const QModelIndex &index);

    void on_m2SrUnpaidTable_doubleClicked(const QModelIndex &index);

    void on_l1IgInvitedTable_doubleClicked(const QModelIndex &index);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_newIgTable_doubleClicked(const QModelIndex &index);

    void on_staggeringTable_doubleClicked(const QModelIndex &index);

    void on_l1ProAdmitedTable_doubleClicked(const QModelIndex &index);

    void on_l1IgAdmitedTable_doubleClicked(const QModelIndex &index);

    void on_l2GbAdmitedTable_doubleClicked(const QModelIndex &index);

    void on_l2SrAdmitedTable_doubleClicked(const QModelIndex &index);

    void on_l3GbAdmitedTable_doubleClicked(const QModelIndex &index);

    void on_l3SrAdmitedTable_doubleClicked(const QModelIndex &index);

    void on_m1GbAdmitedTable_doubleClicked(const QModelIndex &index);

    void on_m1SrAdmitedTable_doubleClicked(const QModelIndex &index);

    void on_m2GbAdmitedTable_doubleClicked(const QModelIndex &index);

    void on_m2SrAdmitedTable_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    QSqlTableModel
        *newProModel, *newIgModel,
        *l1ProModel,*l1IgModel,
        *l2GbModel,*l2SrModel,
        *l3GbModel, *l3SrModel,
        *m1GbModel, *m1SrModel;

    QSqlTableModel *l1ProAdmitedModel,*l1IgAdmitedModel,
        *l2GbAdmitedModel,*l2SrAdmitedModel,
        *l3GbAdmitedModel, *l3SrAdmitedModel,
        *m1GbAdmitedModel, *m1SrAdmitedModel,
        *m2GbAdmitedModel,*m2SrAdmitedModel;


    QSqlTableModel
        *newProUnpaidModel, *newIgUnpaidModel,
        *l1ProUnpaidModel,*l1IgUnpaidModel,
        *l2GbUnpaidModel,*l2SrUnpaidModel,
        *l3GbUnpaidModel, *l3SrUnpaidModel,
        *m1GbUnpaidModel, *m1SrUnpaidModel;

    QSqlQueryModel *staggeringModel;

    QSqlDatabase mDatabase;


    void initInvitedStudentTable(QString year = "2022");
    void initAdmitedStudentTable(QString year = "2022");
    void initUnpaidStudentTable(QString year="2022");

    // Staggering methods
    void initStaggeringTable(QString year="2022");
    void admitStaggeringPaid();

    void hideColumn(QTableView *tableView);
    void setupTableModelRelation(QSqlTableModel *model, QTableView *tableView,QString dbTableName,QString studyLevel,QString category, QString year,QString situation );

    void openStudentInfo(const QModelIndex &index, QTableView *tableView);
    void openChangeStaggering(const QModelIndex &index);

    QLineSeries *amountSeries;

    // QChartView


    QChartView *invitedChartView;
    QChartView *admitedChartView;
    QChartView *unpaidChartView;


    QChartView *amountChartView;
    QDateTimeAxis *amountAxisX= new QDateTimeAxis();
    void createLineSeries(QWidget *parent,  QList<QPointF> points,QString chartTitle,QString studyLevel);
    void updateLineSeries( QList<QPointF> points,QString studyLevel);
    void displayChart();

    QList<QPointF> getDataOfQLineSeries(QString studyLevel);
    map<QString, int> queryStudentInscriptionYear(QString studyLevel);


    void createBarChart(QChartView *chartView,QList<int> data,QStringList labels, QString chartTitle,QList<int> yAxisRange);




    void displayAdmitedChart();


    void updateStudentsSituationToUnpaid();
    void isInscriptionDateEnd();


    QStringList newToM1ListLabel = {
        "Nouveaux Etudiants",
        "L1",
        "L2",
        "L3",
        "M1"
    };

    QStringList l1ToM2ListLabel = {
        "L1",
        "L2",
        "L3",
        "M1",
        "M2"
    };

    map<QString, int> getBarChartData(QStringList keys);
    map<QString, QList<int>> getSituationCountBasedOnYear(QString year);

    void renderAllBarChart(QString year);
    void setResumeStudentTable(QString year);
    void setResumeAmountTable(QString year);

};
#endif // MAINWINDOW_H



















