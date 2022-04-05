#include "statistiques.h"
#include "ui_statistiques.h"
#include "connection.h"
#include <QMap>
#include <QVector>
#include <QString>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtWidgets/QGridLayout>
#include <QSqlQuery>
#include <QDebug>
QT_CHARTS_USE_NAMESPACE
statistiques::statistiques(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::statistiques)
{

    ui->setupUi(this);
    int row_count = 0;
    int row_count1 = 0;
    int row_count2 = 0;
            QSqlQuery query,query2,query3;
            query.prepare("SELECT * FROM produits where prix < 500 ");
            query.exec();
            query2.prepare("SELECT * FROM produits where (prix >= 500) AND (prix < 5000) ");
            query2.exec();
            query3.prepare("SELECT * FROM produits where prix >= 5000");
            query3.exec();
            while(query3.next())
                row_count2++;
            while(query2.next())
                 row_count1++;
            while(query.next())
                  row_count++;

                qDebug()<<row_count<<row_count1<<row_count2;
        QPieSeries *series = new QPieSeries();
                series->append("Produits ont un prix superieur a 5000 DT", row_count2);
                series->append("Produits ont un prix entre 5000 et 500 DT", row_count1);
                series->append("Produits ont un prix inferieur a 500 DT", row_count);
        QChart *chart = new QChart();
                chart->addSeries(series);
                chart->setTitle("Statistiques Des Prix");
                chart->setAnimationOptions(QChart::AllAnimations);
                chart->legend()->setAlignment(Qt::AlignRight);
                chart->legend()->setBackgroundVisible(true);
                chart->legend()->setBrush(QBrush(QColor(128, 128, 128, 128)));
        chart->legend()->setPen(QPen(QColor(248, 246, 0)));
                series->setLabelsVisible();
        QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);
                QGridLayout *mainLayout = new QGridLayout;
                    mainLayout->addWidget(chartView, 1, 1);
                    setLayout(mainLayout);

}

statistiques::~statistiques()
{
    delete ui;
}
