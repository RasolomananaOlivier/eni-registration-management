#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::renderAllBarChart(QString year)
{

    // l1, l2 , l3, M1, M2
    map<QString, QList<int>> barChartData = getSituationCountBasedOnYear("2022");
    QList<int> invitedData = barChartData["invited"];
    QList<int> invitedDataRange = {
        0,
        Utility::max(invitedData.toVector()) + 5
    };

    QList<int> admitedData = barChartData["admited"];
    QList<int> admitedDataRange = {
        0,
        Utility::max(admitedData.toVector()) + 5
    };

    QList<int> unpaidData = barChartData["unpaid"];
    QList<int> unpaidDataRange = {
        0,
        Utility::max(unpaidData.toVector()) + 5
    };

    // Bar chart for the total invited students
    createBarChart(invitedChartView,invitedData , newToM1ListLabel,
            "Total des étudiants invités à s'inscrire",invitedDataRange );

    // Bar chart for the total admited students
    createBarChart(admitedChartView, admitedData,l1ToM2ListLabel,
                   "Total des étudiants admis",  admitedDataRange);

    // Bar chart for the total students that have a problem of payment
    createBarChart(unpaidChartView, unpaidData, newToM1ListLabel,
                   "Total des étudiants qui ont un problème de paiement",unpaidDataRange);
}



void MainWindow::displayChart()
{
    renderAllBarChart("2022");

    createLineSeries(ui->amountChartView, getDataOfQLineSeries("L1"),
                     "Somme totale d'inscription au cours des années","L1");
}



void MainWindow::createBarChart(
        QChartView *chartView,QList<int> data,QStringList labels,
        QString chartTitle,QList<int> yAxisRange)
{
    QBarSet *sets[5];
    for (int i = 0 ; i < data.size() ; i++ ) {
        // Create a new set
        sets[i]= new QBarSet(labels[i]);
        // Add data to it
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

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(yAxisRange[0],yAxisRange[1]);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedSize(400, 300);
}


void MainWindow::createLineSeries(QWidget *parent, QList<QPointF> points, QString chartTitle,QString studyLevel)
{
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
    chart->setTitle("Somme totale d'inscription au cours des années ( " + studyLevel + " )");

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
    // ("2022", 235),("2023", 250),...
    map<QString, int> yearCountMap = queryStudentInscriptionYear(studyLevel);

    QList<QDateTime> dateTimeList;
    // => { QDateTime(2022,1,1) , QDateTime(2023,1,1) ,...}
    for (auto it : yearCountMap ) {
        QDateTime tmpDate;
        tmpDate.setDate(QDate(it.first.toInt(),1,1));
        dateTimeList.append(tmpDate);
    }

    QList<QPointF> points;
    for (auto it : yearCountMap ) {
        QDateTime d;
        d.setDate(QDate(it.first.toInt(),1,1));

        long amount;
        if(studyLevel.compare("L1") == 0){
            // it.second : 235 * 450.000ar
            amount = it.second * 450000;
        }else if(studyLevel.compare("L2") == 0 || studyLevel.compare("L3")){
            amount = it.second * 472500;
        }else{
            amount = it.second * 682500;
        }


        points.append(QPointF(d.toMSecsSinceEpoch(), amount));
    }

    return points;
}



