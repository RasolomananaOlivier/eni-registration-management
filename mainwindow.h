#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QSqlTableModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_10_clicked();

    void on_addStudent_clicked();

    void on_l1ProInvitedTable_clicked(const QModelIndex &index);

    void on_inscriptionYear_currentTextChanged(const QString &arg1);

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

    QSqlDatabase mDatabase;


    void initInvitedStudentTable(QString year = "2022");
    void initAdmitedStudentTable(QString year = "2022");
};
#endif // MAINWINDOW_H
