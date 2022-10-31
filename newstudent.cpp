#include "newstudent.h"
#include "ui_newstudent.h"

NewStudent::NewStudent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewStudent)
{
    ui->setupUi(this);
}

NewStudent::~NewStudent()
{
    delete ui;
}
