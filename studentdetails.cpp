#include "studentdetails.h"
#include "ui_studentdetails.h"
#include "categorychoice.h"

StudentDetails::StudentDetails(QWidget *parent,QList<QString> data, MainWindow *dashboard) :
    QDialog(parent),
    ui(new Ui::StudentDetails)
{
    ui->setupUi(this);

    this->data = data;
    this->parent = parent;
    this->dashboard = dashboard;

    studentId = data[0];
    studentCategory = data[14];

    ui->firstName->setText(data[1]);
    ui->lastName->setText(data[2]);
    ui->cin->setText(data[3]);
    ui->deliveranceDate->setText(data[4]);
    ui->duplicata->setText(data[5]);
    ui->duplicataDeliverance->setText(data[6]);
    ui->birthday->setText(data[7]);
    ui->birthplace->setText(data[8]);
    ui->phoneNumber->setText(data[9]);
    ui->motherName->setText(data[10]);
    ui->fatherName->setText(data[11]);
    ui->bac->setText(data[12]);
    ui->inscriptionYear->setText(data[15]);;
    ui->studyLevel->setText(data[16]);
    ui->email->setText(data[17]);

    QString studentSituation = data[13];
    currentStudyLevel = data[16];

    if(studentSituation.compare("invited") == 0) {
        ui->invitationBtn->hide();

        if(currentStudyLevel.compare("New") == 0){
            ui->admitedBtn->setText("Admettre en L1");
            nextStudyLevel = "L1";
        }else if(currentStudyLevel.compare("L1") == 0){
            ui->admitedBtn->setText("Admettre en L2");
            nextStudyLevel = "L2";
        }else if(currentStudyLevel.compare("L2") == 0){
            ui->admitedBtn->setText("Admettre en L3");
            nextStudyLevel = "L3";
        }else if(currentStudyLevel.compare("L3") == 0){
            ui->admitedBtn->setText("Admettre en M1");
            nextStudyLevel = "M1";
        }else {
            ui->admitedBtn->setText("Admettre en M2");
            nextStudyLevel = "M2";
        }
    }else if(studentSituation.compare("admited") == 0){
        if(currentStudyLevel.compare("New") == 0){
            nextStudyLevel = "L1";
        }else if(currentStudyLevel.compare("L1") == 0){
            nextStudyLevel = "L2";
        }else if(currentStudyLevel.compare("L2") == 0){
            nextStudyLevel = "L3";
        }else if(currentStudyLevel.compare("L3") == 0){
            nextStudyLevel = "M1";
        }else {
            nextStudyLevel = "M2";
        }
        ui->admitedBtn->hide();
        ui->invitationBtn->setText("Inviter à s'inscrire en "+ nextStudyLevel);
    }else {
        currentStudyLevel = data[16];
        ui->invitationBtn->hide();
    }
}

StudentDetails::~StudentDetails()
{
    delete ui;
}


void StudentDetails::on_admitedBtn_clicked()
{
    if(studentCategory.compare("Pro") == 0) {
        if(currentStudyLevel.compare("New") == 0){
            this->dashboard->admitStudent(studentCategory,nextStudyLevel,studentId);
        }else{

            CategoryChoice *categoryDialog;
            categoryDialog = new CategoryChoice(nullptr,this);
            categoryDialog->show();
        }

    }else{
        this->dashboard->admitStudent(studentCategory,nextStudyLevel,studentId);
    }
}

void StudentDetails::on_pushButton_clicked()
{
    this->close();
}


void StudentDetails::on_updateBtn_clicked()
{
    this->close();
    UpdateStudent *updateWindow = new UpdateStudent(parent,data,dashboard);
    updateWindow->show();
}

