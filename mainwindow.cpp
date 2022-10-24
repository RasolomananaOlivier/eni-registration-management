#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"

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
//    ui->view->setCurrentIndex(0);
//    ui->stackedWidget->setCurrentWidget(0);
//    ui->pushButton->setStyleSheet(style_active);
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
    ui->pushButton_3->setStyleSheet(style_active);
    ui->pushButton->setStyleSheet(style_inactive);
    ui->pushButton_2->setStyleSheet(style_inactive);
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


void MainWindow::on_pushButton_9_clicked()
{
    ui->view->setCurrentIndex(1);
}

