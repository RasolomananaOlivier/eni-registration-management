#include "studentinfo.h"
#include "ui_studentinfo.h"

studentInfo::studentInfo(QWidget *parent,QList<QString> data, MainWindow *dashboard) :
    QDialog(parent),
    ui(new Ui::studentInfo)
{
    ui->setupUi(this);
    this->data = data;
    this->parent = parent;
    this->dashboard = dashboard;

    studentId = data[0];

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
    ui->inscriptionYear->setText(data[14]);;
    ui->studyLevel->setText(data[15]);
    ui->email->setText(data[17]);

    QString studentSituation = data[13];

    for (int i = 0;  i < 18; i++ ) {
            qDebug() << data[i] << i;
    }

    if(studentSituation.compare("invited") != 0) {
        ui->admitedBtn->hide();
    }else {
        QString currentStudyLevel = data[16];

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

    }
}

studentInfo::~studentInfo()
{
    delete ui;
}

void studentInfo::on_updateBtn_clicked()
{
    this->close();
    UpdateStudent *updateWindow = new UpdateStudent(parent,data,dashboard);
    updateWindow->show();
}


void studentInfo::admitStudent() {
    QSqlQuery query;
    query.prepare("UPDATE Student "
                  "SET studyLevel=:studyLevel "
                  "WHERE studentId=:studentId");
    query.bindValue(":studyLevel", nextStudyLevel);
    query.bindValue(":studentId", studentId);

    if(query.exec()){
        QMessageBox::information(this, "Admission effectuée", "Admission de l'élève a bien été effectuée !");
        this->dashboard->refreshAllTables();
    }else{
        QMessageBox::warning(this, "Echec", "La requete a echouee !");
    }
}


void studentInfo::on_admitedBtn_clicked()
{
    admitStudent();
}

