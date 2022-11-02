#ifndef NEWSTAGGERING_H
#define NEWSTAGGERING_H

#include <QDialog>
#include <QSqlDatabase>
#include "mainwindow.h"

namespace Ui {
class NewStaggering;
}

class NewStaggering : public QDialog
{
    Q_OBJECT

public:
    explicit NewStaggering(QWidget *parent = nullptr,MainWindow *dashboard=nullptr);
    ~NewStaggering();

private slots:
    void on_levelChoice_currentTextChanged(const QString &level);

    void on_categoryChoice_currentTextChanged(const QString &category);

    void on_saveStaggeringbtn_accepted();

private:
    Ui::NewStaggering *ui;
    QSqlDatabase mDatabase;
    MainWindow *dashboard ;
};

#endif // NEWSTAGGERING_H
