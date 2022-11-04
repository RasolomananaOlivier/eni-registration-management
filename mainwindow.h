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

#include <map>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


QT_CHARTS_USE_NAMESPACE

using namespace std;

class QSqlTableModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,QString username = "");
    ~MainWindow();
    void refreshAllTables();
    void refreshStaggeringTable();

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


    QSqlTableModel *l1ProUnpaidModel,*l1IgUnpaidModel,
        *l2GbUnpaidModel,*l2SrUnpaidModel,
        *l3GbUnpaidModel, *l3SrUnpaidModel,
        *m1GbUnpaidModel, *m1SrUnpaidModel,
        *m2GbUnpaidModel,*m2SrUnpaidModel;

    QSqlTableModel *staggeringModel;

    QSqlDatabase mDatabase;


    void initInvitedStudentTable(QString year = "2022");
    void initAdmitedStudentTable(QString year = "2022");
    void initUnpaidStudentTable(QString year="2022");
    void initStaggeringTable(QString year="2022");

    void hideColumn(QTableView *tableView);
    void setupTableModelRelation(QSqlTableModel *model, QTableView *tableView,QString dbTableName,QString studyLevel,QString category, QString year,QString situation );

    void openStudentInfo(const QModelIndex &index);

    QLineSeries *amountSeries;
    QChartView *amountChartView;
    QDateTimeAxis *amountAxisX= new QDateTimeAxis();


    void displayChart();
    void createBarChart(QWidget *parent,QList<int> data, QString chartTitle,QList<int> yAxisRange);

    void createLineSeries(QWidget *parent,  QList<QPointF> points,QString chartTitle,QString studyLevel);
    void updateLineSeries( QList<QPointF> points,QString studyLevel);
    QList<QPointF> getDataOfQLineSeries(QString studyLevel);
    map<QString, int> queryStudentInscriptionYear(QString studyLevel);


    void displayAdmitedChart();

};
#endif // MAINWINDOW_H



















