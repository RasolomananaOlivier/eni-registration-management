#include "changestaggering.h"
#include "ui_changestaggering.h"

ChangeStaggering::ChangeStaggering(QWidget *parent,MainWindow *dashboard,map<QString,QString> data) :
    QDialog(parent),
    ui(new Ui::ChangeStaggering)
{
    ui->setupUi(this);

    this->dashboard = dashboard;
    this->data = data;

    ui->fullname->setText( data["fullname"] );
    ui->remain->setText(data["remainAmount"] +  " Ar");
    studentId = data["studentId"];
}

ChangeStaggering::~ChangeStaggering()
{
    delete ui;
}

void ChangeStaggering::saveChange(){
    QSqlQuery query;
    query.prepare("UPDATE Staggering "
                  "SET totalPaid=:paid "
                  "WHERE studentId=:studentId");
    query.bindValue(":paid", data["amountPaid"].toInt() + ui->amount->text().toInt());
    query.bindValue(":studentId",studentId );

    if(query.exec()){
        this->dashboard->refreshStaggeringTable();

        if(isAllAmountPaid(studentId)){
            QString currentStudyLevel,studentCategory;

            QSqlQuery qry;
            qry.prepare("SELECT category,studyLevel FROM Student "
                        "WHERE studentId=:id");
            qry.bindValue(":id", studentId);

            if(qry.exec()){
                while(qry.next()){
                    qDebug() << qry.value(0).toString();
                    studentCategory = qry.value(0).toString();
                    currentStudyLevel = qry.value(1).toString();
                }
            }else{
                qDebug() << "inside isallamountpaid query not executed";
            }


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

            if(studentCategory.compare("Pro") == 0) {
                if(currentStudyLevel.compare("New") == 0){
                    this->dashboard->admitStudent(studentCategory,nextStudyLevel,studentId);
                    this->close();
                }else{

                    CategoryChoice *categoryDialog;
                    categoryDialog = new CategoryChoice(nullptr,this);
                    categoryDialog->show();
                }

            }else{
                this->dashboard->admitStudent(studentCategory,nextStudyLevel,studentId);
                this->close();
            }
        }
    }else{
        QMessageBox::information(this,"Echec", "Une erreur est survenue durant la requête !");
    }
}

bool ChangeStaggering::isAllAmountPaid(QString studentId){
    bool result = false;
    QSqlQuery query;
    query.prepare("SELECT totalAmount, totalPaid FROM Staggering "
                  "WHERE studentId=:id");
    query.bindValue(":id", studentId);

    if(query.exec()){
        while(query.next()){
            int totalAmount = query.value(0).toInt();
            int totalPaid = query.value(1).toInt();

            if(totalAmount == totalPaid)
                result = true;
        }
    }else{
        qDebug() << query.lastError().text();
        QMessageBox::information(this,"Echec", "Une erreur est survenue durant la requête !");
    }

    return result;
}
void ChangeStaggering::on_pushButton_clicked()
{
    saveChange();
}


void ChangeStaggering::on_pushButton_2_clicked()
{
    this->close();
}

