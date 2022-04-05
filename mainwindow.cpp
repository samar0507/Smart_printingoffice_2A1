#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employes.h"
#include<QMessageBox>
#include<QIntValidator>
#include<QFileDialog>
#include<QImage>
#include <QFile>
#include <QUdpSocket>
#include <QPainter>
#include "qrcode.h"
#include<QtSvg/QSvgRenderer>
#include<QSvgRenderer>
#include<QPixmap>
#include<QDebug>
#include<vector>
#include<iostream>
#include<fstream>
#include <QDate>
#include <QTcpSocket>

using qrcodegen::QrCode;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->id->setValidator(new QIntValidator(0,9999999,this));
    ui->tab_employes->setModel(e.afficher());
    ui->tab_id_2->setModel((e.afficher_id()));
    mSocket=new QTcpSocket(this);
    mSocket->connectToHost("localhost",2000);
    if (mSocket->waitForConnected(3000))
    {
        ui->plainTextEdit->appendPlainText("se connecter correctement");
    }
    else
    {
        ui->plainTextEdit->appendPlainText("pas de connexion");
    }
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(leer()));
}

void MainWindow::leer()
{
    QByteArray buffer;
    buffer.resize(mSocket->bytesAvailable());
    mSocket->read(buffer.data(),buffer.size());
    ui->plainTextEdit->setReadOnly(true);
    ui->plainTextEdit->appendPlainText(QString(buffer));
}
MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_add_btn_clicked()
{
    int id=ui->id->text().toInt();
        QString nom=ui->nom->text();
        QString prenom=ui->per->text();
        QDate date_naiss=ui->date->date();
        QString pass= ui->fonc->text();
        employes e(id,nom,prenom,date_naiss,pass);
        bool test=e.ajouter();
        if(test)
        {
            //REFRESH
            ui->tab_employes->setModel(e.afficher());
            ui->tab_id_2->setModel(e.afficher_id());
            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("Ajout effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Failed"),
                        QObject::tr("Ajout non effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
}

void MainWindow::on_del_btn_clicked()
{
    int id=ui->combo->currentText().toInt();
         bool test=e.supprimer(id);
         if(test)
         {
             //REFRESH
             ui->tab_employes->setModel(e.afficher());
             ui->tab_id_2->setModel(e.afficher_id());
             QMessageBox::information(nullptr, QObject::tr("OK"),
                         QObject::tr("Suppression effectuée.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
         }
         else
         {
             QMessageBox::critical(nullptr, QObject::tr("Failed"),
                         QObject::tr("Suppression non effectuée.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);

         }
}

void MainWindow::on_mod_btn_clicked()
{
    int id=ui->update_id->text().toInt();
           QString nom=ui->nom_mod->text();
           QString prenom=ui->per_mod->text();
           QDate date_naiss=ui->date_mod->date();
           QString pass=ui->fonc_mod->text();
        bool test=e.modifier(id,nom,prenom,date_naiss,pass);
        if(test)
        {
            //REFRESH
            ui->tab_employes->setModel(e.afficher());
            ui->tab_id_2->setModel(e.afficher_id());
            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("Modification effectuée.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Failed"),
                        QObject::tr("Modification non effectuée.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
}

void MainWindow::on_load_butt_clicked()
{
    QSqlQueryModel* modal= new QSqlQueryModel();
       modal->setQuery("SELECT id  FROM employes");
       ui->combo->setModel(modal);
}

void MainWindow::on_insertion_photo_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,tr("choose"),"",tr("Image(*.png *.jpeg *.jpg *.bmp *.gif)"));
    if (QString::compare(filename,QString()) !=0)
    {
        QImage image;
        bool valid = image.load(filename);
        if(valid)
        {
            image=image.scaledToWidth(ui->img_label->width(), Qt::SmoothTransformation);
                    ui->img_label->setPixmap(QPixmap::fromImage(image));

        }

     }
}

QSqlQueryModel * employes::tri_fonc()
{   QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from employes order by fonc");
    return model;}

void MainWindow::on_tri_resp_clicked()
{

    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectué avec succès.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_employes->setModel(e.tri_fonc());
}
QSqlQueryModel * employes::tri_nom()
{   QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from employes order by nom");
    return model;}
void MainWindow::on_tri_nom_clicked()
{

    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectué avec succès.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_employes->setModel(e.tri_nom());
}
QSqlQueryModel * employes::tri_prenom()
{   QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from employes order by prenom");
    return model;}
void MainWindow::on_tri_prenom_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectué avec succès.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_employes->setModel(e.tri_prenom());
}
//QSqlQueryModel * employes::recherche(int id)
//{
//    QSqlQuery query ;
//    QSqlQueryModel* model=new QSqlQueryModel();
//   query.prepare("select * from employes where id =:id");
//    query.bindValue(":id",id);
//    query.exec();
//    model->setQuery(query);
//return model;
//}
//void MainWindow::on_rechercher_clicked()
//{
//    {
//        ui->tab_employes->setModel(e.afficher());
//             int id=ui->cherche->text().toInt();
//             e.rechercher(ui->tab_employes,id);
//                }
//}

QSqlQueryModel*  employes ::afficher_id()
{ QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("select id from employes");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
return model;
}


//void MainWindow::on_enviar_clicked()
//{   auto datagrama = ui->msj->text().toLatin1();
//    mSocket->writeDatagram(datagrama, QHostAddress::Broadcast,ui->puerto->value());
//}





void MainWindow::on_tab_id_2_activated(const QModelIndex &index)
{
        QSqlQuery query;
        QString id=ui->tab_id_2->model()->data(index).toString();
        query.prepare("select * from employes where id='"+id+"'");
        if(query.exec())
        {
            while (query.next())
            {
                ui->update_id->setText(query.value(0).toString());
                ui->nom_mod->setText(query.value(1).toString());
                ui->per_mod->setText(query.value(2).toString());
                ui->date_mod->setDate(query.value(3).toDate());
                ui->fonc_mod->setText(query.value(4).toString());
            }
         }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Failed"),
                            QObject::tr("Impossible.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }
}

void MainWindow::on_qr_clicked()
{
    if(ui->tab_employes->currentIndex().row()==-1)
                   QMessageBox::information(nullptr, QObject::tr("QrCode"),
                                            QObject::tr("Veuillez Choisir un client du Tableau.\n"
                                                        "Click Ok to exit."), QMessageBox::Ok);
               else
               {
                    int id=ui->tab_employes->model()->data(ui->tab_employes->model()->index(ui->tab_employes->currentIndex().row(),0)).toInt();
                    const QrCode qr = QrCode::encodeText(std::to_string(id).c_str(), QrCode::Ecc::LOW);
                    std::ofstream myfile;
                    myfile.open ("qrcode.svg") ;
                    myfile << qr.toSvgString(1);
                    myfile.close();
                    QSvgRenderer svgRenderer(QString("qrcode.svg"));
                    QPixmap pix( QSize(90, 90) );
                    QPainter pixPainter( &pix );
                    svgRenderer.render( &pixPainter );
                    ui->qr_label->setPixmap(pix);


               }
}

void employes::rechercher(QTableView *table, int id)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from employes where regexp_like(id,:id);");
   query->bindValue(":id",id);

   if(id==0)
   {
       query->prepare("select * from employes");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}

//void MainWindow::on_connexion_clicked()
//{
//    mSocket->bind(ui->puerto->value(), QUdpSocket::ShareAddress) ;
//}

void MainWindow::on_CHAT_clicked()
{
    mSocket->write(ui->lineEdit->text().toLatin1().data(),ui->lineEdit->text().size());
    ui->plainTextEdit->appendPlainText(ui->lineEdit->text());
    ui->lineEdit->clear();
}

void MainWindow::on_cherche_textChanged(const QString &arg1)
{
    e.clear_employes(ui->tab_employes);
            int id=ui->cherche->text().toInt();
            e.rechercher(ui->tab_employes,id);
}
