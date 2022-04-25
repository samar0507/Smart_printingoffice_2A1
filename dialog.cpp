#include "dialog.h"
#include "arduino1.h"
#include "ui_dialog.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

int nbr1=20;

dialog::dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog)
{
    ui->setupUi(this);

    serial = new QSerialPort(); //Inicializa la variable Serial
    arduino_available = false;

    foreach (const QSerialPortInfo &serial_Info, QSerialPortInfo::availablePorts()) {//Lee la información de cada puerto serial
            qDebug()<<"Puerto: "<<serial_Info.portName();
            portname = serial_Info.portName();
            qDebug()<<"Vendor Id: "<<serial_Info.vendorIdentifier();
            vendorId = serial_Info.vendorIdentifier();
            qDebug()<<"Product Id: "<<serial_Info.productIdentifier();
            productId = serial_Info.productIdentifier();
            arduino_available = true;
        }
        if(arduino_available){
            arduino_init();
        }
        ui->lcdNumber_2->display(nbr1);
        QSqlQuery query;
                  query.prepare("DELETE FROM arduino");
                   query.exec();

    }

   dialog::~dialog()
    {
        delete ui;
    }

    void dialog::arduino_init()
    {
        serial->setPortName(portname);
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        serial->open(QIODevice::ReadWrite);
        connect(serial,SIGNAL(readyRead()),this,SLOT(serial_read()));
    }



    void dialog::serial_read()
    {
        if(serial->isWritable()&&arduino_available)
        {
         serialData = serial->readAll();
         serialBuffer +=QString::fromStdString(serialData.toStdString());
            qDebug()<<serialBuffer;
    dialog::update_dist(serialBuffer);




        }
    }

    void dialog::update_dist(const QString sensor_reading)
    {
         ui->lcdNumber->display(sensor_reading);
    }

void dialog::on_pushButton_ON_clicked()
{
    if((serial->isWritable())&&(nbr1>0)){
            serial->write("2");
            qDebug()<<"ouvrir";

        }
        else {
            QMessageBox::information(nullptr, QObject::tr("non dispo"),
                        QObject::tr("parking complet.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
}

void dialog::on_pushButton_OFF_clicked()
{
    if(serial->isWritable()&&(nbr1>0)){
          serial->write("1");
          qDebug()<<"fermer";
          nbr1 --;
          ui->lcdNumber_2->display(nbr1);
          QString d1 = QDateTime::currentDateTime().toString();
          arduino1 a1(nbr1,d1);
          a1.ajouter();
      }
      else{nbr1=20;
          ui->lcdNumber_2->display(nbr1);}


}
bool arduino1::ajouter()
{
    QString quantite_string=QString::number(nbr1);
    QSqlQuery query;
          query.prepare("INSERT INTO arduino (nbr, DATE_AJOUT) "
                        "VALUES (:nbr, :DATE_AJOUT)");
          query.bindValue(0, quantite_string);
          query.bindValue(1, date_ajout);
          return  query.exec();

}
