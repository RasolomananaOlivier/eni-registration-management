#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class Login;
}

class QSqlTableModel;

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_login_clicked();

private:
    Ui::Login *ui;

    QSqlTableModel *userModel;
    QSqlDatabase mDatabase;

};

#endif // LOGIN_H
