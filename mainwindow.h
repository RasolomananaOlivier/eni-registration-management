#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QTableView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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

private:
    Ui::MainWindow *ui;

    QSqlTableModel *l1ProModel,*l1IgModel,
        *l2GbModel,*l2SrModel,
        *l3GbModel, *l3SrModel,
        *m1GbModel, *m1SrModel,
        *m2GbModel,*m2SrModel;

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
};
#endif // MAINWINDOW_H
