#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::displayChart() {

    // l1, l2 , l3, M1, M2
    QList<int> l1InvitedTotal = {800, 200, 150, 100, 80 };
    QList<int> l1AdmitedTotal = {150, 140, 120 , 100 , 70};
    QList<int> l1UnpaidTotal = {10, 14, 2 , 20 , 0};

    QList<int> range = {0,1000};

    // Bar chart for the total invited students
    createBarChart(ui->invitedChartView, l1InvitedTotal,
                   "Total des etudents invites a s'inscrire",range);

    // Bar chart for the total admited students
    createBarChart(ui->admitedChartView, l1AdmitedTotal,
                   "Total des etudents admis", range);

    // Bar chart for the total students that have a problem of payment
    createBarChart(ui->unpaidChartView, l1UnpaidTotal,
                   "Total des etudents qui ont un probleme de paiement", {0, 50});

    // Line chart for the amount
    createLineSeries(ui->amountChartView, getDataOfQLineSeries("L1") ,"Somme total d'inscription par an","L1");
}


void MainWindow::createBarChart(QWidget *parent,QList<int> data, QString chartTitle,QList<int> yAxisRange) {

    QBarSet *set0 = new QBarSet("L1");
    QBarSet *set1 = new QBarSet("L2");
    QBarSet *set2 = new QBarSet("L3");
    QBarSet *set3 = new QBarSet("M1");
    QBarSet *set4 = new QBarSet("M2");

    QBarSet *sets[5] = { set0, set1, set2, set3, set4 };

    for (int i = 0 ; i < data.size() ; i++ ) {
        sets[i]->append(data[i]);
    }

    QBarSeries *series = new QBarSeries();

    for (int i = 0 ; i < 5 ; i++ ) {
        series->append(sets[i]);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(chartTitle);
    chart->setAnimationOptions(QChart::SeriesAnimations);


    //    QStringList categories;
    //    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    //    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    //    axisX->append(categories);
    //    chart->addAxis(axisX, Qt::AlignBottom);
    //    series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(yAxisRange[0],yAxisRange[1]);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
    ////![5]

    //![6]
        QChartView *chartView = new QChartView(chart,parent);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setFixedSize(400, 300);
}


void MainWindow::createLineSeries(QWidget *parent, QList<QPointF> points, QString chartTitle,QString studyLevel) {

    for (int i = 0; i < points.size() ; i++ ) {
        this->amountSeries->append(points[i]);
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(this->amountSeries);
    chart->createDefaultAxes();
    chart->setTitle(chartTitle + " ( " + studyLevel + " )");

    amountChartView = new QChartView(chart,parent);
    amountChartView->setRenderHint(QPainter::Antialiasing);
    amountChartView->setFixedSize(700,500);


    amountAxisX->setFormat("yyyy");

    QDateTime minDate;
    minDate.setDate(QDate(2022,1,1));
    amountAxisX->setMin(minDate);

    amountChartView->chart()->setAxisX(amountAxisX,this->amountSeries);
    chart->setAnimationOptions(QChart::SeriesAnimations);
}


void MainWindow::updateLineSeries( QList<QPointF> points,QString studyLevel){
    QLineSeries *series = new QLineSeries();
//    amountChartView->chart()->removeAxis()

    for (int i = 0; i < points.size() ; i++ ) {
        series->append(points[i]);
    }

    // Create a new chart object
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Somme total d'inscription par an ( " + studyLevel + " )");

    // Reset the chart of the chart view
    amountChartView->setChart(chart);

    // Setup x axix
    QDateTimeAxis *axisX= new QDateTimeAxis();
    axisX->setFormat("yyyy");

    // Define the minimum date
    QDateTime minDate;
    minDate.setDate(QDate(2022,1,1));
    axisX->setMin(minDate);

    // Attach the axisX to the chart
    amountChartView->chart()->setAxisX(axisX, series);

    // Set the chartView to the new chart

    chart->setAnimationOptions(QChart::SeriesAnimations);

}

map<QString, int> MainWindow::queryStudentInscriptionYear(QString studyLevel){
    map<QString, int> yearCount;

    yearCount["2022"] = 0;
    yearCount["2023"] = 0;
    yearCount["2024"] = 0;
    yearCount["2025"] = 0;
    yearCount["2026"] = 0;
    yearCount["2027"] = 0;
    yearCount["2028"] = 0;
    yearCount["2029"] = 0;


    QSqlQuery query;
    query.prepare("SELECT inscriptionYear FROM Student WHERE situation='admited' AND studyLevel=:studyLevel");
    query.bindValue(":studyLevel", studyLevel);
    if(query.exec()){
        while (query.next()) {
            yearCount[query.value(0).toString()] += 1;
        }
    }else{
        qDebug() << "Query not running";
    }

    return yearCount;
}

QList<QPointF> MainWindow::getDataOfQLineSeries(QString studyLevel) {
    map<QString, int> yearCountMap = queryStudentInscriptionYear(studyLevel);

    QList<QDateTime> dateTimeList;

    for (auto it : yearCountMap ) {
        QDateTime tmpDate;
        tmpDate.setDate(QDate(it.first.toInt(),1,1));
        dateTimeList.append(tmpDate);
    }

    QList<QPointF> points;
    for (auto it : yearCountMap ) {
        QDateTime d;
        d.setDate(QDate(it.first.toInt(),1,1));

        long amount = it.second * 50000;

        points.append(QPointF(d.toMSecsSinceEpoch(), amount));
    }

    return points;
}



